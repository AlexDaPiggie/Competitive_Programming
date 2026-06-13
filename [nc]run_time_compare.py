import numpy as np
class Solution:
    def first_function(self):
        for index, value in np.ndenumerate(matrix):
            yield (index, value)

    def second_function(self):
        for index in np.ndindex(matrix.shape):
            yield (index, matrix[index])
            

matrix = np.arange (1, int(1e7))
alex = Solution()

#======================= FUNCTIONS END ===================================
                

#Tools
from time import perf_counter
from time import sleep
import argparse
import os
from rich.console import Console

console = Console()

os.system('cls')

#Format color
def print_color (text = "", end = "\n", style = "sea_green2"):
    console.print(f"{text}", end = end, style = style)

#Show progress bar
def progress (prog, total):
    percent = 100 * (prog / total) 
    bar = '█' * int(percent) + '-' * int((100 - percent))
    print_color (f"\r[bold plum1]│[/bold plum1]{bar}[bold plum1]│[/bold plum1] [bold steel_blue1]{percent:.2f}%[/bold steel_blue1]", end = "\r")

#Modes to choose from 
def parse():
    mode = argparse.ArgumentParser()
    mode.add_argument("--t", action = "store_true", )
    mode.add_argument("--p", action = "store_true")
    mode.add_argument("--n", dest ="num", type = int)
    return mode.parse_args()

#Compare time performance
first = second = iter = 0
minTime1, maxTime1, avg1 = 1e10, 0.0, 0.0
minTime2, maxTime2, avg2 = 1e10, 0.0, 0.0

args = parse()
show_time = args.t
show_progress = args.p

trials = 1000
if args.num:
    trials = int(args.num)
    

for iter in range (1, trials + 1):

    #Estimate each run time
    start = perf_counter()
    for _ in range (1000):
        alex.first_function()

    time1 = perf_counter() - start
    minTime1 = min(minTime1, time1)
    maxTime1 = max(maxTime1, time1)
    avg1 += time1 / trials

    start = perf_counter()
    for _ in range (1000):
        alex.second_function()
    time2 = perf_counter() - start
    minTime2 = min(minTime2, time2)
    maxTime2 = max(maxTime2, time2)
    avg2 += time2 / trials

    #Update winning score
    if time1 < time2: 
        first += 1
    else: 
        second += 1

    #Display

    if not show_progress:
        print_color (f"\nTEST: time1 = [bold steel_blue1]{time1 * 1000: .6f} ms[/bold steel_blue1]")
        print_color (f"TEST: time2 = [bold steel_blue1]{time2 * 1000: .6f} ms[/bold steel_blue1]")

    if not show_time:
        progress(iter, trials)

#Format output
if not (show_progress or show_time):
    sleep(0.25)
    os.system('cls')

print_color()
print_color(f"\n                                   [bold steel_blue1]DONE TESTING!!![/bold steel_blue1]")
print_color ("                ┌──────────────────────────────────────────────────────────────┐ ")

if first > second:
    print_color ("                │       [bold plum1]REPORT: FIRST function has BETTER performance[bold plum1]          │")
    print_color ("                │                                                              │")
    print_color (f"                │       REPORT: [bold plum1]WINNING RATE[/bold plum1] of [bold plum1]FIRST[/bold plum1] function is: [bold plum1]{first / trials * 100:5.1f}%[/bold plum1]      │")


else: 
    print_color ("                │       [bold underline bold plum1]REPORT: SECOND function has BETTER performance[/bold underline bold plum1]         │")
    print_color ("                │                                                              │")
    print_color (f"                │       REPORT: [bold plum1]WINNING RATE[/bold plum1] of [bold plum1]SECOND[/bold plum1] function is: [bold plum1]{second/ trials* 100:5.1f}%[/bold plum1]     │")

print_color ("                │                                                              │")
print_color (f"                │       REPORT: RUN TIME OF FIRST FUNCTION:                    │\r")                  
print_color (f"\r                │       ┌───────────────────────┐                              │\n"
       f"                │       │ min     = [bold steel_blue1]{minTime1* 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       │ max     = [bold steel_blue1]{maxTime1* 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       │ average = [bold steel_blue1]{avg1 * 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       └───────────────────────┘                              │\r")

print_color (f"\r                │       REPORT: RUN TIME OF SECOND FUNCTION:                   │\r")
print_color (f"\r                │       ┌───────────────────────┐                              │\n"
       f"                │       │ min     = [bold steel_blue1]{minTime2* 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       │ max     = [bold steel_blue1]{maxTime2* 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       │ average = [bold steel_blue1]{avg2 * 1000: 8.3f} ms[/bold steel_blue1] │                              │\n"
       f"                │       └───────────────────────┘                              │")
print_color (f"                └──────────────────────────────────────────────────────────────┘")
