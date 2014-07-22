import random

def process_1(item):
    val = random.random() * 10
    return sum([int(char.isspace()) * val for char in item])
