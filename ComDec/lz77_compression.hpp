
#ifndef LZ77_COMPRESSION_H
#define LZ77_COMPRESSION_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Global fixed window size
const int WINDOW_SIZE = 4096; //4KB window

// Structure to store tokens (offset, length, next_char)
struct Token {
    int offset;
    int length;
    char next_char;
};

class LZ77Compressor {
private:
vector<Token> tokens; // attribute to store the compressed tokens
public:
      /*
 * Description :
 * compressing file using LZ77 compression technique
 *  takes input (xml_file)
 * returns tokens (offset, length, next_char)
 */
public:
    vector<Token> compress(const string& input); // Compress input and update tokens
    void saveCompressed(const string& filePath, const string& filename); // Save tokens to file
    vector<Token> get_token(){  // getter function for tokens
        return tokens;
    }
};



  class LZ77Decompressor {
private:
  // Original decompress function using the tokens
   string decompress(const  vector<Token>& tokens);

  // Function to read tokens from a binary file
   vector<Token> readTokensFromFile(const  string& filePath);
public:
 /*
 * Description :
 * Decompressing the compressed file (LZ77 compression technique)
 *  takes filepath and access the data inside to decompress it
 * returns string with the xml content 
 */
   string decompressFromFile(const  string& filePath);
   void saveDecompressed(const string& data, const string& filePath, const string& filename);

};

#endif 
