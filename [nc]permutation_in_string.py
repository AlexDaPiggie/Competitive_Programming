from collections import defaultdict
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2): return False
        count, window = [0] * 26, [0] * 26
        match = 0

        for i in range (len(s1)):
            count[ord(s1[i]) - ord('a')] += 1
            window[ord(s2[i]) - ord('a')] += 1
        for i in range (26):
            if window[i] == count[i]: 
                match += 1
        if match == 26:
            return True
        
        # print (f"DEBUG: \n count = {count}, \n \
        #        \r window = {window} \n \
        #        \r match = {match}")

        #sliding window
        start = 0
        for end in range (len(s1), len(s2)):
            asc_start = ord(s2[start]) - ord('a')
            start += 1
            if window[asc_start] == count[asc_start]: 
                match -= 1
            window[asc_start] -= 1
            if window[asc_start] == count[asc_start]:
                match += 1

            asc_end = ord(s2[end]) - ord('a')
            if window[asc_end] == count[asc_end]:
                match -= 1
            window[asc_end] += 1
            if window[asc_end] == count[asc_end]: 
                match += 1
            
            if match == 26: 
                return True
            # print (f"DEBUG: \n start = {start} and end = {end} \n \
            #        \r count = {count}, \n \
            #        \r window = {window} \n \
            #        \r match = {match}\n")
        return False


alex = Solution()

s1 = "abc"
s2 = "caab" #False
s1 = "abc"
s2 = "lecaabee" #false
s1 = "abc"
s2 = "lecabee" #true
s1 = "abc"
s2 = "lcabd" #true
print (alex.checkInclusion(s1, s2))