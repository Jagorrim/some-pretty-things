from random import randrange


class Treap:
    def __init__(self, x):
        # self.l and self.r actually are "pointers" to childs. If any of these fields is 0 so that node hasnt that child.
        self.x: int = x
        self.y: int = randrange(1, 1_000_000_000)
        self.l: Treap = 0
        self.r: Treap = 0


def split(t: Treap, x) -> [Treap, Treap]:
    if t == 0: return [0, 0]

    if t.x <= x:
        q = split(t.r, x)
        t.r = q[0]
        return [t, q[1]]
    else:
        q = split(t.l, x)
        t.l = q[1]
        return [q[0], t]


def merge(t1: Treap, t2: Treap) -> Treap:
    if t1 == 0: return t2
    if t2 == 0: return t1

    if t1.y > t2.y:
        t1.r = merge(t1.r, t2)
        return t1
    else:
        t2.l = merge(t1, t2.l)
        return t2


def max_item(t: Treap) -> Treap:
    if t.r == 0: return t
    return max_item(t.r)


def min_item(t: Treap) -> Treap:
    if t.l == 0: return t
    return min_item(t.l)


ans = []
mod = 1_000_000_000

if __name__ == "__main__":
    n = int(input())
    size = 0
    y = 0
    t = 0

    for i in range(n):
        a = input()
        c = a.split()[0]
        num = int(a.split()[1])
        if c == '+':
            num += y
            if y != 0:
                while num >= mod:
                    num -= mod
            y = 0
            if t == 0:
                t = Treap(num)
            else:
                q = split(t, num)
                if q[0] != 0 and max_item(q[0]).x == num:
                    t = merge(q[0], q[1])
                else:
                    t = merge(merge(q[0], Treap(num)), q[1])
            size += 1
        else:
            q = split(t, num - 1)
            if q[1] == 0:
                y = -1
            else:
                y = min_item(q[1]).x
            t = merge(q[0], q[1])
            ans.append(str(y))
print("\n".join(ans))
