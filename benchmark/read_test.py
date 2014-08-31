from __future__ import print_function
import subprocess
import sys


if len(sys.argv) < 3:
  print("USAGE: ", sys.argv[0], " PATH OFFSET")
  sys.exit(0)

path = sys.argv[1]
offset = sys.argv[2]

sizes = [500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
#sizes = [2000]
#offsets = range(0, 10, 1)
offsets = [0]
offset = 0
families = [1,2,4,8,16]
#queries = [1,2,3,4,5,6,7,8,9,10,12,14,15,17,18,19,20]
queries = [0]

rows = 23996604
tests = [ (x, y, z) for x in sizes for y in families for z in queries]

def clear_cache():
    subprocess.call(['sync'])
    with open('/proc/sys/vm/drop_caches', 'w') as f:
        f.write('3')

#for i in range(3):
i = 0
for size, family, query in tests:
    #clear_cache()
    #subprocess.call(['./cat', path + '_' + str(family), str(size), str(int(offset * rows / 10))])
    i = (i + 1) % 5
    print("{} {} ".format(size, family), end='')
    sys.stdout.flush()
    subprocess.call('strace ./cat "{}/{}_{}" {} {} 2>&1 | grep seek -c'.format(path, size, family, size, int(offset * rows / 1)), shell=True)
    if i == 0:
      print("")
