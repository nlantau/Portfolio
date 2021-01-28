# Testing Algorithms - Setup
I've created a couple of Python scripts to test my C programs and their algorithms

## Python - controll_sort.py
+ Script that checks:
    1. If "sorted" textfile is sorted
    2. If number occurence in sorted text file equals the original file

## Python - tester.py
+ Script that executes C program with number files in specified folder
+ All the files will be passed, one at a time, to the C program for as many iterations as specified
+ Resulting output is programmed in the C executable to be sent to STDERR

Having it this way allows the C programs output to be redirected to a textfile containing
the results, without any text from STDOUT (which is used by the Python script to display progress)

## Python - plotter.py
+ Script that plots results using matplotlib

[Link to number files](https://github.com/nlantau/DT256CHT20/tree/main/numb_files)

[Link to Python
Tester Script](https://github.com/nlantau/DT256CHT20/blob/main/Python/Plott_results/tester.py)

[Link to Python
Plotter Script](https://github.com/nlantau/DT256CHT20/blob/main/Python/Plott_results/plotter.py)

## How to commence test - Python

1. Compile C program

```shell
gcc driver_main.c Templates/read_file.c QS_rec/QS_rec.c -O1 -o qs_reca
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

