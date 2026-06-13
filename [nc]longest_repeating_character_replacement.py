from collections import defaultdict
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        result = freq = start = 0
        count = defaultdict(str)
        for end in range (len(s)): 
            count[s[end]] = count.get(s[end], 0) + 1
            freq = max(freq, count[s[end]])
                
            while (end - start + 1) - freq > k:
                count[s[start]] -= 1
                start += 1
                freq = max(count.values())

            result = max(result, end - start + 1)
        return result 
    
alex = Solution()

s = "XYYX" #4
k = 2
s = "ABAB" #1
k = 0
s="AAABABB" #5
k = 1

print (alex.characterReplacement(s, k))
