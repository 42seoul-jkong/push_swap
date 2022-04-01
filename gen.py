import sys
import os
import random

if len(sys.argv) > 3:
	lbound = int(sys.argv[1])
	ubound = int(sys.argv[2])
	count = int(sys.argv[3])
elif len(sys.argv) > 1:
	lbound = 0
	ubound = int(sys.argv[1])
	count = int(sys.argv[1])
else:
	lbound = 0
	ubound = 500
	count = 500

r = range(lbound, ubound)
sample = random.sample(r, count)
args = ' '.join(str(i) for i in sample)

os.system('./push_swap ' + args)
