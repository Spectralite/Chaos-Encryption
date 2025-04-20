#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <iomanip>

// Logistic Map Parameters
const double r = 3.99;  // Chaotic parameter (close to 4 for full chaos)
const int KEY_LENGTH = 256;  // Length of chaotic sequence

// Generate chaotic key stream using Logistic Map
double logistic_map(double x) {
    return r * x * (1 - x);
}

std::vector<uint8_t> generate_chaotic_keystream(double seed, size_t length) {
    std::vector<uint8_t> keystream;
    double x = seed;
    for (size_t i = 0; i < length; i++) {
        x = logistic_map(x);
        keystream.push_back(static_cast<uint8_t>(x * 255));  // Normalise to 0-255
    }
    return keystream;
}

// XOR Encryption+Decryption
std::vector<uint8_t> encrypt_decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < data.size(); i++) {
        result.push_back(data[i] ^ key[i % key.size()]);
    }
    return result;
}

// Helper function to convert string to byte vector
std::vector<uint8_t> string_to_bytes(const std::string& str) {
    return std::vector<uint8_t>(str.begin(), str.end());
}

// Helper function to convert byte vector to string
std::string bytes_to_string(const std::vector<uint8_t>& bytes) {
    return std::string(bytes.begin(), bytes.end());
}

int main() {
    std::string plaintext = "This is our string input";
    double seed = 0.5;  // Initial chaotic seed (must be secret)
    
    std::vector<uint8_t> data = string_to_bytes(plaintext);
    std::vector<uint8_t> keystream = generate_chaotic_keystream(seed, data.size());
    std::vector<uint8_t> encrypted = encrypt_decrypt(data, keystream);
    std::vector<uint8_t> decrypted = encrypt_decrypt(encrypted, keystream);
    
    std::cout << "Original:   " << plaintext << "\n";
    std::cout << "Encrypted:  ";
    for (auto byte : encrypted) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
    }
    std::cout << "\n";
    std::cout << "Decrypted:  " << bytes_to_string(decrypted) << "\n";
    return 0;
}

