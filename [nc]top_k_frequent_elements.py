class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        if k > len(nums): return []
        result = []
        freq = {}
        bucket = [[] for _ in range (len(nums) + 1)]
        for num in nums:
            freq[num] = freq.get(num, 0) + 1
        for key, value in freq.items():
            bucket[value].append(key)
        for i in range (len(bucket) - 1, 0, -1):
            for num in bucket[i]:
                result.append(num)
                if len(result) >= k:
                    return result