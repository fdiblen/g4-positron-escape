#! /usr/bin/env python

import sys
import math
from ROOT import *
from optparse import OptionParser


# Commandline options
parser = OptionParser()

parser.add_option('-f', '--file', dest='sfile', help='ROOT file to read singles')
parser.add_option("-t", action="store_true", dest="sBrowser", help='Start Tree viewer')
parser.add_option("-b", action="store_true", dest="batch", help='batch mode')
(opts, args) = parser.parse_args()


if opts.sfile is None:
    print "You must specify filename. \n"
    parser.print_help()
    sys.exit(-1)


# Show commandline inputs
rFileName = opts.sfile
sBrowser  = opts.sBrowser
batch     = opts.batch



rfile = TFile(rFileName)

bool_singles = True

print
print  "File: %s" % (rFileName)


nentries  = 0


if bool_singles:
    tree = rfile.Get("stopped")
    tree.Draw("posx","","goff");
    nentries = tree.GetSelectedRows()
    print "Number of entries          : %s" % ( nentries )
    if sBrowser:
        tree.StartViewer()
else:
    print "No Singles tree found!"


print

if not batch:
    test = raw_input("Press any key to exit.")
    print

