# task - https://stepik.org/lesson/416757/step/10?unit=406265

n, m = map(int, input().split())
matrix = [[None] * m for _ in range(n)]
horizontal, vertical = m, n - 1

line = ['h', 'v']
line_n = 0 % 2

turn = [1, 1, -1, -1]
turn_n = 0 % 4

cur_point = [0, 0]
num = 1
while num <= n * m:
    if line[line_n] == 'h':
        nums = list(range(num, num + horizontal))
        for num in nums:
            matrix[cur_point[0]][cur_point[1]] = num
            cur_point[1] += turn[turn_n]

        cur_point[1] -= turn[turn_n]  # Убираем лишнее

        num = nums[-1] + 1
        cur_point[0] += turn[turn_n]
        horizontal -= 1

    else:
        nums = list(range(num, num + vertical))
        for num in nums:
            matrix[cur_point[0]][cur_point[1]] = num
            cur_point[0] += turn[turn_n]

        cur_point[0] -= turn[turn_n]  # Убираем лишнее

        num = nums[-1] + 1
        cur_point[1] += turn[turn_n] * -1
        vertical -= 1

    turn_n = (turn_n + 1) % 4
    line_n = (line_n + 1) % 2


for line in matrix:
    print(''.join([str(item).ljust(3) for item in line]))
