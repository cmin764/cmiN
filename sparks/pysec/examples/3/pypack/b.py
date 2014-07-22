import random

def process_smth(item):
    lo = ord("a")
    hi = lo + random.random() * 100 % 13
    return len(filter(lambda char: ord(char) >= lo and
                                   ord(char) <= hi, item))
