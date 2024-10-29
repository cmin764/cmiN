WHITESPACE_STR = " \t\n\r"


def parse_array(s, _w=WHITESPACE_STR, _sep=","):
    array = None
    stack = []
    accumulator = ""

    open_brackets = 0
    sep_flag = False
    got_space = False
    started = False
    closed = False

    for idx, ch in enumerate(s):
        if ch in _w:
            got_space = True
            continue

        if ch == "[":
            if started and not stack:
                raise ValueError("Already started without a stack")
            if accumulator:
                raise ValueError("Accumulated without separation")
            if closed:
                raise ValueError("Previous element requires separator")
            open_brackets += 1
            started = True
            in_array = []
            if stack:
                stack[-1](in_array)
            else:
                array = in_array
            stack.append(in_array.append)
            sep_flag = False
            got_space = False
            closed = False

        elif not open_brackets:
            raise ValueError("Consuming chars without a start")

        elif ch == "]":
            if not open_brackets:
                raise ValueError("Already closed without stack")
            open_brackets -= 1
            closed = True
            if accumulator:
                stack[-1](int(accumulator))
                accumulator = ""
            stack.pop()
            sep_flag = False
            got_space = False
            started = False

        elif ch in _sep:
            if sep_flag:
                raise ValueError("Already separated")
            if accumulator:
                stack[-1](int(accumulator))
                accumulator = ""
            elif len(stack) == open_brackets:
                pass
            else:
                raise ValueError("Separator encountered after nothing")
            sep_flag = True
            got_space = False
            started = closed = False

        else:
            if not (ch.isdigit() or ch in ("+", "-")):
                raise ValueError(f"Bad number {ch!r}")
            if accumulator and got_space:
                raise ValueError("Accumulating with space in between")
            if not sep_flag and closed:
                raise ValueError("Accumulating without separating")
            accumulator += ch
            sep_flag = False
            got_space = False
            started = closed = False

    if open_brackets:
        raise ValueError("Not all open brackets were closed")

    if array is not None:
        return array
    else:
        raise ValueError("Empty array")


if __name__ == "__main__":
    # These "asserts" using only for self-checking and not necessary for auto-testing
    assert parse_array("[1, 2, 3]") == [1, 2, 3], "Simple"
    assert parse_array("[[1], 2, 3]") == [[1], 2, 3], "Nested"
    assert parse_array("[-3, [-2, 0], 10]") == [-3, [-2, 0], 10], "Negative integers"
    assert parse_array("[100]") == [100], "One number"
    assert parse_array("[2,     3]") == [2, 3], "Whitespaces"
    assert parse_array("[[10, [11]], [[[1], 2], 3], 5]") == [
        [10, [11]],
        [[[1], 2], 3],
        5,
    ], "Deep nested"
    assert parse_array("   [3, 4]   ") == [3, 4], "Skip whitespaces"
    assert parse_array("[[], 0]") == [[], 0], "Empty arrays"
    assert parse_array("[[0,], 0]") == [[0], 0], "Comma - closed bracket"

    try:
        parse_array("[asd]")
        assert False, "Only integers"
    except ValueError:
        pass

    try:
        parse_array("[2, 3]]")
        assert False, "Excess bracket"
    except ValueError as exc:
        print(exc)
        pass

    try:
        parse_array("[++2, 1]")
        assert False, "Two plus"
    except ValueError:
        pass

    try:
        parse_array("[10, 11, , 12]")
        assert False, "Two separators"
    except ValueError:
        pass

    try:
        parse_array(" 13 ")
        assert False, "Where is a list?"
    except ValueError:
        pass

    try:
        parse_array("[[2]")
        assert False, "Excess opened bracket"
    except ValueError:
        pass

    try:
        parse_array("[3 4]")
        assert False, "Check for spurious spaces within a number"
    except ValueError:
        pass

    try:
        parse_array("[10, 11,, 12]")
        assert False, "Check for double separators without a space in between"
    except ValueError:
        pass

    try:
        parse_array("[[]3]")
        assert False, "Check for missing separators after []"
    except ValueError:
        pass

    try:
        parse_array("[2[]]")
        assert False, " Check for missing separators before []"
    except ValueError:
        pass

    try:
        parse_array("[3],")
        assert False, "Excess separator"
    except ValueError:
        pass

    try:
        parse_array("[1,2]3")
        assert False, "Excess number"
    except ValueError:
        pass

    try:
        parse_array("[1], [2,3]")
        assert False, "Here should be only one array."
    except ValueError as exc:
        print(exc)
        pass

    try:
        parse_array("[[[[1], 2][]]]")
        assert False, "Require separation between elements"
    except ValueError as exc:
        print(exc)
        pass
