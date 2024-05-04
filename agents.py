# task - https://acmp.ru/index.asp?main=task&id_task=500
n = int(input())
 
nums = [int(i) for i in input().split()]
data = [[nums[i], nums[i + 1]] for i in range(0, n * 2, 2)]
data.sort(key=lambda item: item[0])
dp = [0] * n
dp[0] = 10 ** 9
dp[1] = data[1][1]
# print(data)
 
for index in range(2, n):
    dp[index] = min(
        dp[index - 1],
        dp[index - 2]
    ) + data[index][1]
 
    # dp[index] = min(
    #     dp[index - 1],
    #     dp[index - 2]
    # ) + data[index][1]
 
print(dp[-1])
 
# 6
# 1 1 1 3 1 1 1 2 1 4 1 5
