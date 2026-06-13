from time import perf_counter
import valid_anagram

def time_measure (function, trials: int = 10):
    total = 0.0
    for _ in range(trials):
        start = perf_counter()
        function
        total += perf_counter() - start
    return total / trials

alex = valid_anagram.main()
print (f"{time_measure(alex, trials = 10) * 1000: .10f}")