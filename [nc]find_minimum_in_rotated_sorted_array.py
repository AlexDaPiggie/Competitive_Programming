class Solution:
    def findMin(self, nums: list[int]) -> int:
        left, right = 0, len(nums) - 1
        result = nums[left]
        while left <= right:
            if nums[right] >= nums[left]: 
                return nums[left]
            mid = left + (right - left) // 2
            if nums[mid] >= nums[left]:
                left = mid + 1
            else: 
                right = mid
        return result 


alex = Solution()

nums = [3,4,5,6,1,2]
print (alex.findMin(nums)) #1

nums = [4,5,6,7]
print (alex.findMin(nums)) #4
