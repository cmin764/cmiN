import copy
import functools
import itertools
from collections import deque

StateType = deque[deque[int]]

DIRECTIONS = tuple(itertools.product((0, 1, -1), (0, 1, -1)))[1:]


def _extend_borders(matrix: StateType, contract: bool = True):
    # Ensure extra rows/columns if there's potential for newborns outside the dir_map.

    # For rows (up or down).
    cols = len(matrix[0])
    row_template = deque([0] * cols)
    if upper_row := sum(matrix[0]):
        matrix.appendleft(row_template.copy())
    elif contract and not upper_row and not sum(matrix[1]):
        matrix.popleft()
    if lower_row := sum(matrix[-1]):
        matrix.append(row_template.copy())
    elif contract and not lower_row and not sum(matrix[-2]):
        matrix.pop()

    # For columns (left or right).
    if left_col := sum(matrix[idx][0] for idx in range(len(matrix))):
        for row in matrix:
            row.appendleft(0)
    elif (
        contract
        and not left_col
        and not sum(matrix[idx][1] for idx in range(len(matrix)))
    ):
        for row in matrix:
            row.popleft()
    if right_col := sum(matrix[idx][-1] for idx in range(len(matrix))):
        for row in matrix:
            row.append(0)
    elif (
        contract
        and not right_col
        and not sum(matrix[idx][-2] for idx in range(len(matrix)))
    ):
        for row in matrix:
            row.pop()


def _count_alive_neighbours(matrix: StateType, row_idx: int, col_idx: int) -> int:
    total = 0
    for direction in DIRECTIONS:
        # Take all 8 neighbours over all possible directions.
        adj_row_idx = row_idx + direction[0]
        adj_col_idx = col_idx + direction[1]
        # Skip the ones outside the dir_map.
        if adj_row_idx < 0 or adj_row_idx >= len(matrix):
            continue
        if adj_col_idx < 0 or adj_col_idx >= len(matrix[0]):
            continue
        # Count the living ones.
        total += matrix[adj_row_idx][adj_col_idx]
    return total


def _transform_cell(cell: int, alive_neighbours: int) -> int:
    # Tackle a living cell.
    if cell:
        if 2 <= alive_neighbours <= 3:
            return 1  # continues to live
        return 0  # over/underpopulation

    # Let's see if we can revive a dead cell.
    return int(alive_neighbours == 3)


def _generate(matrix: StateType) -> StateType:
    _extend_borders(matrix)
    new_matrix = copy.deepcopy(matrix)

    for row_idx, row in enumerate(matrix):
        for col_idx, cell in enumerate(row):
            alive_neighbours = _count_alive_neighbours(matrix, row_idx, col_idx)
            new_cell = _transform_cell(cell, alive_neighbours)
            new_matrix[row_idx][col_idx] = new_cell

    return new_matrix


def _display_matrix(matrix: StateType, alive_cells: int):
    for row in matrix:
        print(list(row))
    print(f"Dimensions: {len(matrix)}x{len(matrix[0])}")
    print("Alive cells: ", alive_cells)


def life_counter(state: tuple[tuple[int, ...], ...], tick_n: int) -> int:
    matrix = deque((deque(row) for row in state))
    alive_cells = 0
    for _ in range(tick_n):
        matrix = _generate(matrix)
        alive_cells = functools.reduce(lambda total, row: total + sum(row), matrix, 0)
        _display_matrix(matrix, alive_cells)
    return alive_cells


if __name__ == "__main__":
    # assert (
    #     life_counter(
    #         (
    #             (0, 1, 0, 0, 0, 0, 0),
    #             (0, 0, 1, 0, 0, 0, 0),
    #             (1, 1, 1, 0, 0, 0, 0),
    #             (0, 0, 0, 0, 0, 1, 1),
    #             (0, 0, 0, 0, 0, 1, 1),
    #             (0, 0, 0, 0, 0, 0, 0),
    #             (1, 1, 1, 0, 0, 0, 0),
    #         ),
    #         4,
    #     )
    #     == 15
    # ), "Example"
    # assert (
    #     life_counter(
    #         (
    #             (0, 1, 0, 0, 0, 0, 0),
    #             (0, 0, 1, 0, 0, 0, 0),
    #             (1, 1, 1, 0, 0, 0, 0),
    #             (0, 0, 0, 0, 0, 1, 1),
    #             (0, 0, 0, 0, 0, 1, 1),
    #             (0, 0, 0, 0, 0, 0, 0),
    #             (1, 1, 1, 0, 0, 0, 0),
    #         ),
    #         15,
    #     )
    #     == 14
    # ), "Little later"
    # assert life_counter(((0, 1, 0), (0, 0, 1), (1, 1, 1)), 50) == 5, "Glider"
    # assert (
    #     life_counter(
    #         (
    #             (1, 1, 0, 1, 1),
    #             (1, 1, 0, 1, 1),
    #             (0, 0, 0, 0, 0),
    #             (1, 1, 0, 1, 1),
    #             (1, 1, 0, 1, 1),
    #         ),
    #         100,
    #     )
    #     == 16
    # ), "Stones"
    # assert life_counter([[0, 1, 0], [0, 0, 1], [1, 1, 1]], 999) == 5
    print(
        life_counter(
            (
                (0, 1, 0, 0, 0, 0, 0),
                (0, 0, 1, 0, 0, 0, 0),
                (1, 1, 1, 0, 0, 0, 0),
                (0, 0, 0, 0, 0, 1, 1),
                (0, 0, 0, 0, 0, 1, 1),
                (0, 0, 0, 0, 0, 0, 0),
                (1, 1, 1, 0, 0, 0, 0),
            ),
            15,
        )
    )
