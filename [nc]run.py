import two_sum
from time import perf_counter

def time_measure (function, *args, trials: int = 10):
    total = 0.0
    for _ in range (trials):
        start = perf_counter()
        function (*args)
        total += perf_counter() - start
    return total / trials

nums = [3,4,5,6]
target = 7
alex = two_sum.Solution()
print (f"{time_measure(alex.twoSum, nums, target, trials = 10)* 1000: .10f}")