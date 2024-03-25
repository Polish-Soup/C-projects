#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

std::string const BACKUPCIPHER = { "H;pga<Nb?8deKf_Ehi@kl]mSn{ZGXo-qrst}uvw(delete '\' after copying->)\"xz`~!#$V7%^M1&*\',./0Y2T3(45[69Ay:BC=D>FI|JLO+PQ)RUWj"};

DWORD WINAPI CheckEscape( LPVOID lpParam ) {
        while(GetAsyncKeyState(VK_ESCAPE)==0){
            //sleep 
            Sleep(10);
        }
        exit(0);
}

int findIt(char codeCharA[], int size, char value)
{
    int index = 0;
    int position = -1;
    bool found = false;

    while (index < size && !found)
    {
        if (codeCharA[index] == value)
        {
            found = true;
            position = index;
        }
        index++;
    }
    return position;
}

int main()
{
    int ascii;
    int size = 94;
    char newChar;
    char nextChar;
    char codeChar[94];
    
    std::string word = {"I can write a secret message"};
    std::string whole_file;
    std::string newString = "";
    std::string code = "";

    char originalChar;
    int index;

    char choice;

    std::ifstream inFile;
    inFile.open("code.txt");
    // Set position to the end of the file
    inFile.seekg(0, std::ios::end);  
    if (inFile.tellg() == 0)
    { 
        std::cout << "The file containing the cipher is empty." << std::endl;
        std::cout << "You can't use the program without the cipher!\n" << std::endl;
    }
    inFile.close();

    CreateThread( NULL, 0, CheckEscape,NULL  , 0, NULL);

    std::cout << "Press Esc to exit." << std::endl;

    std::cout << "****** CIPHER CODE ******" << std::endl;
    std::cout << "Do you want to:\n";
    std::cout << "Encode a message (W)rite\n";
    std::cout << "Decode a message (R)ead\n";
    std::cout << "(W/w or R/r)...";
    std::cin >> choice;

    choice = tolower(choice);

    if (choice == 'w')
    {
        std::cout << "Write the message you want to encode:\n";
        std::getline (std::cin >> std::ws,word);

        inFile.open("code.txt");

        if (!inFile.is_open())
        {
            std::cout << "File could not be opened (writing)" << std::endl;
        }
        else 
        {
            for (int i = 0; i < 94; i++)
            {
                inFile >> codeChar[i];
            }
            for (int i = 0; i < word.length(); i++)
            {
                ascii = word[i];
                newChar = codeChar[ascii - 32];
                code += newChar;
            }
            inFile.close();
            std::cout << "The original message:\n" << word << std::endl;
            std::cout << "The secret code:\n" << code << std::endl;

            // writing the cipher to text file
            std::ofstream eFile;
            eFile.open("cipher.txt", std::ofstream::out | std::ofstream::trunc);
            if (!eFile.is_open())
            {
                std::cout << "File could not be opened (writing)" << std::endl;
            } else
            {
                eFile << code;
                if (eFile.bad())
                {
                    // failed to write
                    std::cout << "Operation failed, message saved incorrectly" << std::endl;
                }
            }
            eFile.close();
        }
    } else if (choice == 'r')
    {
        // read cipher key
        inFile.open("code.txt");
        if (!inFile.is_open())
        {
            std::cout << "Cipher file could not be opened" << std::endl;
        }
        else 
        {
            for (int i = 0; i < 94; i++)
            {
                inFile >> codeChar[i];
            }
        }
        inFile.close();
        // reading only
        std::ifstream readFile;
        readFile.open("cipher.txt");
        // Set position to the end of the file
        readFile.seekg(0, std::ios::end);  
        // check if the file opened successfully
        if (!readFile.is_open()) {
            std::cout << "File could not be opened (reading)" << std::endl;
        } else if (readFile.tellg() == 0)
        { 
            std::cout << "File is empty." << std::endl;
        }
        else
        {
            // Set position to the end of the file
            readFile.seekg(0, std::ios::end);
            // Reserve memory for the file
            whole_file.reserve(readFile.tellg());
            // Set position to the start of the file
            readFile.seekg(0, std::ios::beg);
            // Assign text from file to whole_file string
            whole_file.assign(std::istreambuf_iterator<char>(readFile),
                std::istreambuf_iterator<char>());

            for (int i = 0; i < whole_file.length(); i++)
            {
                nextChar = whole_file[i];
                index = findIt(codeChar, size, nextChar);
                originalChar = index + 32;
                newString += originalChar;
            }
            //
            std::cout << "The coded message:\n" << whole_file << std::endl;
            std::cout << "The decoded message:\n" << newString << std::endl;
        }
        readFile.close();
    }

    std::cout << "**************************" << std::endl;

    return 0;
}
