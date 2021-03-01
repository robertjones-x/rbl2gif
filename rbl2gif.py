#!/usr/bin/python


# rbl2gif.py - convert .rbl encoded files to GIF

# MIT License
#
# Copyright (c) 2021 robertjones-x
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


import argparse
import logging
import os

logging.basicConfig(level=logging.WARNING)

parser = argparse.ArgumentParser()
parser.add_argument("infile", help='input file to convert')
parser.add_argument("outfile", help='output file in GIF format')
args = parser.parse_args()


def main():
    infilename = args.infile
    outfilename = args.outfile

    if infilename == outfilename:
        logging.error('cannot write back to same filename')
        return 1

    if outfilename[-3:].lower() != 'gif':
        logging.warning('output file extension does not match output data type')

    if not os.path.exists(infilename):
        logging.error('input file does not exist')
        return 1

    fin = open(infilename, 'rb')
    incontent = fin.read()
    fin.close()

    outcontent = bytes('GIF89', 'ascii')

    for byte in incontent[5:-2]:
        if byte == 0:
            newval = 255
        else:
            newval = byte - 1
        outcontent += newval.to_bytes(1, byteorder='little')

    outcontent += incontent[-2:]

    if len(incontent) != len(outcontent):
        logging.error('data translation error, length mismatch')
        return 1

    fout = open(outfilename, 'wb')
    fout.write(outcontent)
    fout.close()

    return 0


if __name__ == '__main__':
    exit(main())
