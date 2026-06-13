from collections import defaultdict
class Solution:
    def twoSum(self, numbers: list[int], target: int) -> list[int]:
        num_store = defaultdict(int)
        for i in range (len(numbers)):
            num = numbers[i]
            if num not in num_store:
                num_store[target - num] = i + 1
            else:
                return [num_store[num], i + 1]

alex = Solution()
numbers = [1,2,3,4]
target = 3 #1,2

numbers = [3,4,1,2]
target = 3 #3,4

numbers = [0,3,1]
target = 3 #1,2

numbers = []
for num in range (1, 10001):
    numbers.append(num)
target = 10001

from time import perf_counter
start = perf_counter()
print (alex.twoSum(numbers, target))
time1 = perf_counter() - start
print (time1 * 1000)