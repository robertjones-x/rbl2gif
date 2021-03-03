// rbl2gif.cpp : convert .rbl encoded files to GIF
//
//
// MIT License
//
// Copyright(c) 2021 robertjones - x
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned char BYTE;

void printusage(char* progname, int longver) {
    std::cout << std::endl << "usage: " << progname << " [-h] infile outfile" << std::endl;
    if (longver) {
        std::cout << std::endl;
        std::cout << "postional arguments:" << std::endl;
        std::cout << "  infile\tinput file to convert" << std::endl;
        std::cout << "  outfile\toutput file in GIF format" << std::endl << std::endl;
        std::cout << "optional arguments:" << std::endl;
        std::cout << "  -h\tshow this help message and exit" << std::endl;
    }
    return;
}

int main(int argc, char* argv[])
{
    std::string infile, outfile;

    if (argc == 2) {
        if (std::string(argv[1]) == "-h") {
            printusage(argv[0], true);
            return 0;
        }
        else {
            printusage(argv[0], false);
            std::cout << "error: invalid syntax." << std::endl;
            return 1;
        }
    }
    else if (argc == 3) {
        infile = argv[1];
        outfile = argv[2];
        if (infile.compare(outfile) == 0) {
            printusage(argv[0], false);
            std::cout << "error: INFILE and OUTFILE cannot be the same" << std::endl;
            return 1;
        }
        else {
            std::ifstream f(infile.c_str());
            if (!f.good()) {
                printusage(argv[0], false);
                std::cout << "error: unable to open INFILE" << std::endl;
                return 1;
            }
        }
    }
    else {
        printusage(argv[0], false);
        std::cout << "error: invalid syntax" << std::endl << std::endl;
        return 1;
    }

    long filesize;
    std::ifstream reader(infile, std::ios::binary);
    if (reader.is_open())
    {
        reader.seekg(0, std::ios::end);
        filesize = reader.tellg();
        reader.seekg(0, std::ios::beg);
        std::vector<BYTE> filedata(filesize);
        reader.read((char*)&filedata[0], filesize);

        if (filesize < 7) {
            reader.close();
            return 0;
        }

        std::ofstream writer(outfile, std::ios::binary);
        writer.write("GIF89", 5);

        filesize = filesize -= 2;

        for (int idx = 5; idx < filesize; idx++) {
            unsigned char dat = filedata[idx];
            writer.put(dat - 1);
        }
        for (int idx = 0; idx < 2; idx++) {
            writer.put(filedata[filesize + idx]);
        }

        reader.close();
        writer.close();
    }
}