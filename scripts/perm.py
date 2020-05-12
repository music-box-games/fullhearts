import sys
import itertools

cli_args = sys.argv
cli_args.pop(0) # remote perm.py from list

l = list(itertools.permutations(cli_args))
outstring = str()
counter = 0
for p in l:
  counter += 1
  print(counter)
  for s in p:
    outstring = outstring + s + ' '
print(outstring) 
