import os
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns


def printplot(name):
    plt.rcParams["figure.autolayout"] = True

    df = pd.read_csv(os.getcwd() + '\\rapport\\csv\\' + name + '.csv')
    df = df.set_index('n')

    plt.figure(figsize=(19.2, 10.8))
    sns.lineplot(data=df)
    plt.yscale('log')
    plt.xscale('log')
    plt.xlabel('n elements')
    plt.ylabel('time (ms)')
    plt.title(name)
    plt.savefig((os.getcwd() + '\\rapport\\svg\\' + name + '.svg'))


printplot('time-measurement-almost-sorted')
printplot('time-measurement-decreasing')
printplot('time-measurement-increasing')
printplot('time-measurement-random')

