class Solution:
    def isPalindrome(self, s: str) -> bool:
        if len(s) <= 1: return True
        string = ""
        for char in s:
            if char.isalnum():
                string += char.lower()

        if len(string) <= 1: return True
        for i in range (len(string) // 2):
            if string[i] != string[-1 - i]:
                return False
                
        return True

alex = Solution()
s = "Was it a car or a cat I saw?" #True
s = "" #True
s = None #True
s = "?><>?<" #True
s = " " #True
s = "0z;z   ; 0" #True
print (alex.isPalindrome(s))