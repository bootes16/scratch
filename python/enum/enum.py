import sys
from collections import namedtuple

def mkenum(labels, values=None, start=0, name="Enum"):
    if values is None:
        values = tuple((i for i in range(start, start + len(labels.split()))))

    if sys.version_info < (3, 7):
        temp = namedtuple(name, labels)
        if sys.version_info < (2, 6):
            temp.__new__.func_defaults = values
        else:
            temp.__new__.__defaults__ = values
    else:
        temp = namedtuple(name, labels, defaults=values)
    
    return temp()

c = mkenum("Red Green Blue", start=1)

print(c)
print(mkenum("a b c", values=(9,8,7)))