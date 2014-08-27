import subprocess
import sys

if len(sys.argv) < 3:
  print "USAGE: ", sys.argv[0], " PATH OFFSET"
  sys.exit(0)

path = sys.argv[1]
offset = sys.argv[2]

sizes = [500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
families = [1,2,4,8,16]

tests = [ (x, y) for x in sizes for y in families]

def clear_cache():
    subprocess.call(['sync'])
    with open('/proc/sys/vm/drop_caches', 'w') as f:
        f.write('3')

for size, family in tests:
  for i in range(3):
    clear_cache()
    subprocess.call(['./cat', path + '_' + str(family), str(size), str(offset)])
