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

## Shell Script - "Old"

#### The shell script works as follows:
+ a for-each loop calls and run the executable C program and passes in a textfile (hard coded)
+ Resulting output is programmed in the C executable to be sent to STDERR
+ The shell scripts output is sent to STDOUT

Having it this way allows the C programs output to be redirected to a textfile containing
the results, without any text from STDOUT (which is used by the shell script to display progress)

## How to compile
gcc driver_main.c Templates/read_file.c QS_rec/QS_rec.c -O2 -o qs_reca

## How to commence test - Shell
./tester.zsh 2> Results/QS_loop_10iterations_each.txt

The "2>" means that STDERR is sent to whatever is on its right hand side (results textfile)

## Testing process
+ Example:
    + 10 iterations of Quick Sort with 100 numbers
    + 10 iterations of Quick Sort with 1000 numbers
    + 10 iterations of...
    + and so on
