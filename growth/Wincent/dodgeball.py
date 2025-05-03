#! /usr/bin/env python

import collections
import itertools
import math
import sys
from pathlib import Path


Players = dict[int, tuple[int, int]]

DIRS2GEO = collections.OrderedDict([
    ((0, 1), "N"),
    ((1, 1), "NE"),
    ((1, 0), "E"),
    ((1, -1), "SE"),
    ((0, -1), "S"),
    ((-1, -1), "SW"),
    ((-1, 0), "W"),
    ((-1, 1), "NW"),
])
GEO2DIRS = collections.OrderedDict({geo: points for points, geo in DIRS2GEO.items()})
DIRS = list(DIRS2GEO)

DEBUG = False
NO_PRINT = True  # switch on to see the strategy in action


def _get_next_dir(
        crt_dir: tuple[int, int] | None = None, crt_geo: str | None = None
) -> tuple[int, int]:
    if crt_geo:
        crt_dir = GEO2DIRS[crt_geo]
    else:
        assert crt_dir, "missing any direction"

    # Pick the next direction relative to the input one looking clockwise.
    next_idx = DIRS.index(crt_dir) + 1
    return next(
        itertools.islice(
            itertools.cycle(DIRS2GEO),
            next_idx,
            next_idx + len(DIRS)
        )
    )


def _sign(number: int) -> int:
    # -1 (<0), 0 (=0), 1 (>0)
    return (number > 0) - (number < 0)


def _reverse_direction(direction: tuple[int, int]) -> tuple[int, int]:
    return direction[0] * -1, direction[1] * -1


def debug_print(*args, debug: bool = True) -> None:
    if NO_PRINT:
        return
    if debug and DEBUG or not debug:
        print(*args)


def play_game(
        players: Players, initial_player_id: int, initial_geo: str
) -> tuple[int, int]:
    debug_print("Players: ", players, initial_player_id, initial_geo, debug=False)
    current_pid = initial_player_id
    current_dir = _get_next_dir(crt_geo=initial_geo)
    debug_print(
        f"Starting from player {current_pid!r}"
        f" looking first to direction: {current_dir} ({DIRS2GEO[current_dir]})",
        debug=False
    )

    active_players = set(players)
    still_playing = True
    last_player = current_pid
    throws = 0

    while still_playing:
        # Look for a valid direction to throw the ball.
        still_playing = False
        current_coords = players[current_pid]

        # Select players which can receive the ball first, on a valid direction.
        candidates: dict[tuple[int, int], (int, float)] = {}
        for active_player in (active_players - {current_pid}):
            active_coords = players[active_player]

            # Ensure slope is valid
            dx = active_coords[0] - current_coords[0]
            dy = active_coords[1] - current_coords[1]
            if not any([dx == 0, dy == 0, abs(dx) == abs(dy)]):
                # Slope not in increment of 45 degrees.
                continue

            debug_print(f"Checking on candidate next player: {active_player}")
            # Build active direction relative to Ox and Oy slopes.
            active_dir = (_sign(dx), _sign(dy))
            active_distance: float = math.sqrt(math.pow(dx, 2) + math.pow(dy, 2))
            existing_candidate = candidates.get(active_dir)
            # Pick a closer player on an existing direction.
            existing_distance = existing_candidate[1] if existing_candidate else math.inf
            if existing_distance > active_distance:
                candidates[active_dir] = (active_player, active_distance)

        debug_print(f"Good candidates: {candidates}")
        while candidates:
            debug_print(
                f"Throw attempt in direction: {current_dir} ({DIRS2GEO[current_dir]})"
            )
            candidate = candidates.get(current_dir)
            if not candidate:
                current_dir = _get_next_dir(current_dir)
                continue

            debug_print(
                f"Found next player to throw the ball at: {candidate}", debug=False
            )
            throws += 1  # throws the ball
            active_players -= {current_pid}  # shooting player gets out
            # Player that receives the ball becomes now active.
            last_player = current_pid = candidate[0]
            # Receiving player looks on the next direction from arrival of the ball.
            current_dir = _get_next_dir(_reverse_direction(current_dir))
            still_playing = True  # we're still in the game
            break


    return throws, last_player


def main(input_file: Path):
    debug_print(f"Reading {input_file}...")
    lines = input_file.read_text().splitlines()
    cases_count = int(lines[0])
    idx = 1

    results: list[tuple[int, int]] = []

    for _ in range(cases_count):
        players_count = int(lines[idx])
        players: Players = {}
        idx += 1
        player_id = 1
        for _ in range(players_count):
            players[player_id] = tuple(map(int, lines[idx].split()))
            idx += 1
            player_id += 1
        initial_geo = lines[idx]
        idx += 1
        initial_player_id = int(lines[idx])
        idx += 1

        throws_count, last_player = play_game(players, initial_player_id, initial_geo)
        results.append((throws_count, last_player))

    output_file = input_file.parent / f"{input_file.stem}.out"
    lines = [f"{result[0]} {result[1]}" for result in results]
    output_file.write_text("\n".join(lines))
    debug_print(f"Challenge output: {output_file}")


if __name__ == "__main__":
    input_file = Path(sys.argv[1])
    main(input_file)
