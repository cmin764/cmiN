#! /usr/bin/env python3
# 04.01.2011 cmiN

class Sort:
    pyvec = list()
    bubblevec = list()
    quickvec = list()

    def pysort(self, vec):
        return sorted(vec)
    
    def bubblesort(self, vec):
        flag = True
        length = len(vec)
        j = 1
        while flag:
            flag = False
            for i in range(length - j):
                if vec[i] > vec[i + 1]:
                    tmp = vec[i]
                    vec[i] = vec[i + 1]
                    vec[i + 1] = tmp
                    flag = True
            j += 1
        return vec
    
    def quicksort(self, vec):
        if len(vec) > 1:
            lss, grt = list(), list()
            piv = vec.pop()
            for x in vec:
                if x <= piv:
                    lss.append(x)
                else:
                    grt.append(x)
            return self.quicksort(lss) + [piv] + self.quicksort(grt)
        else:
            return vec
        
    def str_to_int(self, vec):
        for i in range(len(vec)):
            vec[i] = int(vec[i])
        return vec
    
    def __init__(self, vec):
        self.pyvec = self.pysort(vec[:])
        self.bubblevec = self.bubblesort(vec[:])
        self.quickvec = self.quicksort(vec[:])

def show(args):
    for arg in args:
        for x in arg:
            print(x, end=" ")
        print()

def main():
    vec = input("Enter numbers separated by spaces: ")
    sob = Sort(vec.split())
    show([sob.pyvec, sob.bubblevec, sob.quickvec])
    
if __name__ == "__main__":
    main()
