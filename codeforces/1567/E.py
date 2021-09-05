from __future__ import division, print_function

import os
import sys
from io import BytesIO, IOBase

if sys.version_info[0] < 3:
    from __builtin__ import xrange as range
    from future_builtins import ascii, filter, hex, map, oct, zip


BUFSIZE = 8192

class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


def print(*args, **kwargs):
    """Prints the values to a stream, or to sys.stdout by default."""
    sep, file = kwargs.pop("sep", " "), kwargs.pop("file", sys.stdout)
    at_start = True
    for x in args:
        if not at_start:
            file.write(sep)
        file.write(str(x))
        at_start = False
    file.write(kwargs.pop("end", "\n"))
    if kwargs.pop("flush", False):
        file.flush()


if sys.version_info[0] < 3:
    sys.stdin, sys.stdout = FastIO(sys.stdin), FastIO(sys.stdout)
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

input = lambda: sys.stdin.readline().rstrip("\r\n")

class Node:
    def __init__(self, first, last, suf, pre, length, ans):
        self.first = first
        self.last = last
        self.suf = suf
        self.pre = pre
        self.length = length
        self.ans = ans

def id_node():
    return Node(0, 0, 0, 0, 0, 0)

def combine(a: Node, b: Node):
    if a.length == 0:
        return b
    if b.length == 0:
        return a
    x = Node(a.first, b.last, 0, 0, a.length + b.length, a.ans + b.ans)
    if a.last <= b.first:
        if a.length == a.pre:
            x.pre = b.pre + a.length
        else:
            x.pre = a.pre
        if b.length == b.suf:
            x.suf = a.suf + b.length
        else:
            x.suf = b.suf
        x.ans += a.suf * b.pre
    else:
        x.pre = a.pre
        x.suf = b.suf
    return x

def main():
    n, q = tuple(map(int, input().split()))
    a = list(map(int, input().split()))
    log = 0
    while (1 << log) < n:
        log += 1
    size = 1 << log
    segtree = [id_node() for i in range(2 * size)]
    for i in range(n):
        segtree[size + i] = Node(a[i], a[i], 1, 1, 1, 1)
    for i in range(size - 1, 0, -1):
        segtree[i] = combine(segtree[i << 1], segtree[i << 1 | 1])
    for _ in range(q):
        t, l, r = tuple(map(int, input().split()))
        l -= 1
        if t == 1:
            l += size
            segtree[l] = Node(r, r, 1, 1, 1, 1)
            while l > 1:
                l >>= 1
                segtree[l] = combine(segtree[l << 1], segtree[l << 1 | 1])
        else:
            l += size
            r += size
            sml, smr = id_node(), id_node()
            while l < r:
                if l & 1:
                    sml = combine(sml, segtree[l])
                    l += 1
                if r & 1:
                    r -= 1
                    smr = combine(segtree[r], smr)
                l >>= 1
                r >>= 1
            print(combine(sml, smr).ans)

if __name__ == '__main__':
    main()
