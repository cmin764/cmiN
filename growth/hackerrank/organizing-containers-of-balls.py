#!/bin/python3

#
# Complete the 'organizingContainers' function below.
#
# The function is expected to return a STRING.
# The function accepts 2D_INTEGER_ARRAY container as parameter.
#


def organizingContainers(container):
    caps = sorted([sum(bucket) for bucket in container])
    freq = {}
    for bucket in container:
        for ball, count in enumerate(bucket, start=1):
            freq[ball] = freq.get(ball, 0) + count

    # print(caps, list(freq.values()))
    if sorted(freq.values()) == caps:
        return "Possible"

    return "Impossible"


if __name__ == "__main__":
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')
    # q = int(input().strip())
    # for q_itr in range(q):
    #     n = int(input().strip())
    #     container = []
    #     for _ in range(n):
    #         container.append(list(map(int, input().rstrip().split())))
    #     result = organizingContainers(container)
    #     fptr.write(result + '\n')
    # fptr.close()

    container = [(0, 2, 1), (1, 1, 1), (2, 0, 0)]
    result = organizingContainers(container)
    print(result)
