import sys
import itertools

cli_args = sys.argv
cli_args.pop(0) # remote perm.py from list

l = list(itertools.permutations(cli_args))
outstring = str()
for p in l:
  for s in p:
    outstring = outstring + s + ' '
print(outstring) 
