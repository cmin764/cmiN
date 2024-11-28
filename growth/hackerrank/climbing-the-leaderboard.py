#!/bin/python3

import bisect
import os


#
# Complete the 'climbingLeaderboard' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY ranked
#  2. INTEGER_ARRAY player
#


def climbingLeaderboard(ranked, player):
    # Build a new ranked list in ascending order and without duplicates.
    norm_ranked = []
    last = None
    for idx in range(len(ranked) - 1, -1, -1):
        score = ranked[idx]
        if last is None or score != last:
            norm_ranked.append(score)
            last = score

    # print(norm_ranked)
    ranks = []
    total_ranks = len(norm_ranked)
    for score in player:
        norm_rank = bisect.bisect_right(norm_ranked, score)
        rank = total_ranks - norm_rank + 1
        ranks.append(rank)

    return ranks


if __name__ == "__main__":
    fptr = open(os.environ["OUTPUT_PATH"], "w")

    ranked_count = int(input().strip())
    ranked = list(map(int, input().rstrip().split()))
    player_count = int(input().strip())
    player = list(map(int, input().rstrip().split()))
    # ranked = [100, 100, 50, 40, 40, 20, 10]
    # player = [5, 25, 50, 120]
    # ranked = [100, 90, 90, 80, 75, 60]
    # player = [50, 65, 77, 90, 102]

    result = climbingLeaderboard(ranked, player)

    fptr.write("\n".join(map(str, result)))
    fptr.write("\n")

    fptr.close()
