from math import floor
# from time import time


# n = int(input())  # Искомое число
# data = [int(i) for i in input().split()]


def ternary_search(n: int, data: list) -> int:
    l = 0
    r = len(data) - 1

    while r - l > 1:
        floor_third = floor((r - l + 1) / 3)
        mid_l = l + floor_third
        mid_r = r - floor_third

        if n < data[mid_l]:
            r = mid_l - 1
        elif n > data[mid_r]:
            l = mid_r + 1
        else:
            l = mid_l
            r = mid_r

    if data[l] == n:
        return l
    else:
        return r


# ternary_search(3, [1, 2, 3, 4, 5, 6, 7, 8, 9])
#
# lst = []
# for i in range(1, 100001):
#     lst.append(i)
#
# answers = []
# start = time()
# for j in lst:
#     answers.append(lst[ternary_search(j, lst)] == j)
# print(time() - start)
# print(all(answers))
#
# answers = []
# start = time()
# for j in lst:
#     answers.append(j in lst)
# print(time() - start)
# print(all(answers))

