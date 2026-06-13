import group_anagrams
from time import perf_counter
def time_measure (function, trials: int = 10):
    for _ in range (trials):
        total = 0.0
        start = perf_counter()
        function
        total += perf_counter() - start
    return total / trials

program = group_anagrams
print (f"{time_measure(program.main()) * 1000: .10f} ms")
print (f"{time_measure(program.other_method()) * 1000: .10f} ms")