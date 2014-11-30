#! /usr/bin/env python


import random
from itertools import combinations
import math
import copy


def euclid(a, b):
    '''returns the Greatest Common Divisor of a and b'''
    a = abs(a)
    b = abs(b)
    if a < b:
        a, b = b, a
    while b != 0:
        a, b = b, a % b
    return a


def coprime(l):
    '''returns 'True' if the values in the list L are all co-prime
       otherwier, it returns 'False'. '''
    for i, j in combinations(l, 2):
        if euclid(i, j) != 1:
            return False
    return True


def extendedEuclid(a, b):
    '''return a tuple of three values: x, y and z, such that x is
    the GCD of a and b, and x = y * a + z * b'''
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extendedEuclid(b % a, a)
        return (g, x - (b // a) * y, y)


def modInv(a, m):
    '''returns the multiplicative inverse of a in modulo m as a
       positve value between zero and m-1'''
    # notice that a and m need to co-prime to each other.
    if coprime([a, m]) == False:
        return 0
    else:
        linearcombination = extendedEuclid(a, m)
        return linearcombination[1] % m


def extractTwos(m):
    '''m is a positive integer. A tuple (s, d) of integers is returned
    such that m = (2 ** s) * d.'''
    # the problem can be break down to count how many '0's are there in
    # the end of bin(m). This can be done this way: m & a stretch of '1's
    # which can be represent as (2 ** n) - 1.
    assert m >= 0
    i = 0
    while m & (2 ** i) == 0:
        i += 1
    return (i, m >> i)


def int2baseTwo(x):
    '''x is a positive integer. Convert it to base two as a list of integers
    in reverse order as a list.'''
    # repeating x >>= 1 and x & 1 will do the trick
    assert x >= 0
    bitInverse = []
    while x != 0:
        bitInverse.append(x & 1)
        x >>= 1
    return bitInverse


def modExp(a, d, n, p=None, q=None):
    '''returns a ** d (mod n)'''
    assert d >= 0
    assert n >= 0
    base2D = int2baseTwo(d)
    base2DLength = len(base2D)
    modArray = []
    result = 1
    for i in range(1, base2DLength + 1):
        if i == 1:
            modArray.append(a % n)
        else:
            modArray.append((modArray[i - 2] ** 2) % n)
    for i in range(0, base2DLength):
        if base2D[i] == 1:
            result *= base2D[i] * modArray[i]
    return result % n


def millerRabin(n, k):
    '''
    Miller Rabin pseudo-prime test
    return True means likely a prime, (how sure about that, depending on k)
    return False means definitely a composite.
    Raise assertion error when n, k are not positive integers
    and n is not 1
    '''
    assert n >= 1
    # ensure n is bigger than 1
    assert k > 0
    # ensure k is a positive integer so everything down here makes sense

    if n == 2:
        return True
    # make sure to return True if n == 2

    if n % 2 == 0:
        return False
    # immediately return False for all the even numbers bigger than 2

    extract2 = extractTwos(n - 1)
    s = extract2[0]
    d = extract2[1]
    assert 2 ** s * d == n - 1

    def tryComposite(a):
        '''Inner function which will inspect whether a given witness
        will reveal the true identity of n. Will only be called within
        millerRabin'''
        x = modExp(a, d, n)
        if x == 1 or x == n - 1:
            return None
        else:
            for j in range(1, s):
                x = modExp(x, 2, n)
                if x == 1:
                    return False
                elif x == n - 1:
                    return None
            return False

    for i in range(0, k):
        a = random.randint(2, n - 2)
        if tryComposite(a) == False:
            return False
    return True  # actually, we should return probably true.


def primeSieve(k):
    '''return a list with length k + 1, showing if list[i] == 1, i is a prime
    else if list[i] == 0, i is a composite, if list[i] == -1, not defined'''

    def isPrime(n):
        '''return True is given number n is absolutely prime,
        return False is otherwise.'''
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True
    result = [-1] * (k + 1)
    for i in range(2, int(k + 1)):
        if isPrime(i):
            result[i] = 1
        else:
            result[i] = 0
    return result


def findAPrime(a, b, k):
    '''Return a pseudo prime number roughly between a and b,
    (could be larger than b). Raise ValueError if cannot find a
    pseudo prime after 10 * ln(x) + 3 tries. '''
    x = random.randint(a, b)
    for i in range(0, int(10 * math.log(x) + 3)):
        if millerRabin(x, k):
            return x
        else:
            x += 1
    raise ValueError


def newKey(a, b, k):
    ''' Try to find two large pseudo primes roughly between a and b.
    Generate public and private keys for RSA encryption.
    Raises ValueError if it fails to find one'''
    try:
        p = findAPrime(a, b, k)
        while True:
            q = findAPrime(a, b, k)
            if q != p:
                break
    except ValueError:
        raise ValueError
    n = p * q
    m = (p - 1) * (q - 1)
    while True:
        e = random.randint(1, m)
        if coprime([e, m]):
            break
    d = modInv(e, m)
    return (n, e, d), (p, q)


def mod2prime(a, n, m, m1, m2):
    n1 = n % (m1 - 1)
    n2 = n % (m2 - 1)
    x1 = pow((a % m1), n1, m1)
    x2 = pow((a % m2), n2, m2)
    w = pow(m1, -1) % m2
    x = x1 + m1 * ((x2 - x1) * w % m2)
    return int(x)


def string2numList(strn):
    '''Converts a string to a list of integers based on ASCII values'''
    # Note that ASCII printable characters range is 0x20 - 0x7E
    return [ord(chars) for chars in strn]


def numList2string(l):
    '''Converts a list of integers to a string based on ASCII values'''
    # Note that ASCII printable characters range is 0x20 - 0x7E
    return ''.join(map(chr, l))


def numList2blocks(l, n):
    '''Take a list of integers(each between 0 and 127), and combines them
    into block size n using base 256. If len(L) % n != 0, use some random
    junk to fill L to make it.'''
    # Note that ASCII printable characters range is 0x20 - 0x7E
    returnList = []
    toProcess = copy.copy(l)
    if len(toProcess) % n != 0:
        for i in range(0, n - len(toProcess) % n):
            toProcess.append(random.randint(32, 126))
    for i in range(0, len(toProcess), n):
        block = 0
        for j in range(0, n):
            block += toProcess[i + j] << (8 * (n - j - 1))
        returnList.append(block)
    return returnList


def blocks2numList(blocks, n):
    '''inverse function of numList2blocks.'''
    toProcess = copy.copy(blocks)
    returnList = []
    for numBlock in toProcess:
        inner = []
        for i in range(0, n):
            inner.append(numBlock % 256)
            numBlock >>= 8
        inner.reverse()
        returnList.extend(inner)
    return returnList


def encrypt(message, modN, e, blockSize, padding=True):
    '''given a string message, public keys and blockSize, encrypt using
    RSA algorithms.'''
    if padding:
        length = len(message)
        toadd = (blockSize - (length % blockSize)) % blockSize
        message += chr(0) * toadd
    numList = string2numList(message)
    numBlocks = numList2blocks(numList, blockSize)
    return [modExp(blocks, e, modN) for blocks in numBlocks]


def decrypt(secret, modN, d, blockSize, padding=True, p=None, q=None):
    '''reverse function of encrypt'''
    #numBlocks = [modExp(blocks, d, modN) for blocks in secret]
    numBlocks = [mod2prime(blocks, d, modN, p, q) for blocks in secret]
    numList = blocks2numList(numBlocks, blockSize)
    rmessage = numList2string(numList)
    if padding:
        rmessage.rstrip(chr(0))
    return rmessage


if __name__ == '__main__':
    (n, e, d), (p, q) = newKey(10 ** 100, 10 ** 101, 50)
    bsize = 16
    show = True
    print ('n = {0}'.format(n))
    print ('e = {0}'.format(e))
    print ('d = {0}'.format(d))
    message = "abc"
    print(message)
    cipher = encrypt(message, n, e, bsize)
    if show:
        nl = blocks2numList(cipher, bsize)
        print(numList2string(nl))
    else:
        print(cipher)
    rmessage = decrypt(cipher, n, d, bsize, p=p, q=q)
    print(rmessage)
