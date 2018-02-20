import matplotlib.pyplot as plt

runs = {}
for line in open('results2Avg.csv', 'r'):
    vals = line.strip().split(",")
    threads = int(vals[0])
    size = int(vals[1])
    time = float(vals[2])
    try:
        runs[threads].append((size, time))
    except:
        runs[threads] = []
        runs[threads].append((size, time))

colors = {1:'b', 2:'g', 4:'r', 8:'c', 16:'m', 28:'y'}
fig = plt.figure()

ax1 = fig.add_subplot(221)
ax1.set_ylabel("runtime (s)")
#ax1.legend(loc='top left', borderpad=.1)
ax1.set_xlabel("matrix size")
for run in sorted(list(runs.keys())):
    #plot speed data
    x = [ item[0] for item in runs[run]]
    y = [ item[1] for item in runs[run]]
    print(x)
    print(y)
    ax1.plot(x, y, label="{} threads".format(run), c=colors[run])

ax2 = fig.add_subplot(222)
ax2.set_xlabel("matrix size")
ax2.set_ylabel("speedup")
ax3 = fig.add_subplot(223)
ax3.set_xlabel("matrix size")
ax3.set_ylabel("efficiency")
#now calculate speedup and efficiency
serialTime = [x[1] for x in runs[1]]
for run in sorted(list(runs.keys())):
    runtime = [x[1] for x in runs[run]]
    speedup = [x[0]/x[1] for x in zip(serialTime, runtime)]
    efficiency = [x/run for x in speedup]
    sizes = [x[0] for x in runs[run]]
    ax2.plot(sizes, speedup, label="{} threads".format(run), c=colors[run])
    ax3.plot(sizes, efficiency, label="{} threads".format(run), c=colors[run])

fig.legend(*fig.axes[0].get_legend_handles_labels(), loc='center', bbox_to_anchor=[.6, .35])
plt.suptitle("Parallel Matrix Multiplication")
plt.show()

