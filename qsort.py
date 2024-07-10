from random import randrange


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


print(qsort([5, 9, 1, 1, 2, 1, 2]))
