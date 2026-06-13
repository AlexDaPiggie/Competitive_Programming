from collections import defaultdict
class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        if len(strs) <= 1: return [strs]
        result = defaultdict(list)
        for string in strs:
            freq = [0] * 26
            for char in string:
                freq[ord(char) - ord('a')] += 1
            result[tuple(freq)].append(string)
        return list(result.values())


def main():
    strs = ["act","pots","tops","cat","stop","hat"]
    alex = Solution()
    print (alex.groupAnagrams(strs))

if __name__ == "__my_method__": main()