class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) <= 1: return len(s)
        result, start = 1, 0
        store = {s[0]}
        for end in range (1, len(s)):
            char_end = s[end]
            while char_end in store: 
                store.remove(s[start])
                start += 1
            store.add(char_end)
            length = end - start + 1
            result = max(result, length)
        return result 

alex = Solution()
s = "xxxx" #1
s = "abcabcbb" #3
s = "zxyzxyz" #3
s = "dvdf" #3
s = "abcdaabcdefg" #7
s = "abaabc" #3
s = "ohvhjdml" #6
s = "abfdjakfaaabcdefghj" #9
from time import perf_counter
start = perf_counter()
for _ in range (100): 
    alex.lengthOfLongestSubstring(s)
time = perf_counter() - start
print (f"Time: {time * 1000 : .10f} ms")
print (alex.lengthOfLongestSubstring(s))