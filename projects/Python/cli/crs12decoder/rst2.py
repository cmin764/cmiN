#! /usr/bin/env python3.2

class RST2:
    def __init__(self, string):
        self.string = string.lower()
        self.charset = list()
        self.charset.append(0.5)
        for i in range(1, 7):
            self.charset.append(self.charset[i - 1] + 0.5)
        self.charset.extend([5, 4.5, 5.5])
        for i in range(10, 26):
            self.charset.append(self.charset[i - 1] + 0.5)

    def encode(self):
        result = 0
        for char in self.string:
            pos = ord(char) - ord("a")
            if pos == 7 or pos >= 9:
                nr = 100
            else:
                nr = 10
            result = result * nr + self.charset[pos]
        return result

def main():
    string = input("Input: ")
    if string.isalpha():
        robj = RST2(string)
        print("Output: " + str(robj.encode()))
    else:
        print("Error: Doar caractere a-z")
    input()

if __name__ == "__main__":
    main()
