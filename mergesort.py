from typing import Any


def merge(l1: list[Any], l2: list[Any], reverse=False) -> list[Any]:
    new_l = list()
    i1, i2 = 0, 0

    while i1 < len(l1) or i2 < len(l2):
        if i1 >= len(l1):
            new_l.append(l2[i2])
            i2 += 1
        elif i2 >= len(l2):
            new_l.append(l1[i1])
            i1 += 1
        elif not reverse:
            if l1[i1] < l2[i2]:
                new_l.append(l1[i1])
                i1 += 1
            else:
                new_l.append(l2[i2])
                i2 += 1
        else:
            if l1[i1] > l2[i2]:
                new_l.append(l1[i1])
                i1 += 1
            else:
                new_l.append(l2[i2])
                i2 += 1

    return new_l


def merge_sort(collection: list[Any], reverse=False) -> list[Any]:
    if len(collection) == 1 or len(collection) == 0:
        return collection

    elif len(collection) == 2:
        if not reverse and collection[1] < collection[0]:
            collection[0], collection[1] = collection[1], collection[0]
        elif reverse and collection[1] > collection[0]:
            collection[0], collection[1] = collection[1], collection[0]
        return collection

    else:
        return merge(
            merge_sort(collection[:len(collection) // 2], reverse=reverse),
            merge_sort(collection[len(collection) // 2:], reverse=reverse),
            reverse=reverse
        )


if __name__ == '__main__':
    print(merge_sort([1, 2, -6, 9, 9222, 21321323121], reverse=True))
