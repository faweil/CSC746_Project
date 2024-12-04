"""

E. Wes Bethel, Copyright (C) 2022

October 2022

Description: This code loads a .csv file and creates a 3-variable plot

Inputs: the named file "runtimeQuickSort.csv"

Outputs: displays a chart with matplotlib

Dependencies: matplotlib, pandas modules

Assumptions: developed and tested using Python version 3.8.8 on macOS 11.6

"""

import pandas as pd
import matplotlib.pyplot as plt


fname = "runtimeQuickSort.csv"
df = pd.read_csv(fname, comment="#")
print(df)

var_names = list(df.columns)

print("var names =", var_names)

# split the df into individual vars

problem_sizes = df[var_names[0]].values.tolist()
conc_1  = df[var_names[1]].values.tolist()
conc_4  = df[var_names[2]].values.tolist()
conc_9  = df[var_names[3]].values.tolist()
conc_15 = df[var_names[4]].values.tolist()
conc_40 = df[var_names[5]].values.tolist()
conc_60 = df[var_names[6]].values.tolist()

plt.title("quickSort-openMP: Runtime across varying levels of concurrency & problem sizes")

xlocs = [i for i in range(len(problem_sizes))]

plt.xticks(xlocs, problem_sizes) 

plt.plot(conc_1, color="orange", linestyle="-.")
plt.plot(conc_4, "g-.")
plt.plot(conc_9, "r-o")
plt.plot(conc_15, "y-^")
plt.plot(conc_40, "m-*")
plt.plot(conc_60, "b-x")


plt.xlabel("Problem Sizes in million (size of array)")
plt.ylabel("Runtime in ms")

varNames = [var_names[1], var_names[2], var_names[3], var_names[4], var_names[5], var_names[6]]

plt.legend(varNames, loc="best")

plt.grid(axis='both')

plt.show()

# EOF