class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        if len(prices) <= 1: return 0
        buy = float("inf")
        profit = 0
        for sell in prices: 
            if buy > sell: 
                buy = sell
                continue
            profit = max(profit, sell - buy)
        return profit
    
alex = Solution()
prices = [1,10,5,7,6,1] #9
prices = [10,8,7,5,2] #0
prices = [10,1,5,6,7,1] #6
prices = [5,1,7,6,1,10] #9
print (alex.maxProfit(prices))