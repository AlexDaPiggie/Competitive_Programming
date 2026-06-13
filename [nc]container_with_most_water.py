class Solution:
    def maxArea(self, heights: list[int]) -> int:
        if len(heights) <= 1: return -1
        left, right = 0, len(heights) - 1
        result = 0
        while left < right:
            if heights[left] <= heights[right]:
                area = heights[left] * (right - left)
                result = max(result, area)
                left += 1
            else:
                area = heights[right] * (right - left)
                result = max(result, area)
                right -= 1
        return result
     
height = [1,8,6,2,5,4,8,3,7]
height = [1,2] #1
height = [1,2,3] #2
height = [3,1,2] #4
alex = Solution()
print (alex.maxArea(height))