import csv
import subprocess

def throughput(row):
    return (float(2553384000) / float(row[3])) * (10**9 / 1024 / 1024)

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

for suffix in ['hdd', 'ssd']:
    with open('read_offset_{}.csv'.format(suffix), 'r') as csvfile:
        reader = csv.reader(csvfile)
        rows = [row for row in reader]
        groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

        read_throughput = 'read_offset'
        output = list()
        for group in groups:
            batch, families = (group[0][1], group[0][0].split('_')[1])
            offset = 1 - round(float(group[0][2]) / 23996604, 1)
            avg_time = avg([int(g[3]) for g in group]) / 1000000000
            output.append((int(families), offset, float(avg_time)))

        with open('{}_{}.dat'.format(read_throughput, suffix), 'w+') as f:
            i = 0
            for x in sorted(output):
                f.write('{} {} {}\n'.format(*x))
                i = (i + 1) % 10
                if i == 0:
                    f.write('\n')

subprocess.call(['gnuplot', 'read_offset.plot'])
