class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        if len(nums) <= 1: return []
        number_store = {}
        for i in range (len(nums)):
            if nums[i] not in number_store:
                number_store[target - nums[i]] = i
            else:
                return [number_store[nums[i]], i]
        return []
    
def main():
    nums = [3,4,5,6]
    target = 7
    alex = Solution()
    print (alex.twoSum(nums, target))

if __name__ == "__main__":
    main()