def binary_search (nums: list[int], target: int) -> int: 
    first, last = nums[0], nums[-1]
    if target < first or target > last: return -1
    if target == first: return 0
    if target == last: return len(nums) - 1
    left, right = 1, len(nums) - 2
    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else: 
            right = mid - 1

    return -1
class Solution:
    def search(self, nums: list[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        index = 0
        while left <= right: 
            if nums[left] <= nums[right]:
                index = left
                break
            mid = left + (right - left) // 2
            if nums[mid] >= nums[left]:
                left = mid + 1
            else: 
                right = mid
        if index == 0: 
            return binary_search(nums, target)
        else: 
            s1 = nums[:index] #right
            s2 = nums[index:] #left
            if target > s2[-1]:
                return binary_search(s1, target)
            position = binary_search(s2, target)
            if position == -1: return -1
            else: return index + position


alex = Solution()

nums = [3,4,5,6,1,2]
target = 1 #4

nums = [5,6,1,2,3,4]
target = 1 #2

nums = [1,2,3,4]
target = 5 #0

nums = [1,3]
target = 3 #-1
print (alex.search(nums, target))
