#!/usr/env python

import sys
import os
import argparse
import unittest

parser = argparse.ArgumentParser(description="Test app for ctest")
parser.add_argument('-v,--verbose', dest='verbose', action='count',
                    help="Increase the amount of output generated by the program")
parser.add_argument('swig_module_dir', metavar='dir',
                    help="Path to swig module.")
parser.add_argument('-o,--output_dir', dest='output_dir', metavar='dir',
                    help="Path to output directory")
parser.add_argument('-i,--input_dir', dest='input_dir', metavar='dir',
                    help="Path to root of input data directory")

args=parser.parse_args()

sys.path=[args.swig_module_dir]+sys.path

import gpstk

def run_unit_tests():
    """A function to run unit tests without using the argument parsing of
    unittest.main() """

    if os.path.dirname(gpstk.__file__) != args.swig_module_dir:
        print "It appears the swig bindings are't loading from the indicated dir"
        print "gpstk.__file__:",os.path.dirname(gpstk.__file__)
        print "args.swig_module_dir:", args.swig_module_dir
        sys.exit(1)
    elif args.verbose:
        print "Using gpstk bindings from {}".format(args.swig_module_dir)

    runner=unittest.TextTestRunner()

    # Find all Test classes in the parent script
    script=os.path.basename(sys.argv[0])
    dir=os.path.dirname(sys.argv[0])
    isuite = unittest.TestLoader().discover(dir, pattern=script)

    rc = runner.run(isuite)
    sys.exit(len(rc.errors))