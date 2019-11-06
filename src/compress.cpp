/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    ifstream inputFile;
    ofstream compressFile;
    vector<byte> content;
    vector<unsigned int> freqs(256, 0);
    int temp = 0;
    byte next;
    compressFile.open(outFileName);
    inputFile.open(inFileName);
    inputFile.seekg(0, ios_base::end);
    unsigned int curr = inputFile.tellg();

    if (curr == 0) {
        for (int index = 0; index < 256; index++) {
            freqs[index] = 0;
        }
        for (int index = 0; index < 256; index++) {
            temp = freqs[index];
            compressFile << temp << endl;
        }
    } else {
        int numberOfSymbols = 0;
        inputFile.seekg(0, ios::beg);
        while (!inputFile.eof()) {
            next = inputFile.get();
            if (inputFile.eof()) {
                break;
            }
            if (freqs[next] == 0) {
                numberOfSymbols++;
            }
            content.push_back(next);
            //  cout << next << endl;
            //  cout << numberOfSymbols << endl;
            int tempCount = freqs[next];
            freqs[next] = tempCount + 1;
        }

        for (int index = 0; index < 256; index++) {
            temp = freqs[index];
            compressFile << temp << endl;
        }
        HCTree currTree;
        currTree.build(freqs);

        for (unsigned int index = 0; index < content.size(); index++) {
            next = content[index];
            //   cout << next << endl;
            currTree.encode(next, compressFile);
        }
    }
    inputFile.close();
    compressFile.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
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
    pseudoCompression(inputfile, outputfile);
    return 0;
}