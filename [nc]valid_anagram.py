class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t): return False
        sCount = {}
        for char in s:
            sCount[char] = sCount.get(char, 0) + 1
        for char in t:
            sCount[char] = sCount.get(char, 0) - 1
            if sCount[char] < 0: 
                return False
        return True

def main():
    program = Solution()
    # s = "jar"
    # t = "jam"
    s = "racecar"
    t = "carrace"
    print (program.isAnagram(s, t))

if __name__ == "__main__":
    main()