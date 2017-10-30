#! /usr/bin/env python


import cPickle
import gzip
import random

import numpy


PATH = "mnist.pkl.gz"

LEARNING_RATE = 0.1
ITER_MAX = 1
DIGITS = 10

# Recunoaste 10 cifre aleatoare.
TEST_DIGITS = 10


def load_data(path):
    with gzip.open(path, "rb") as stream:
        train, valid, test = cPickle.load(stream)
    return {
        "train": train,
        "valid": valid,
        "test": test,
    }


def activation(value):
    """Functia de activare a neuronului."""
    # Intoarce 1 doar in momentul in care suma ponderata depaseste
    # strict bias-ul setat.
    return float(value > 0)


def learn_perceptron(digit, train_data):
    """Facem un perceptron sa deosebeasca o cifra fata de celelalte."""
    # Obtinem constantele lungimilor datelor de antrenament.
    digit_len = len(train_data[0][0])
    digit_count = len(train_data[0])
    # Definim datele de start.
    count = 0    # pt. nr. de iteratii
    classified_status = False    # sunt datele clasificate sau nu
    bias = 0    # un bias de start
    weights = numpy.random.uniform(0, 1, digit_len)    # ponderi random pt. fiecare dendrita

    # Rulam algoritmul pana avem toate datele clasificate sau am atins numarul
    # maxim de rulari.
    while not classified_status and count < ITER_MAX:
        # Pentru fiecare cifra si set de pixeli a acesteia...
        for idx in range(digit_count):
            label, pixels = map(lambda pos: train_data[pos][idx], (1, 0))
            # 0 daca nu e ceea ce cautam, maxim altfel (1)
            expect = float(label == digit)
            # Calculam suma ponderilor cu fiecare neuron.
            total = numpy.add(numpy.dot(weights, pixels), bias)
            # Se activeaza sau nu in functie de total (depasim strict biasul).
            trigger = activation(total)
            # Invatam prin ajustarea datelor curente.
            adjust = (expect - trigger) * LEARNING_RATE
            # Ajustam biasul.
            bias += adjust
            # Si acum reteaua.
            weights = numpy.add(weights, numpy.dot(pixels, adjust))
            # Verificam conditiile de oprire.
            if expect == trigger:
                classified_status = True
        count += 1

    # Intoarcem perceptronul sub forma unei tuple de
    # bias si ponderi.
    return bias, weights


def get_perceptrons(data):
    trons = []
    for digit in range(DIGITS):
        # Antrenam cate un perceptron pt. fiecare cifra in parte,
        # ca sa o deosebeasca pe curenta de celelalte.
        digit_tron = learn_perceptron(digit, data["train"])
        trons.append(digit_tron)
    return trons


def print_stats(digits, total):
    for idx, ok in enumerate(digits[0]):
        print("Digit {}: {}".format(idx, float(ok) / digits[1][idx]))
    print("Average: {}".format(float(total[0]) / total[1]))


def percepscore(tron, pixels):
    bias, weights = tron
    total = numpy.add(numpy.dot(weights, pixels), bias)
    return total


def test_perceptrons(trons, data):
    """Ofera statistici cu privire la nr. de cifre corect identificate."""
    # Frecventa cifrelor de test.
    digit_ok = [0] * DIGITS
    digit_all = [0] * DIGITS
    any_ok = 0
    # Analog invatarii.
    test_data = data["test"]
    digit_count = len(test_data[0])
    for idx in range(digit_count):
        # Testam cifra `label` avand `pixels` dati.
        label, pixels = map(lambda pos: test_data[pos][idx], (1, 0))
        # Selectam perceptronul corespunzator cifrei in cauza.
        total = percepscore(trons[label], pixels)
        if activation(total):
            digit_ok[label] += 1
            any_ok += 1
        digit_all[label] += 1
    print_stats((digit_ok, digit_all), (any_ok, digit_count))


def recognize(trons, data):
    """Identifica aleator cifre."""
    test_data = data["test"]
    digit_count = len(test_data[0])
    indexes = random.sample(range(digit_count), TEST_DIGITS)
    for idx in indexes:
        label, pixels = map(lambda pos: test_data[pos][idx], (1, 0))
        tron_dict = {}
        for idx, tron in enumerate(trons):
            tron_dict[idx] = percepscore(tron, pixels)
        guess = sorted(tron_dict, key=lambda arg: tron_dict[arg], reverse=True)
        print("{}: {}".format(label, ", ".join(map(str, guess))))


def main():
    # Incarcam datele de antrenare, validare si test intr-un dictionar.
    data = load_data(PATH)
    # Obtinem perceptroni pentru fiecare cifra invatandu-i cu datele
    # de antrenament.
    trons = get_perceptrons(data)
    # Testam cu datele de testare ca sa vedem acuratetea.
    test_perceptrons(trons, data)
    # Recunoastere aleatoare din setul de date.
    recognize(trons, data)


if __name__ == "__main__":
    main()
