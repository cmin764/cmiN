from collections import deque


BRACKETS = {
    "(": ")",
    "[": "]",
    "{": "}",
}


def checkio(expression: str) -> bool:
    stack = deque()
    for ch in expression:
        if ch in BRACKETS:
            stack.append(ch)
        elif ch in BRACKETS.values():
            if stack and BRACKETS[stack[-1]] == ch:
                stack.pop()
            else:
                return False
        else:
            continue  # not interested in chars other than brackets

    return not stack


# These "asserts" using only for self-checking and not necessary for auto-testing

print("Example:")
print(checkio("((5+3)*2+1)"))

# These "asserts" are used for self-checking
assert checkio("((5+3)*2+1)") == True
assert checkio("{[(3+1)+2]+}") == True
assert checkio("(3+{1-1)}") == False
assert checkio("[1+1]+(2*2)-{3/3}") == True
assert checkio("(({[(((1)-2)+3)-3]/3}-3)") == False
assert checkio("[(3)+(-1)]*{3}") == True
assert checkio("(((([[[{{{3}}}]]]]))))") == False
assert checkio("[1+202]*3*({4+3)}") == False
assert checkio("({[3]})-[4/(3*{1001-1000}*3)/4]") == True
assert checkio("[[[1+[1+1]]])") == False
assert checkio("(((1+(1+1))))]") == False
assert checkio("2+3") == True

print("The mission is done! Click 'Check Solution' to earn rewards!")
