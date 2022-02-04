# Testing Algorithms - Setup
To save time, I've created a shell script that executes the C programs in loops.
And to save frustration, I've also create Python script that is much better at testing the C program.

## Python - tester.py
+ Script that executes C program with all files containing different amount of numbers

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

