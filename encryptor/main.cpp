#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <limits>

class MorseCodeConverter
{
private:
    std::unordered_map<char, std::string> charToMorse;
    std::unordered_map<std::string, char> morseToChar;

    void initializeMappings()
    {
        charToMorse = {
            {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"}, {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {' ', "/"}};

        for (const auto &pair : charToMorse)
        {
            morseToChar[pair.second] = pair.first;
        }
    }

public:
    MorseCodeConverter()
    {
        initializeMappings();
    }

    std::string encode(const std::string &message)
    {
        std::ostringstream encodedMessage;
        for (char c : message)
        {
            if (charToMorse.find(toupper(c)) != charToMorse.end())
            {
                encodedMessage << charToMorse[toupper(c)] << " ";
            }
        }
        return encodedMessage.str();
    }

    std::string decode(const std::string &morseCode)
    {
        std::istringstream morseStream(morseCode);
        std::ostringstream decodedMessage;
        std::string morseChar;

        while (morseStream >> morseChar)
        {
            if (morseToChar.find(morseChar) != morseToChar.end())
            {
                decodedMessage << morseToChar[morseChar];
            }
            else if (morseChar == "/")
            {
                decodedMessage << " ";
            }
        }

        return decodedMessage.str();
    }

    void encodeFromFile(const std::string &input_file, const std::string &output_file)
    {
        std::ifstream inFile(input_file);
        std::ofstream outFile(output_file);

        if (!inFile.is_open())
        {
            std::cerr << "Failed to open input file: " << input_file << std::endl;
            return;
        }

        if (!outFile.is_open())
        {
            std::cerr << "Failed to open output file: " << output_file << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            outFile << encode(line) << std::endl;
        }

        inFile.close();
        outFile.close();
    }

    void decodeFromFile(const std::string &input_file, const std::string &output_file)
    {
        std::ifstream inFile(input_file);
        std::ofstream outFile(output_file);

        if (!inFile.is_open())
        {
            std::cerr << "Failed to open input file: " << input_file << std::endl;
            return;
        }

        if (!outFile.is_open())
        {
            std::cerr << "Failed to open output file: " << output_file << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inFile, line))
        {
            outFile << decode(line) << std::endl;
        }

        inFile.close();
        outFile.close();
    }
};

int main()
{
    MorseCodeConverter converter;

    int choice;
    std::string input_file, output_file;

    do
    {
        std::cout << "Morse Code Converter" << std::endl;
        std::cout << "1. Encode a message" << std::endl;
        std::cout << "2. Decode a message" << std::endl;
        std::cout << "3. Encode from file" << std::endl;
        std::cout << "4. Decode from file" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice)
        {
        case 1:
            std::cout << "Enter the message to encode: ";
            {
                std::string message;
                std::getline(std::cin, message);
                std::cout << "Encoded Message: " << converter.encode(message) << std::endl;
            }
            break;
        case 2:
            std::cout << "Enter the Morse code to decode (separate letters with spaces and words with /): ";
            {
                std::string morseCode;
                std::getline(std::cin, morseCode);
                std::cout << "Decoded Message: " << converter.decode(morseCode) << std::endl;
            }
            break;
        case 3:
            std::cout << "Enter the input file path (containing messages to encode): ";
            std::getline(std::cin, input_file);
            std::cout << "Enter the output file path (to save encoded messages): ";
            std::getline(std::cin, output_file);
            converter.encodeFromFile(input_file, output_file);
            break;
        case 4:
            std::cout << "Enter the input file path (containing Morse code to decode): ";
            std::getline(std::cin, input_file);
            std::cout << "Enter the output file path (to save decoded messages): ";
            std::getline(std::cin, output_file);
            converter.decodeFromFile(input_file, output_file);
            break;
        case 5:
            std::cout << "Quitting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
