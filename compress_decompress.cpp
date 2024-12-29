#include "lz77_compression.hpp"
using namespace std;
vector<Token> LZ77Compressor::compress(const string& input) {
    tokens.clear(); // Clear previous tokens if any
    size_t i = 0;

    while (i < input.size()) {
        int match_offset = 0;
        int match_length = 0;
        char next_char = input[i];

        // Define the search window
        int start = (i < WINDOW_SIZE) ? 0 : static_cast<int>(i) - WINDOW_SIZE;

        // Search for the longest match
        for (int j = start; j < static_cast<int>(i); ++j) {
            int k = 0;
            while (j + k < i && i + k < input.size() && input[j + k] == input[i + k]) {
                k++;
            }

            // Update the longest match found
            if (k > match_length) {
                match_length = k;
                match_offset = i - j;
                if (i + k < input.size()) {
                    next_char = input[i + k];
                } else {
                    next_char = '\0';
                }
            }
        }

        // Store the token (offset, length, next_char) in the class attribute
        tokens.push_back({match_offset, match_length, next_char});

        // Move to the next segment
        i += (match_length > 0) ? match_length + 1 : 1;
    }

    return tokens; // Optional: Return for debugging purposes
}
void LZ77Compressor::saveCompressed(const string& filePath, const string& filename) {
    string finalFilePath = filePath;

    // Append the filename if the path ends with a directory separator
    if (filePath.back() == '\\' || filePath.back() == '/') {
        finalFilePath += filename;
    }

    // Open the file in binary mode
    ofstream file(finalFilePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not write to file at " << finalFilePath << endl;
        return;
    }

    // Write the tokens to the file
    for (const auto& token : tokens) {
        file.write(reinterpret_cast<const char*>(&token.offset), sizeof(token.offset));
        file.write(reinterpret_cast<const char*>(&token.length), sizeof(token.length));
        file.write(reinterpret_cast<const char*>(&token.next_char), sizeof(token.next_char));
    }

    file.close();
    cout << "Compressed data saved to " << finalFilePath << endl;
}




 string LZ77Decompressor::decompress(const  vector<Token>& tokens) {
   string output;

  for (const auto& token : tokens) {
    if (token.offset > 0 && token.length > 0) {
      int start = output.size() - token.offset;
      for (int i = 0; i < token.length; ++i) {
        output += output[start + i];
      }
    }
    if (token.next_char != '\0') {
      output += token.next_char;
    }
  }

  return output;
}

 vector<Token> LZ77Decompressor::readTokensFromFile(const  string& filePath) {
   vector<Token> tokens;

   ifstream file(filePath,  ios::binary);
  if (!file.is_open()) {
     cerr << "Error: Could not open file for reading!" <<  endl;
    return tokens;
  }

  while (file.peek() != EOF) {
    Token token;
    file.read(reinterpret_cast<char*>(&token.offset), sizeof(token.offset));
    file.read(reinterpret_cast<char*>(&token.length), sizeof(token.length));
    file.read(reinterpret_cast<char*>(&token.next_char), sizeof(token.next_char));

    tokens.push_back(token);
  }

  file.close();
  return tokens;
}

 string LZ77Decompressor::decompressFromFile(const  string& filePath) {
   vector<Token> tokens = readTokensFromFile(filePath);
  return decompress(tokens);
}


void LZ77Decompressor::saveDecompressed(const string& data, const string& filePath, const string& filename) {
    // Combine path and filename into a full file path
    string fullFilePath = filePath;
    
    // Check if the path ends with a directory separator, and if not, add it
    if (filePath.back() != '\\' && filePath.back() != '/') {
        fullFilePath += '\\'; // Add separator for Windows; use '/' for UNIX-like systems if needed
    }
    
    fullFilePath += filename;

    // Open the file for writing
    ofstream file(fullFilePath);
    if (!file.is_open()) {
        cerr << "Error: Could not write to file at " << fullFilePath << endl;
        return;
    }

    // Write the decompressed data to the file
    file << data;

    // Close the file
    file.close();
}





