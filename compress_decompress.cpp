#include "lz77_compression.hpp"
using namespace std;
vector<Token> LZ77Compressor::compress(const string& input) {
    vector<Token> tokens;
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

        // Store the token (offset, length, next_char)
        tokens.push_back({match_offset, match_length, next_char});

        // Move to the next segment
        i += (match_length > 0) ? match_length + 1 : 1;
    }

    return tokens;
}

void LZ77Compressor::saveCompressed(const vector<Token>& tokens, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not write to file." << endl;
        return;
    }

    for (const auto& token : tokens) {
        file.write(reinterpret_cast<const char*>(&token.offset), sizeof(token.offset));
        file.write(reinterpret_cast<const char*>(&token.length), sizeof(token.length));
        file.write(reinterpret_cast<const char*>(&token.next_char), sizeof(token.next_char));
    }

    file.close();
}

string LZ77Decompressor::decompress(const vector<Token>& tokens) {
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

void LZ77Decompressor::saveDecompressed(const string& data, const string& filename) {
     ofstream file(filename);
    if (!file.is_open()) {
         cerr << "Error: Could not write to file." <<  endl;
        return;
    }
    file << data;
    file.close();
}

int main() {
     string filename;
     cout << "Enter the XML file name: ";
     cin >> filename;

    // Read the XML file
     ifstream input_file(filename);
    if (!input_file.is_open()) {
         cerr << "Error: Could not open file." <<  endl;
        return 1;
    }

     string input;
     string line;
    while ( getline(input_file, line)) {
        input += line + '\n';
    }
    input_file.close();

    // Compress the input
    LZ77Compressor compressor;
     vector<Token> tokens = compressor.compress(input);

     cout << "\nCompressed tokens:\n";
    for (const auto& token : tokens) {
         cout << "(" << token.offset << ", " << token.length << ", '" << token.next_char << "')\n";
    }

    // Save compressed tokens to a file
    compressor.saveCompressed(tokens, "compressed_output.lz77");
     cout << "\nCompressed output saved to 'compressed_output.lz77'." <<  endl;

    // Decompress the tokens
    LZ77Decompressor decompressor;
     string decompressed = decompressor.decompress(tokens);

     cout << "\nDecompressed string: " << decompressed <<  endl;

    // Write the decompressed output to a file
    decompressor.saveDecompressed(decompressed, "decompressed_output.xml");
     cout << "\nDecompressed output saved to 'decompressed_output.xml'." <<  endl;

    return 0;
}
