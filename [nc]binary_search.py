class Solution:
    def search(self, nums: list[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right: 
            mid = left + (right - left) // 2
            if nums[mid] == target:
                return mid 
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return -1

alex = Solution()    

nums = [-1,0,2,4,6,8]
target = 3 #-1

nums = [-1,0,2,4,6,8]
target = 4 #3
print (alex.search(nums, target))
