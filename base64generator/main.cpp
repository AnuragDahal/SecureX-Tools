#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

// Base64 encoding function
std::string base64_encode(const std::vector<unsigned char> &data)
{
    static const char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string encoded;
    size_t padding = (3 - data.size() % 3) % 3;

    for (size_t i = 0; i < data.size(); i += 3)
    {
        uint32_t triple = (data[i] << 16) + ((i + 1 < data.size()) ? (data[i + 1] << 8) : 0) + ((i + 2 < data.size()) ? data[i + 2] : 0);
        encoded.push_back(table[(triple >> 18) & 0x3F]);
        encoded.push_back(table[(triple >> 12) & 0x3F]);
        encoded.push_back((i + 1 < data.size()) ? table[(triple >> 6) & 0x3F] : '=');
        encoded.push_back((i + 2 < data.size()) ? table[triple & 0x3F] : '=');
    }

    return encoded;
}

// Function to read file into a vector of unsigned char
std::vector<unsigned char> read_file(const std::string &filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return {};
    }
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Function to write string to a file
void write_to_file(const std::string &filename, const std::string &data)
{
    std::ofstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    file << data;
    file.close();
}

int main()
{
    std::string filepath;
    std::cout << "Enter the path to the image file: ";
    std::getline(std::cin, filepath); // Get file path from user

    std::vector<unsigned char> image_data = read_file(filepath);
    if (image_data.empty())
    {
        std::cerr << "Failed to read file or file is empty." << std::endl;
        return 1;
    }

    std::string encoded_image = base64_encode(image_data);

    std::string output_filename = "base64.txt";
    write_to_file(output_filename, encoded_image);

    std::cout << "Base64 encoded image data has been written to " << output_filename << std::endl;

    return 0;
}
