#! /usr/bin/env python
#
# bifinder: finds code sequences able to restore `__builtins__`
#
# Author(s): Ned Batchelder

"""Look for builtins..."""

import types

def is_builtins(v):
    """Does v seem to be the builtins?"""
    if hasattr(v, "open") and hasattr(v, "__import__"):
        return True
    if isinstance(v, dict):
        return "open" in v and "__import__" in v
    return False

def construct_some(cl):
    """Construct objects from class `cl`.

    Yields (obj, description) tuples.

    """
    # First yield the class itself
    classname = "{}.{}".format(cl.__module__, cl.__name__)
    yield cl, classname

    made = False
    for args in [
        (), ("x",), ("x", "y"), ("x", "y", "z"),
        ("utf8",), ("os",), (1, 2, 3),
        (0,0,0,0,0,b"KABOOM",(),(),(),"","",0,b""),
        # Maybe there are other useful constructor args?
    ]:
        try:
            obj = cl(*args)
        except:
            continue
        desc = "{}{}".format(classname, args)
        yield obj, desc
        made = True
     
    if not made:
        print("Couldn't make a {}".format(classname))

def attributes(obj):
    """Produce a sequence of (name, value), the attributes of `obj`."""
    try:
        for n in dir(obj):
            if n in ('__dict__',):
                continue
            try:
                yield n, getattr(obj, n)
            except:
                continue
    except:
        pass

def items(obj):
    """Produce a sequence of (key, value), the items of `obj`."""
    try:
        for k in obj.keys():
            try:
                yield k, obj[k]
            except:
                continue
    except:
        pass

def attrs_and_items(obj, desc):
    """Produce a sequence of (name, value, desc) for data from `obj`."""
    for n, v in attributes(obj):
        desc2 = "{}.{}".format(desc, n)
        yield n, v, desc2
    for k, v in items(obj):
        desc2 = "{}[{!r}]".format(desc, k)
        yield k, v, desc2

def examine(obj, desc, seen, depth):
    """Examine the data reachable from `obj`, looking for builtins."""
    if depth > 10:
        return
    if id(obj) in seen:
        return
    if isinstance(obj, (type(""), type(b""), type(u""))):
        return

    seen.add(id(obj))

    # Look at the attributes and items
    for n, v, desc2 in attrs_and_items(obj, desc):
        if is_builtins(v):
            print("Looks like {} might be builtins".format(desc2))
        else:
            examine(v, desc2, seen, depth+1)

examined = 0
for cl in object.__subclasses__():
    seen = set()
    for obj, desc in construct_some(cl):
        print("Examining {}".format(desc))
        examine(obj, desc, seen, 0)
    examined += len(seen)

print("Examined {} objects".format(examined))
