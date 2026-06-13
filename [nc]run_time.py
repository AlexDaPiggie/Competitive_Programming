import encode_and_decode_strings
from time import perf_counter

def time (function, trials: int = 10):
    total = 0.0
    for _ in range (trials):
        start = perf_counter()
        function
        total += perf_counter() - start
    return total / trials * 1000

def program ():
    # input = ["Hello", "World", "Alex"]
    input = ["", ""]
    encode = encode_and_decode_strings.Solution().encode(input)
    print ("Encoded string: ", encode)
    decode = encode_and_decode_strings.Solution().decode(encode)
    print ("Decoded string:", decode)

program()
print (f"{time(program, trials = 10): .10f} ms")