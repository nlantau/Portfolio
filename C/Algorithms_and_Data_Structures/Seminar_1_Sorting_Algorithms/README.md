# Testing Algorithms - Setup
I've created a couple of Python scripts to test my C programs and their algorithms

[Plott_results](https://github.com/nlantau/Portfolio/tree/master/C/Algorithms_and_Data_Structures/Seminar_1_Sorting_Algorithms/Python/Plott_results)
was used on MacOS.

[Plott_results](https://github.com/nlantau/Portfolio/tree/master/C/Algorithms_and_Data_Structures/Seminar_1_Sorting_Algorithms/Python/Plott_results_WSL)
was used on Windows 10 with WSL

## Python - controll_sort.py
+ Script that checks:
    1. If "sorted" textfile is sorted
    2. If number occurence in sorted text file equals the original file

You can find the script [here](https://github.com/nlantau/Portfolio/blob/master/C/Datastructures_and_Algorithms/Seminar_1/Python/Plott_results/controll_sort.py)

## Python - tester.py
+ Script that executes C program with number files in specified folder
+ All the files will be passed, one at a time, to the C program for as many iterations as specified
+ Resulting output is programmed in the C executable to be sent to STDERR

Having it this way allows the C programs output to be redirected to a textfile containing
the results, without any text from STDOUT (which is used by the Python script to display progress)

You can find the script [here](https://github.com/nlantau/Portfolio/blob/master/C/Algorithms_and_Data_Structures/Seminar_1_Sorting_Algorithms/Python/Plott_results/tester.py)

## Python - plotter.py
+ Script that plots results using matplotlib

You can find the script [here](https://github.com/nlantau/Portfolio/blob/master/C/Algorithms_and_Data_Structures/Seminar_1_Sorting_Algorithms/Python/Plott_results/plotter.py)
## How to commence test - Python

1. Compile C program

```shell
gcc driver_main.c Templates/read_file.c QS_rec/QS_rec.c -O2 -Wall -o qs_reca
```
2. Run Python tester.py

python tester.py 'C-binary' 'Resulting textfile' 'iterations'
```shell
python tester.py qs_reca QS_Rec_1000_iter.CSV 1000
```
3. Run Python plotter.py
```shell
python plotter.py QS_Rec_1000_iter.CSV
```

## Important!
+ Don't forget to activate conda/venv containing:
    + matplotlib
    + numpy
    + pandas
    + colorama
    + sys
    + os
    + subprocess

