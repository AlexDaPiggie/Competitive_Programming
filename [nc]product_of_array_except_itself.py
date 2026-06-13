class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        left, right = [1]*len(nums), [1]*len(nums)
        result = []
        for i in range (1, len(nums)):
            left[i] = left[i - 1] * nums[i - 1]
            right[i] = right[i - 1] * nums[len(nums) - i]
        for i in range (len(nums)):
            result.append(left[i] * right[len(nums) - i - 1])
        return result
    
nums = [1,2,4,6]
alex = Solution()
print (alex.productExceptSelf(nums))