# nlantau, 2020-12-05

import sys
import os
import subprocess


name = "VEC_IT_allocatorcpp"

path = r"/Users/nlantau/Docs/GitHub/DT256CHT20/Seminar_2/Cpp/./a.out"
csv = r"/Users/nlantau/Docs/GitHub/DT256CHT20/Seminar_2/Cpp/" + name + ".csv"


def main():
    n = [x + 500 for x in range(500, 15000, 500)]
    res = []
    m = [0, 1, 2, 10, 100, 1000, 2000]
    for i in range(1):
        for k in m:
            for num in n:
                result = subprocess.run(
                    [path, str(num), str(k)], stderr=subprocess.PIPE, text=True
                )
                res.append(result.stderr.strip())
    with open(csv, "w") as w:
        for l in res:
            w.writelines(l + "\n")


if __name__ == "__main__":
    main()