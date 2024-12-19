#ifndef LZ77_COMPRESSION_H
#define LZ77_COMPRESSION_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Global fixed window size
const int WINDOW_SIZE = 4096; // 4KB window

// Structure to store tokens (offset, length, next_char)
struct Token {
    int offset;
    int length;
    char next_char;
};

class LZ77Compressor {
public:
      /*
 * Description :
 * compressing file using LZ77 compression technique
 *  takes input file name 
 * returns tokens (offset, length, next_char)
 */
      vector<Token> compress(const string& input);
      
    void saveCompressed(const vector<Token>& tokens, const string& filename);
};

class LZ77Decompressor {
public:
     /*
 * Description :
 * Decompressing the compressed file (LZ77 compression technique)
 *  takes input tokens 
 * returns string with the xml content 
 */
      string decompress(const vector<Token>& tokens);
    void saveDecompressed(const string& data, const string& filename);
};

#endif 
