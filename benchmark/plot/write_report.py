import csv
import subprocess

def throughput(row):
    return (float(row[4]) / float(row[2])) * (10**9 / 1024 / 1024)

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)


with open('write_bench.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    rows = [row for row in reader]
    groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

    write_throughput = 'write_throughput'
    with open('{}.dat'.format(write_throughput), 'w+') as f:
        f.write("# X Y Z\n")
        for group in groups:
            batch, families = group[0][0].split('_')
            avg_time = avg([throughput(g) for g in group])
            f.write("{} {} {}\n".format(batch, families, avg_time))
    subprocess.call(['gnuplot', '{}.plot'.format(write_throughput)])



    write_breakdown = 'write_breakdown'
    with open('{}.dat'.format(write_breakdown), 'w+') as f:
        for group in groups:
            batch, families = group[0][0].split('_')
            avg_time = avg([g[3] for g in group])
            f.write("{} {} {}\n".format(batch, avg_time, 1 - avg_time))
    subprocess.call(['gnuplot', '{}.plot'.format(write_breakdown)])
