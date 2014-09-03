import subprocess
import sys

with open('queries', 'r') as f:
  content = f.read().splitlines()
  for i in range(3):
    for q, columns in  zip(content[::2], content[1::2]):
        columns = columns.strip().split(' ')
        if len(columns) < 16:
            continue

        counts = ', '.join(map(lambda x: "count({})".format(x), columns))

        for i in [0, 2399909, 4798438, 7200456, 9598593, 12000324, 14400643, 16800516, 19201251, 21602403]:
            query = 'SELECT {} FROM LINEITEM WHERE L_ORDERKEY >= {}'.format(counts, i)
#            print '{}, '.format(i),
#            sys.stdout.flush()
#            subprocess.call(['bash', 'mysql_query.sh', query])
#            print ', ',
            sys.stdout.flush()
            subprocess.call(['bash', 'psql_query.sh', query.lower()])
            print
            sys.stdout.flush()
