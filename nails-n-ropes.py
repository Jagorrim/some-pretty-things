# task - https://acmp.ru/index.asp?main=task&id_task=121

n = int(input())
 
nums = [int(i) for i in input().split()]
nums.sort()
 
dp = [0] * n
dp[0] = 10 ** 9
dp[1] = nums[1] - nums[0]
# print(data)
 
for index in range(2, n):
    dp[index] = min(
        dp[index - 1],
        dp[index - 2]
    ) + (nums[index] - nums[index - 1])
 
print(dp[-1])
