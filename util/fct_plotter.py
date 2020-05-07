#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys


def fct(filename):
    df = pd.read_csv(filename, header=None)
    df = df.groupby([0])[4].max()

    y = np.arange(0, 1.001, 0.001)
    x = [np.percentile(df, i * 100) / 1000000.0 for i in y]

    plt.plot(x, y)
    plt.grid(True)

    plt.xlabel('$x$ - flow completion time [sec]')
    plt.ylabel('Probability (flow completion time > $x$)')

    plt.savefig('../results/fct_cdf.pdf', quality=100)


if __name__ == '__main__':
    assert (len(sys.argv) == 2)
    fct(sys.argv[1])
