import csv
import subprocess

def throughput(row):
    return (float(row[4]) / float(row[1])) * (10**9 / 1024 / 1024)

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

for suffix in ['ssd', 'hdd']:
    with open('write_bench_{}.csv'.format(suffix), 'r') as csvfile:
        reader = csv.reader(csvfile)
        rows = [row for row in reader]
        groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

        write_throughput = 'write_throughput'
        output = list()
        for group in groups:
            batch, families = group[0][0].split('_')
            avg_time = avg([throughput(g) for g in group])
            output.append((int(batch), int(families), float(avg_time)))

        with open('{}_{}.dat'.format(write_throughput, suffix), 'w+') as f:
            f.write("# X Y Z\n")
            i = 0
            for x in sorted(output):
                i = (i + 1) % 5
                f.write("{} {} {}\n".format(*x))
                if i == 0:
                    f.write('\n')

subprocess.call(['gnuplot', 'write_throughput.plot'])
