import csv
import subprocess

def throughput(row):
    return (float(2130537436) / float(row[3])) * (10**9 / 1024 / 1024)

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

with open('blocks.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    rows = [row for row in reader]

    output = list()
    for row in rows:
        batch, families = row[0].split('_')
        output.append((int(batch), int(families), int(row[3])))

with open('blocks.dat', 'w+') as f:
    i = 0
    for x in sorted(output):	
        f.write('{} {} {}\n'.format(*x))
        i = (i + 1) % 5
        if i == 0:
            f.write('\n')

subprocess.call(['gnuplot', 'blocks.plot'])
