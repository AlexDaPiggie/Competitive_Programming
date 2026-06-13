class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        if not matrix: return False
        row, col = len(matrix), len(matrix[0])
        left, right = 0, row * col - 1

        while left <= right: 
            mid = left + (right - left) // 2
            i = mid // col
            j = mid % col
            num = matrix[i][j]
            if num == target: 
                return True
            elif num < target:
                left = mid + 1
            else: 
                right = mid - 1
        return False 
    
alex = Solution()


matrix = [[1,2,4,8],[10,11,12,13],[14,20,30,40]]
target = 15 # False 
matrix = [[1,2,4,8],[10,11,12,13],[14,20,30,40]]
target = 10 # True

matrix = [[0,1,2,3,4],[5,6,7,8,9]]
target = 8
print (alex.searchMatrix(matrix, target))