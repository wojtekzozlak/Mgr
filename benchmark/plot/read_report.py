import csv
import subprocess

def throughput(row):
    return (float(2130537436) / float(row[3])) * (10**9 / 1024 / 1024)

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

for suffix in ['hdd']:
    with open('read_bench_{}.csv'.format(suffix), 'r') as csvfile:
        reader = csv.reader(csvfile)
        rows = [row for row in reader]
        groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

        read_throughput = 'read_throughput'
        with open('{}_{}.dat'.format(read_throughput, suffix), 'w+') as f:
            f.write("# X Y Z\n")
            i = 0
            for group in groups:
                i = (i + 1) % 5
                batch, families = (group[0][1], group[0][0].split('_')[1])
                avg_time = avg([throughput(g) for g in group])
                f.write("{} {} {}\n".format(batch, families, avg_time))
                if i == 0:
                    f.write('\n')


subprocess.call(['gnuplot', 'read_throughput.plot'])
