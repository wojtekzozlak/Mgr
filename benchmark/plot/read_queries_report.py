import csv
import subprocess

def avg(l):
    l = [ float(x) for x in l ]
    return sum(l, 0.0) / len(l)

for suffix in ['hdd', 'ssd']:
    with open('read_queries_{}.csv'.format(suffix), 'r') as csvfile:
        reader = csv.reader(csvfile)
        rows = [row for row in reader]
        groups = [rows[n:n+3] for n in range(0, len(rows), 3)]

        queries = {}
        read_throughput = 'read_queries'
        output = list()
        for group in groups:
            batch, families = (group[0][1], group[0][0].split('_')[1])
            avg_time = avg([int(g[5]) for g in group]) / 1000000000
            query = (int(group[0][2]), '"Q{} ({})"'.format(group[0][2], group[0][3]))
            queries[query] = queries.get(query, [])
            queries[query].append((int(families), float(avg_time)))
            output.append((int(families), query, float(avg_time)))

        with open('{}_{}.dat'.format(read_throughput, suffix), 'w+') as f:
            f.write("query 1 2 4 8 16\n")
            for k, q in sorted(queries.iteritems()):
                row = k[1] + ' ' + ' '.join(map(lambda (x, y): str(y), sorted(q)))
                f.write(row + '\n')
                

subprocess.call(['gnuplot', 'read_queries.plot'])
