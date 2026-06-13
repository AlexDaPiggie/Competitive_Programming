class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        result = []
        if len(nums) < 3: return []
        nums.sort()
        for i, num in enumerate(nums):
            if num > 0: break
            if i > 0 and num == nums[i - 1]: continue
            left, right = i + 1, len(nums) - 1
            while left < right:
                threeSum = num + nums[left] + nums[right]
                if threeSum == 0:
                    result.append([num, nums[left], nums[right]])
                    left += 1
                    right -= 1
                    while left < right and nums[left] == nums[left - 1]: left += 1
                    while left < right and nums[right] == nums[right + 1]: right -= 1

                elif threeSum < 0:
                    left += 1
                else: 
                    right -= 1 
        return result
    
alex = Solution()

nums = [1,-2,0] #[]
nums = [2,-3,0,-2,-5,-5,-4,1,2,-2,2,0,2,-4]
nums = [-1,0,1,2,-1,-4] #[-1,0,1][-1,2,-1]
nums = [-1,0,1,1,0,0,1,0,1] #[-1,0,1][0,0,0]

# '''DEBUG'''
# nums = [-1,0,1,2,-1,-4,-2,-3,3,0,4] 
# expected = [[-4,0,4],[-4,1,3],[-3,-1,4],[-3,0,3],[-3,1,2],[-2,-1,3],[-2,0,2],[-1,-1,2],[-1,0,1]]
# print (len(alex.threeSum(nums)) == len(expected))
# print (len(alex.threeSum(nums)) > len(expected))
# print (len(alex.threeSum(nums)) < len(expected))

print (alex.threeSum(nums))