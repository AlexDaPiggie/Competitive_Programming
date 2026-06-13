class Solution:
    def hasDuplicate(self, nums: list[int]) -> bool:
        store = set()
        for num in nums:
            if num in store:
                return True
            store.add (num)
        return False

nums = [1,2,3,3]
alex = Solution()
print (alex.hasDuplicate(nums))