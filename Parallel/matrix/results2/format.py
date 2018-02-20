
with open('results', 'r') as f1:
    with open('results.csv', 'w') as f2:
        for line in f1:
            threads = line.split(':')[-1].strip()
            line = f1.readline()
            size = line.split(':')[-1].strip()
            line = f1.readline()
            time = line.split(':')[-1].strip()
            f2.write("{},{},{}\n".format(threads, size, time))
