from collections import defaultdict
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if len(t) > len(s): return ""
        count, window = defaultdict(int), defaultdict(int)
        match, min_length = 0, len(s) + 1
        min_length = len(s) + 1
        result = []
        for char in t: 
            count[char] += 1

        start, match, target = 0, 0, len(count)

        for end in range (len(s)):
            char_end = s[end]
            window[char_end] += 1
            if count[char_end] != 0 and window[char_end] == count[char_end]:
                match += 1
            while match >= target:
                if end - start + 1 < min_length:
                    min_length = end - start + 1
                    result = [start, end]
                char_start = s[start]
                if count[char_start] != 0 and window[char_start] == count[char_start]:
                    match -= 1
                window[char_start] -= 1
                start += 1
        if not result: return ""
        start, end = result
        return s[start : end + 1]

alex = Solution()
s = "OUZODYXAZV"
t = "XYZ" #YXAZ

s = "abc"
t = "abc" #abc

s = "adfdkjfljbc"
t = "abc" #adfdkjfljbc
print (alex.minWindow(s,t ))

