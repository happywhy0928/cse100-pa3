/**
 * TODO: file header
 *
 * Author:
 */
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {
    ifstream compressFile;
    ofstream result;
    vector<unsigned int> freqs(256, 0);
    int freq = 0;
    byte read;
    compressFile.open(inFileName);

    //  int i = 0;
    int numElement = 0;

    for (int i = 0; i < 256; i++) {
        compressFile >> freq;
        if (freq != 0) {
            numElement++;
            //   cout << freq << endl;
        }
        freqs[i] = freq;
        freq = 0;
    }
    /*
    while (compressFile >> freq) {
        if (freq != 0) {
            numElement++;
        }
        freqs[i] = freq;
        freq = 0;
        i++;
        if (i > 255) {
            break;
        }
    } */
    if (numElement == 0) {
        result.open(outFileName);
        result.close();
    } else {
        read = compressFile.get();
        //  cout << read << endl;
        HCTree temp;
        temp.build(freqs);
        result.open(outFileName);
        while (1) {
            // read = compressFile.get();
            read = temp.decode(compressFile);
            /* if (read == 0) {
                 break;
             }
   */ if (compressFile.eof()) {
                break;
            }

            // while (!compressFile.eof()) {
            // read = temp.decode(compressFile);
            //   cout << "FALSE" << endl;
            // if (compressFile.eof()) {
            //     break;
            // }
            result << (char)read;
        }
        //  }
        result.close();
        compressFile.close();
    }
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    string inputfile = "";
    string outputfile = "";
    for (int i = 1; i < argc; i++) {
        string curr = argv[i];
        if (inputfile == "") {
            inputfile = curr;
        } else {
            outputfile = curr;
        }
    }
    if (inputfile == "" || outputfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        return 1;
    }
    pseudoDecompression(inputfile, outputfile);
    return 0;
}
