#! /usr/bin/env python


import gzip
import math
import pickle
import random
import sys
import time

import numpy


LEARN_RATE = 0.05
HIDDEN_LAYER = 100
MAX_ITER = 1
DATA_PATH = "../../2/tron/mnist.pkl.gz"
TRAIN_FACTOR = 1


def load_data(path):
    """Incarca si intoarce un dictionar cu datele disponibile."""
    with gzip.open(path, "rb") as stream:
        data = pickle.load(stream)
    return {
        "train": data[0],
        "valid": data[1],
        "test": data[2],
    }


def show_perc(perc):
    """Afiseaza procent."""
    string = str(int(perc)).zfill(2) + "%"
    sys.stdout.write("\b" * len(string))
    sys.stdout.write(string)
    sys.stdout.flush()


def generate_wb():
    """Intoarce ponderile si biasurile initiale (primele 2 straturi)."""
    # Generam un set initial de date pentru ponderi si biasuri astfel incat
    # sa avem date aleatoare normalizate de dimensiuni mici. Acestea urmeaza
    # o distributie conforma lungimii setului de date.
    weights = [
        numpy.random.normal(
            0, 1.0 / math.sqrt(784),
            (HIDDEN_LAYER, 784)
        ),
        numpy.random.rand(
            10,
            HIDDEN_LAYER
        )
    ]
    biases = [
        numpy.random.normal(
            0, 1.0 / math.sqrt(10),
            HIDDEN_LAYER
        ),
        numpy.random.rand(
            10
        )
    ]
    return weights, biases


def sigmoid(zet):
    """Activare uniforma."""
    return 1 / (1 + math.exp(-zet))


def last_layer_error(last_layer_output, label):
    target_output_vector = numpy.zeros(10)
    target_output_vector[label] = 1
    one_minus_target_output_vector = numpy.ones(10) - target_output_vector
    one_minus_output = numpy.ones(10) - last_layer_output
    return (target_output_vector * one_minus_output -
            one_minus_target_output_vector * last_layer_output)


def intermidiate_layer_error(previous_layer_error, weights, output):
    one_minus_output = numpy.ones(HIDDEN_LAYER) - output
    return (output * one_minus_output *
            numpy.dot(previous_layer_error, weights))


def compute_overall_error(eta, previous_layer_error, current_layer_output):
    for_dropout = random.sample(range(HIDDEN_LAYER), 50)
    for idx in range(len(for_dropout)):
        current_layer_output[for_dropout[idx]] = 0
    mat = numpy.array(previous_layer_error)[numpy.newaxis]
    biases = numpy.array(current_layer_output)[numpy.newaxis]
    return eta * numpy.dot(mat.T, biases)


def activate_last_layer(zet):
    elements_sum = sum([math.pow(math.e, element) for element in zet])
    for idx in range(len(zet)):
        zet[idx] = math.pow(math.e, zet[idx]) / elements_sum
    return zet


def network_output(weights, biases, pixels):
    sigmoidify = numpy.vectorize(sigmoid)
    mat = numpy.array(pixels)[numpy.newaxis]
    to_be_vectorized = (numpy.dot(weights[0], mat.T).reshape(HIDDEN_LAYER) +
                        biases[0])
    output = [sigmoidify(to_be_vectorized)]
    last_layer = numpy.array(output[0])[numpy.newaxis]
    new_weights = weights[1] * 0.5
    zet = (numpy.dot(new_weights, last_layer.T.reshape(HIDDEN_LAYER, 1))
             .reshape(10) + biases[1])
    output.append(activate_last_layer(zet))
    return output


def backpropagation(weights, biases, pixels, label):
    output = network_output(weights, biases, pixels)
    delta = [last_layer_error(output[1], label)]
    delta.append(
        intermidiate_layer_error(
            delta[-1],
            weights[1],
            output[0]
        )
    )
    weights[1] = weights[1] + compute_overall_error(LEARN_RATE, delta[0],
                                                    output[0])
    weights[0] = weights[0] + compute_overall_error(LEARN_RATE, delta[1],
                                                    pixels)
    biases[0] = biases[0] + LEARN_RATE * delta[1] * output[0]
    biases[1] = biases[1] + LEARN_RATE * delta[0] * output[1]


def classify_instance(weights, biases, pixels, label):
    output = network_output(weights, biases, pixels)
    if output[1].argmax() == label:
        return 1
    return 0


def learn_neurons(data):
    percentage = (lambda nr, total, rnd=0:
        round(float(nr) / total, rnd + 2) * 100)

    # Incarca 2 straturi ale retelei.
    weights, biases = generate_wb()
    # Re-normalizeaza valorile initiale.
    norm = numpy.vectorize(lambda nr: nr / 100)
    for idx in range(2):
        weights[idx] = norm(weights[idx])
        biases[idx] = norm(biases[idx])

    # Antrenam reteaua de cate iteratii vrem.
    data_len = int(len(data["train"][0]) * TRAIN_FACTOR)
    perc = 0    # ratio as percentage
    for idx in range(MAX_ITER):
        for idx in range(data_len):
            ratio = percentage(idx, data_len)
            if ratio > perc:
                perc = ratio
                show_perc(perc)
            backpropagation(
                weights, biases,
                data["train"][0][idx],
                data["train"][1][idx]
            )

    print("\nFinished\n\n")
    print("Testing...")
    sys.stdout.flush()

    good = 0
    data_len = len(data["test"][0])
    for idx in range(data_len):
        good += classify_instance(
            weights, biases,
            data["test"][0][idx],
            data["test"][1][idx]
        )
    return good, percentage(good, data_len, rnd=2)


def main():
    start = time.time()

    data = load_data(DATA_PATH)
    good, perc = learn_neurons(data)
    print("Good: {} ({}%)\n".format(good, perc))

    delta = time.time() - start
    print("Time: {}s".format(round(delta, 2)))


if __name__ == "__main__":
    main()
