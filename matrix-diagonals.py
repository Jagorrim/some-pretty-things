# task - https://stepik.org/lesson/416757/step/9?unit=406265
n, m = map(int, input().split())
matrix = [[0] * m for _ in range(n)]
num = 0
for start in range(0, m):
    point = [0, start]
    num += 1
    matrix[point[0]][point[1]] = num
    for _ in range(min(n - 1, start)):
        point[0] += 1
        point[1] -= 1
        num += 1
        matrix[point[0]][point[1]] = num

for start in range(1, n):
    point = [start, m - 1]
    num += 1
    matrix[point[0]][point[1]] = num
    while point[0] < n - 1 and point[1] > 0:
        point[0] += 1
        point[1] -= 1
        num += 1
        matrix[point[0]][point[1]] = num

for line in matrix:
    print(''.join([str(item).ljust(3) for item in line]))
