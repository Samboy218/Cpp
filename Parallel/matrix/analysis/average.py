f = open('results2Avg.csv', 'w')
for lines in zip(open('results3.csv', 'r'), open('results4.csv', 'r')):
    print(lines)
    vals1 = lines[0].strip().split(',')
    vals2 = lines[1].strip().split(',')
    if (vals1[0] != vals2[0] or vals1[1] != vals2[1]):
        print('fuck')
        exit()
    average = (float(vals1[2]) + float(vals2[2]))/2
    f.write("{},{},{}\n".format(vals1[0], vals1[1], average))

