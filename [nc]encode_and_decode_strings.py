class Solution:

    def encode(self, strs: list[str]) -> str:
        if not strs:
            return ""
        result = ""
        for string in strs:
            result += str(len(string)) + "@" + string
        return result
    def decode(self, s: str) -> list[str]:
        if s == "":
            return []
        if s == "0@":
            return [""]
        result = []
        at_position = s.find("@")
        end_str = -1
        while end_str != len(s) - 1:
            # print (f"DEBUG: end_str: {s[end_str]} and at_position: {s[at_position]}")
            length = int(s[end_str + 1 : at_position])
            if length == 0:
                result.append("")
            else:
                string = s[at_position + 1: at_position + length + 1]
                result.append(string)
            # print (f"DEBUG: length = {length}, string = {string}")
            end_str = at_position + length
            at_position = s.find("@", end_str + 1) 
            #if length = 0 and start finding from end_str, program will have inf loop

        return result