import subprocess
import sys

with open('queries', 'r') as f:
  content = f.read().splitlines()
  for i in range(3):
    for q, columns in  zip(content[::2], content[1::2]):
        columns = columns.strip().split(' ')
        counts = ', '.join(map(lambda x: "count({})".format(x), columns))
        query = 'SELECT {} FROM LINEITEM'.format(counts)

        print '{}, {}, '.format(q, len(columns)),
        sys.stdout.flush()
        subprocess.call(['bash', 'mysql_query.sh', query])
        print ', ',
        sys.stdout.flush()
        subprocess.call(['bash', 'psql_query.sh', query.lower()])
        print
        sys.stdout.flush()
