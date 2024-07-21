#include <iostream>
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
};

int main()
{
    MorseCodeConverter converter;

    int choice;
    std::string input;

    do
    {
        std::cout << "Morse Code Converter" << std::endl;
        std::cout << "1. Encode a message" << std::endl;
        std::cout << "2. Decode a message" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice)
        {
        case 1:
            std::cout << "Enter the message to encode: ";
            std::getline(std::cin, input);
            std::cout << "Encoded Message: " << converter.encode(input) << std::endl;
            break;
        case 2:
            std::cout << "Enter the Morse code to decode (separate letters with spaces and words with /): ";
            std::getline(std::cin, input);
            std::cout << "Decoded Message: " << converter.decode(input) << std::endl;
            break;
        case 3:
            std::cout << "Quitting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}