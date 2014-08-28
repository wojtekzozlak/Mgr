import subprocess
import sys

if len(sys.argv) < 3:
  print "USAGE: ", sys.argv[0], " PATH OFFSET"
  sys.exit(0)

path = sys.argv[1]
offset = sys.argv[2]

sizes = [500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
#sizes = [2000]
#offsets = range(0, 10, 1)
offsets = [0]
families = [1,2,4,8,16]

rows = 23996604
tests = [ (x, y, z) for x in sizes for y in families for z in offsets]

def clear_cache():
    subprocess.call(['sync'])
    with open('/proc/sys/vm/drop_caches', 'w') as f:
        f.write('3')

for size, family, offset in tests:
  for i in range(3):
    clear_cache()
    subprocess.call(['./cat', path + '_' + str(family), str(size), str(int(offset * rows / 10))])
