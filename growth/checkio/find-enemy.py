import functools
import string
from collections import OrderedDict

Pos = tuple[str, int]
Grid = dict[str, list[int | str | None]]

# Extend the available columns with left & right border.
CHARS = OrderedDict.fromkeys("@" + string.ascii_uppercase + "[")
MAX_ROWS = 11


@functools.lru_cache(maxsize=len(CHARS))
def _get_orientation(char: str) -> OrderedDict[str, tuple[int, int]]:
    level = (ord(char) - ord("A")) % 2
    orient = {
        # Return all the adjacent neighbours in trigonometric order starting with North.
        #  (letter/col, level/row)
        "N": (0, -1),  # 0
        "NW": (-1, level - 1),  # 1
        "SW": (-1, level),  # 2
        "S": (0, 1),  # 3
        "SE": (1, level),  # 4
        "NE": (1, level - 1),  # 5
    }
    return OrderedDict(orient)


def _create_map(default: int | str | None = None) -> Grid:
    # Get an extended grid, surrounded by a thin border.
    grid = {key: [default] * MAX_ROWS for key in CHARS}
    return grid


def _step_to_pos(step: tuple[int, int], pos: Pos) -> Pos:
    return chr(ord(pos[0]) + step[0]), pos[1] + step[1]


def _is_pos_good(pos: Pos) -> bool:
    return pos[0] in CHARS and 0 <= pos[1] < MAX_ROWS


def _get_distance(you: Pos, enemy: Pos) -> int:
    dist_map = _create_map()
    dist_map[you[0]][you[1]] = 0
    to_explore = {you}

    while to_explore:
        cell = to_explore.pop()
        distance = dist_map[cell[0]][cell[1]]

        for step in _get_orientation(cell[0]).values():
            new_pos = _step_to_pos(step, cell)
            if not _is_pos_good(new_pos):
                continue  # outside the dir_map

            if (
                old_dist := dist_map[new_pos[0]][new_pos[1]]
            ) is None or old_dist > distance + 1:
                dist_map[new_pos[0]][new_pos[1]] = distance + 1
                to_explore.add(new_pos)

    # for idx in range(1, 10):
    #     print(*(dist_map[char][idx] for char in CHARS))
    return dist_map[enemy[0]][enemy[1]]


def _draw_border(dir_map: Grid, *, forward: Pos, rotation: int, side: str):
    if not _is_pos_good(forward):
        return

    if dir_map[forward[0]][forward[1]] != "C":
        dir_map[forward[0]][forward[1]] = side
    while True:
        orientation = _get_orientation(forward[0])
        step = tuple(orientation.values())[rotation]
        forward = _step_to_pos(step, forward)
        if _is_pos_good(forward):
            dir_map[forward[0]][forward[1]] = side
        else:
            break


def _fill_sector(dir_map: Grid, *, cell: Pos):
    if not _is_pos_good(cell):
        return

    to_explore = {cell}
    while to_explore:
        cell = to_explore.pop()
        label = dir_map[cell[0]][cell[1]]

        for step in _get_orientation(cell[0]).values():
            new_pos = _step_to_pos(step, cell)
            if not _is_pos_good(new_pos):
                continue  # outside the dir_map

            if not (old_label := dir_map[new_pos[0]][new_pos[1]]) or old_label == "N":
                dir_map[new_pos[0]][new_pos[1]] = label
                to_explore.add(new_pos)


def _get_aim(you: Pos, enemy: Pos, *, direction: str) -> str:
    dir_map = _create_map("N")
    dir_map[you[0]][you[1]] = "C"  # in the center
    orientation = _get_orientation(you[0])
    cardinals = list(orientation)
    steps = tuple(orientation.values())
    cardinal_diff = (
        lambda nose, target: (cardinals.index(nose) + cardinals.index(target)) % 6
    )

    border_heads = [
        # Front
        (
            _step_to_pos(orientation[direction], you),
            {
                "dirs": ["NE", "NW"],
                "label": "F",
            },
        ),
        # Back
        (
            _step_to_pos(steps[cardinal_diff(direction, "S")], you),
            {
                "dirs": ["SE", "SW"],
                "label": "B",
            },
        ),
        # Left
        (
            you,
            {
                "dirs": ["NW", "SW"],
                "label": "L",
            },
        ),
        # Right
        (
            you,
            {
                "dirs": ["NE", "SE"],
                "label": "R",
            },
        ),
    ]
    # Draw the borders for each of the front, back, left and right sectors.
    for border_head, config in border_heads:
        for border_dir in config["dirs"]:
            _draw_border(
                dir_map,
                forward=border_head,
                rotation=cardinal_diff(direction, border_dir),
                side=config["label"],
            )

    # Then fill the sectors with the corresponding aim.
    fill_heads = [head for (head, conf) in border_heads if conf["label"] in ("F", "B")]
    fill_heads.extend(
        [
            # Left
            _step_to_pos(steps[cardinal_diff(direction, "NW")], you),
            _step_to_pos(steps[cardinal_diff(direction, "SW")], you),
            # Right
            _step_to_pos(steps[cardinal_diff(direction, "NE")], you),
            _step_to_pos(steps[cardinal_diff(direction, "SE")], you),
        ]
    )
    for fill_head in fill_heads:
        _fill_sector(dir_map, cell=fill_head)

    # for idx in range(1, 10):
    #     print(*(dir_map[char][idx] for char in CHARS))
    return dir_map[enemy[0]][enemy[1]]


def find_enemy(you: str, direction: str, enemy: str) -> [str, int]:
    you_pos = (you[0], int(you[1]))
    enemy_pos = (enemy[0], int(enemy[1]))
    dist = _get_distance(you_pos, enemy_pos)
    aim = _get_aim(you_pos, enemy_pos, direction=direction)
    return [aim, dist]


print("Example:")
# print(find_enemy("G5", "N", "G4"))
print(find_enemy("D9", "NE", "B9"))

assert find_enemy("G5", "N", "G4") == ["F", 1]
assert find_enemy("G5", "N", "I4") == ["R", 2]
assert find_enemy("G5", "N", "J6") == ["R", 3]
assert find_enemy("G5", "N", "G9") == ["B", 4]
assert find_enemy("G5", "N", "B7") == ["L", 5]
assert find_enemy("G5", "N", "A2") == ["L", 6]
assert find_enemy("G3", "NE", "C5") == ["B", 4]
assert find_enemy("H3", "SW", "E2") == ["R", 3]
assert find_enemy("A4", "S", "M4") == ["L", 12]
assert find_enemy("D9", "NE", "B9") == ["B", 2]
assert find_enemy("B2", "N", "C4") == ["B", 2]
