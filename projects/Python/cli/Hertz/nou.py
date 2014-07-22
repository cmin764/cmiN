import md5
from this import s as zen

def solve(challenge):
    words = zen.split()
    unique = len(words)
    if int(unique) == 96:
        hidden = md5.new('int'+'len'+'split'+challenge+'s')
        return getattr(hidden, 'tsegidxeh'[::-1])()
    else:
        raise 'Wrong'

solution = solve('a5/cb')
