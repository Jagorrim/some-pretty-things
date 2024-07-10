from random import randrange
from math import ceil, floor


def get_median(data: list, ) -> int:
    base_index = randrange(0, len(data))
    base_elem = data[base_index]

    less = []
    greater = []

    meet_base_elem = False

    for i in data:
        if i < base_elem:
            less.append(i)
        else:
            if i == base_elem and meet_base_elem:
                greater.append(i)

            elif i == base_elem and not meet_base_elem:
                meet_base_elem = True

            else:
                greater.append(i)

    if len(less) == floor(len(data) / 2) or len(less) == ceil(len(data) / 2):
        return base_index

    if len(less) > ceil(len(data) / 2):
        return get_median(less)

    if len(less) < floor(len(data) / 2):
        return len(less) + get_median(greater)


# actually it works so slower than qsort that chose pivot item randomly (idk why)
def _qsort(data: list) -> list:
    if len(data) == 0 or len(data) == 1:
        return data

    if len(data) == 2:
        if data[0] > data[1]:
            data[0], data[1] = data[1], data[0]
        return data

    base_index = get_median(data)
    base_elem = data[base_index]

    less = []
    greater = []

    meet_base_elem = False

    for i in data:
        if i < base_elem:
            less.append(i)
        else:
            if i == base_elem and meet_base_elem:
                greater.append(i)

            elif i == base_elem and not meet_base_elem:
                meet_base_elem = True

            else:
                greater.append(i)

    return _qsort(less) + [base_elem] + _qsort(greater)


# this is main function, pls don't use another
def qsort(data: list) -> list:
    if len(data) == 0 or len(data) == 1:
        return data

    if len(data) == 2:
        if data[0] > data[1]:
            data[0], data[1] = data[1], data[0]
        return data

    base_index = randrange(0, len(data))
    base_elem = data[base_index]

    less = []
    greater = []

    meet_base_elem = False

    for i in data:
        if i < base_elem:
            less.append(i)
        else:
            if i == base_elem and meet_base_elem:
                greater.append(i)

            elif i == base_elem and not meet_base_elem:
                meet_base_elem = True

            else:
                greater.append(i)

    return qsort(less) + [base_elem] + qsort(greater)


if __name__ == '__main__':
    from time import time

    _1_time = 0
    _2_time = 0

    for _ in range(100):
        nums = [randrange(1, 101) for _ in range(1001)]
        start = time()
        _1 = _qsort(nums)
        _1_time += (time() - start)

        start = time()
        _2 = qsort(nums)
        _2_time += (time() - start)
    print(_1_time)
    print(_2_time)

