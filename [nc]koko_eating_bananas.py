import math
class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        left, right = 1, max(piles)
        result = right
        while left <= right:
            mid = left + (right - left) // 2
            hour = 0
            for banana in piles:
                hour += math.ceil(float(banana) / mid)
            # print (f"DEBUG: hour = {hour} and k = {mid}")
            if hour <= h:
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        return result

alex = Solution()

piles = [1,4,3,2]
h = 9 #2

piles = [25,10,23,4]
h = 4 #25

piles = [1,4,3,2]
h = 9 #2

print (alex.minEatingSpeed(piles, h))