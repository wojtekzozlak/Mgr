import csv
import subprocess
import sys

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

with open(sys.argv[1], 'r') as csvfile:
    reader = csv.reader(csvfile)
    rows = [row for row in reader]
    groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

    output = list()
    for g in groups:
        z = g[0]
        z[0] = round(1 - float(z[0])/24000000, 2)
#        z[1] = z[1].strip()
        z[2] = avg(x[2] for x in g)
        z[1] = avg(x[1] for x in g)
        output.append(z)
    for z in sorted(output):
        print '{}, {}, {}'.format(*z)
