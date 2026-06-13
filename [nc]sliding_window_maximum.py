from collections import deque
class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        if not nums: return []
        if k == 1: return nums
        q = deque()
        result = []
        start = 0
        for idx, char in enumerate(nums):
            while q and char > q[-1]:
                q.pop()
            q.append(char)
            if idx + 1 >= k:
                result.append(q[0])
                if nums[start] == q[0]:
                    q.popleft()
                start += 1
        return result

alex = Solution()
nums = [1,2,1,0,4,2,6]
k = 3 #2,2,4,4,6

nums = [1,2,3,2,3,3,6,4,5]
k = 3 #3,3,3,3,6,6,6

nums = [3,2,1,2,2,4,5,6]
k = 3 #3,2,2,4,5,6

nums = [9,8,7,6,11,10,9,8,7]
k = 3 #

print (alex.maxSlidingWindow(nums, k))