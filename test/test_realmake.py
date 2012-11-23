# This is the automated test suite for the realmake utility. This
# script should be used for automation as well as regression testing 
# for realmake. It can also be used to verify realmake functionality
# after builing/installing the executable.
#
# License: This software is licensed under the GPL. You are
# free to make any modifications, updates, changes, and distribute
# this code provided you release all of the source code under the 
# GPL.
# 
# DISCLAIMER: THIS SOFTWARE IS PROVIDED AS IS WITH NO WARRANTIES OR
# ANY PROMISE TO MAINTAIN DATA INTEGRITY. BY USING THIS SOFTWARE, YOU
# ACKNOWLEDGE THAT YOU UNDERSTAND THE RISKS INVOLVED AND RELEASE ALL
# DEVELOPERS, OWNERS, AND ANYONE ASSOCIATION WITH THE DEVELOPMENT OF
# THIS SOFTWARE FROM ANY LIABILITY.

import sys;		# we'll need the sys module for sure
import os;		# needed to execute system commands

ARG_COUNT = 1;		# The expected number of arguments
ERROR_MAX = 256;	# Unix error code divisor

def test_realmake(testfile):

 # first, try opening the test file
 tf = open(testfile,'rb');

 tc = 1;
 for line in tf:
  if 0 == len(line.strip()): # don't bother with empty lines
   continue;
  d = [x.strip() for x in line.split(",")]; # get next line of input
  result = os.system(d[0] + " > /dev/null 2>&1"); # execute the command
  result = result/ERROR_MAX; # get the real result of the command

  if int(result) != int(d[1]):
   d.insert(0,str(tc));
   return d;
  
  tc = tc + 1;
 
 return [];

 # close the test file when done
 tf.close();

def main(argv):

 if len(argv) != ARG_COUNT:
  print "Usage: test_realmake.py <test file>";
  return 1;

 output = test_realmake(argv[0]);
 if 0 != len(output):
  (tc,com,rc) = output;
  print "realmake test failed: case(" + tc + "), command(" + com + "), return code(" + rc + ")";
  return 1;

 print "all realmake tests passed!";
 return 0;
	
if __name__ == "__main__":
 sys.exit(main(sys.argv[1:]));

