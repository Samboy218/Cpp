// (c) Samuel Wehunt 2106
// This is a steganography program which has the capability to use 2 different algorithms to hide/extract messages hidden in a .png file
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <functional>
#include <string>
#include <cstdlib>
#include <cctype>
#include "lodepng.h"


using namespace std;

//Uses the Pseudo-random number generation to find which pixels the data should be hidden in
//Pre: image is the vector which contains the image data, key is the seed for the PRNG, and plaintext is the message to be hidden in the image data
//Post: returns true if the operation was successful, in this case image has been edited and now contians the hidden message
//      returns false if any part of the hiding failed. image is not guaranteed to be unchanged.
bool stegoEncodePRNG(vector<unsigned char> &image, string key, string plainText);

//Performs the revers of the above function, and attempts to extract a message hidden in a .png file
//Pre: image is the image data to extract an image from, key is the seed to use for the PRNG (must match the key used to hide the message)
//Post: returns the message hidden in the image if it existed and the key was correct (success)
//      returns the empty string if the operation was unsuccessful
string stegoDecodePRNG(vector<unsigned char> image, string key);

//Channel based hiding algorithm, uses the pointer channel to determine whether to hide data in the other two channels
//Pre: image is the image data, channel is either 'R' 'G' or 'B', and tells which channel is the pointer channel, plaintext is the message to hide
//Post: returns true if the message was successfully encoded in the image data, retruns false otherwise (image data is still modified)
bool stegoEncodeCBH(vector<unsigned char> &image, char channel, string plainText);

//Performs the reverse of the above operation
//Pre: image is the image data to extract the message from, channel denotes which channel is the pointer
//Post: returns the message if there was a message hidden using the correct pointer channel
//      returns the empty string if the operation was unsuccessful
string stegoDecodeCBH(vector<unsigned char> image, char channel);

//converts an ascii string to binary
//Pre: text is the string to convert, bin is an empty vector of bytes which will be populated with the data
//Post: the string is converted, and the binary data is stored in bin
void str_bin(string text, vector<bitset<8> > &bin);

//converts binary to an ascii string
//Pre: bin is a vector of bytes to convert to an ASCII equivalent string
//Post: the ASCII string is returned, bin is unchanged
string bin_str(vector<bitset<8> > bin);

//Saves image data into a .png file
//Pre: filename is the name of the file to save, out is the image data to be stored in the file, width and height are the dimensions of the image
//Post: if filename is an existing file, a prompt will verify that the file will be overwritten
//      returns true if the file was successfully saved, returns false otherwise (including if the user chose to not override an existing file)
bool writePNG(string fileName, vector<unsigned char> out, unsigned width, unsigned height);

//Loads an image (.png) file into memory
//Pre: filename is the file to load, out is an empty vector of characters to save the data to, width and height are where the function will output the image dimensions
//Post: returns false if any error occurred during the load (none of the variables are guarateed in this scenario)
//      returns true if loading was successful. out will be populated with the image data, and width and height will contain the proper image dimensions
bool loadPNG(string fileName, vector<unsigned char> &out, unsigned &width, unsigned &height);

//Checks if a file exists or not
//Pre: filename is the file to check
//Post: opens the file, and then checks if the operation was successful
//      returns true on a good open, returns false otherwise (file doesn't exist, or otherwise is not good to open)
bool doesFileExist(string fileName);

//checks if a string is raw data, or a filename
//Pre: input is whatever the user typed
//Post: if no file exists by the name of what they entered, return the raw string
//      otherwise, read the file and return its contents
string fileOrRaw(string input);

//reads a text file as one long string
//Pre:  fileName is the file to read from
//Post: The contents of the file are returned as a string,
//      with end-of-lines interpreted as a space
string readFromFile(string fileName);



int main()
{
    string encodeChoice;
    string algChoice;
    string key;
    string filename;
    string message;
    string plainText;
    string fileNameOut;
    string choice;
    string result;
    vector <unsigned char> image;
    unsigned int width = 0;
    unsigned int height = 0;
    do
    {
        image.clear();
        width = 0;
        height = 0;

        cout << "Do you want to hide a message, or extract a message? (H/E)\n>>";
        getline(cin, encodeChoice);
        if (encodeChoice == "")
        {
            cout << "need to choose an encoding option\n>>";
            return 2;
        }

        cout << "Choose an algorithm; PRNG or CBH? (P/C)\n>>";
        getline(cin, algChoice);
        if (algChoice == "" || algChoice[0] == 'p' || algChoice[0] == 'P')
            cout << "Enter the key\n>>";
        else
            cout << "Enter the channel that will be used as a pointer (valid options are 'R' 'G' 'B')\n>>";
        getline(cin, key);
        if (encodeChoice[0] == 'h' || encodeChoice[0] == 'H')
        {
            cout << "Enter the ASCII message you wish to hide; this could also be the name of a file containing ASCII characters\n>>";
            getline(cin, message);
            cout << "Enter the name of the .png image to hide the message in\n>>";
        }
        else
            cout << "Enter the name of the .png file to extract a message from\n>>";
        
        getline(cin, filename);

         
        if (loadPNG(filename, image, width, height))
        {
            cout <<width<<" "<<height<<endl;
            cout << "Image load success!\n";
        }
        else
        {
            cout << "Image load fail\n";
            return 1;
        }
        
        

        if (encodeChoice[0] == 'h' || encodeChoice[0] == 'H')
        {
            plainText = fileOrRaw(message);
            if (algChoice == "" || algChoice[0] == 'P' || algChoice[0] == 'p')
            {
                if (!stegoEncodePRNG(image, key, plainText))
                {
                    cout << "Image encoding failed!\n";
                    return 3;
                }
            }
            else
            {
                if (key == "")
                    key = "R";
                if (!stegoEncodeCBH(image, key[0], plainText))
                {
                    cout << "Image encoding failed!\n";
                    return 3;
                }
            }
            do
            {
                cout << "Image encoding success! Enter the .png filename to store the secret-encoded image\n>>";
                getline(cin, fileNameOut);
            }while(!writePNG(fileNameOut, image, width, height));
        }
        else
        {
            if (algChoice == "" || algChoice[0] == 'P' || algChoice[0] == 'p')
            {
                result = stegoDecodePRNG(image, key);
                if (result == "")
                    cout << "No data successfully extracted\n";
                else
                    cout << result;
            }
            else
            {
                if (key == "")
                    key = "R";
                result = stegoDecodeCBH(image, key[0]);
                if (result == "")
                    cout << "No data successfully extracted\n";
                else
                    cout << result;
            }
        }


        cout << "\nWanna quit?\n";
        getline(cin, choice);
    }while (choice != "" && choice[0] != 'y' && choice[0] != 'Y');

    return 0;
}

//Uses the Pseudo-random number generation to find which pixels the data should be hidden in
//Pre: image is the vector which contains the image data, key is the seed for the PRNG, and plaintext is the message to be hidden in the image data
//Post: returns true if the operation was successful, in this case image has been edited and now contians the hidden message
//      returns false if any part of the hiding failed. image is not guaranteed to be unchanged.
bool stegoEncodePRNG(vector<unsigned char> &image, string key, string plainText)
{
    //seed the rng with their value
    hash<string> str_hash;
    int hash_val = str_hash(key);
    srand(hash_val);

    //the indicies to store binary values at
    vector<unsigned> indicies;
    
    //go until we find all possible indicies to hide the message (image.size() / 4)
    for (unsigned currentInd = 0; currentInd < image.size()/4 ; currentInd++)
    {
        int random = rand() % 2;
        if (random == 0)
        {
            indicies.push_back(currentInd);
        }
    }

    cout << "Storage size = " << indicies.size()/8 << " Bytes\n";
    cout << "Message size = " << plainText.size() + 2 << " Bytes\n";
    //now we make sure we have enough room to store the message (and 16 bit delimiter). 
    //we check if the last bit of our message runs past the number of pixels in the image
    if (plainText.size()*8 + 16 > indicies.size())
    {
        cout << "Error: cannot fit message into image data, try larger image, shorter message, different hiding algorithm, or possibly a different key\n";
        return false;
    }

    //now lets get the binary of the message
    vector<bitset<8> > binary;
    str_bin(plainText, binary);
    bitset<8> delimiter;
    delimiter.set();
    binary.push_back(delimiter);
    binary.push_back(delimiter);

    for (unsigned currChar = 0; currChar < binary.size(); currChar++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            //find the pixel for the current bit, then get the red channel of that pixel
            unsigned currInd = indicies[currChar*8 + bit];
            unsigned imageIndex = currInd * 4;
            bitset<8> pixelR(image[imageIndex]);
            pixelR[0] = binary[currChar][bit];
            image[imageIndex] = pixelR.to_ulong();
        }
    }

    return true;
}

//Performs the revers of the above function, and attempts to extract a message hidden in a .png file
//Pre: image is the image data to extract an image from, key is the seed to use for the PRNG (must match the key used to hide the message)
//Post: returns the message hidden in the image if it existed and the key was correct (success)
//      returns the empty string if the operation was unsuccessful
string stegoDecodePRNG(vector<unsigned char> image, string key)
{
    //seed the rng with their value
    hash<string> str_hash;
    int hash_val = str_hash(key);
    srand(hash_val);

    vector<bitset<8> > binary;
    unsigned currChar = 0;
    unsigned currBit = 0;
    bitset<8> empty;

    binary.push_back(empty);

    //scan through each pixel in the image, if the pixel contains hidden data the extract it
    for (unsigned pixelInd = 0; pixelInd < image.size(); pixelInd += 4)
    {
        if (rand() % 2 == 0)
        {
            bitset<8> pixelR = image[pixelInd];
            binary[currChar][currBit] = pixelR[0];
            currBit++;

            if (currBit == 8)
            {
                if (binary[binary.size()-1].all() && binary[binary.size()-2].all())
                {
                    return bin_str(binary);
                }
                currChar++;
                currBit = 0;
                binary.push_back(empty);

            }
        }
    }

    cout << "Error: Delimiter not found, decoded string likely incorrect\n";
    return "";
}

//Channel based hiding algorithm, uses the pointer channel to determine whether to hide data in the other two channels
//Pre: image is the image data, channel is either 'R' 'G' or 'B', and tells which channel is the pointer channel, plaintext is the message to hide
//Post: returns true if the message was successfully encoded in the image data, retruns false otherwise (image data is still modified)
bool stegoEncodeCBH(vector<unsigned char> &image, char channel, string plainText)
{
    unsigned int offset = 0;
    switch (channel)
    {
        case 'R':
        offset = 0;
        break;

        case 'G':
        offset = 1;
        break;

        case 'B':
        offset = 2;
        break;

        default:
        cout << "Valid channel choices are RGB, enter a valid channel\n";
        return false;
        break;
    }
    //we need the message in binary form
    vector<bitset<8> > binary;
    str_bin(plainText, binary);
    bitset<8> delimiter;
    delimiter.set();
    binary.push_back(delimiter);
    binary.push_back(delimiter);

    //lets see if we will have enough data to hide the message
    unsigned int binarySize = (plainText.size() + 2) * 8;
    unsigned int storage = 0;
    for (unsigned int i = 0 + offset; i < image.size(); i += 4)
    {
        bitset <8> pixChannel(image[i]);
        if (pixChannel[1] == 1)
            storage++;
        if (pixChannel[0] == 1)
            storage++;
    }

    cout << "Storage size = " << storage/8 << " Bytes\n";
    cout << "Message size = " << plainText.size() + 2 << " Bytes\n";
    if (storage < binarySize)
    {
        cout << "Error: cannot fit message into image data, try larger image, shorter message, different hiding algorithm, or possibly a different channel\n";
        return false;
    }
    

    //now we know we have enough space to fit the message, so lets get to work
    unsigned int currBit = 0;
    for (unsigned int i = 0; i < image.size(); i+= 4)
    {
        bitset <8> pixelR(image[i]);
        bitset <8> pixelG(image[i+1]);
        bitset <8> pixelB(image[i+2]);

        switch(offset)
        {
            case 0:
            if (pixelR[1] == 1)
            {
                pixelG[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            if (currBit == binarySize)
                break;
            if (pixelR[0] == 1)
            {
                pixelB[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            break;
            
            case 1:
            if (pixelG[1] == 1)
            {
                pixelR[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            if (currBit == binarySize)
                break;
            if (pixelG[0] == 1)
            {
                pixelB[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            break;
            
            case 2:
            if (pixelB[1] == 1)
            {
                pixelR[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            if (currBit == binarySize)
                break;
            if (pixelB[0] == 1)
            {
                pixelG[0] = binary[currBit/8][currBit%8];
                currBit++;
            }
            break;
        }
        image[i] = pixelR.to_ulong();
        image[i+1] = pixelG.to_ulong();
        image[i+2] = pixelB.to_ulong();

        if (currBit == binarySize)
            break;
    }

    if (currBit < binary.size() * 8)
    {
        cout << "An error ocurred while hiding the data: all data not encoded successfully\n";
        return false;
    }
    return true;
}

//Performs the reverse of the above operation
//Pre: image is the image data to extract the message from, channel denotes which channel is the pointer
//Post: returns the message if there was a message hidden using the correct pointer channel
//      returns the empty string if the operation was unsuccessful
string stegoDecodeCBH(vector<unsigned char> image, char channel)
{
    unsigned int offset = 0;
    switch (channel)
    {
        case 'R':
        offset = 0;
        break;

        case 'G':
        offset = 1;
        break;

        case 'B':
        offset = 2;
        break;

        default:
        cout << "Valid channel choices are RGB, use a valid channel\n";
        return "";
        break;
    }

    vector<bitset<8> > binary;
    //unsigned currChar = 0;
    //unsigned currBit = 0;
    bitset<8> empty;
    binary.push_back(empty);

    unsigned int currChar = 0;
    unsigned int currBit = 0;

    for (unsigned int i = 0; i < image.size(); i += 4)
    {
        bitset <8> pixelR(image[i]);
        bitset <8> pixelG(image[i+1]);
        bitset <8> pixelB(image[i+2]);
        bitset <2> extracted;
        int foundBits = 0;

        switch (offset)
        {
            case 0:
            if (pixelR[1] == 1)
            {
                extracted[foundBits] = pixelG[0];
                foundBits++;
            }
            if (pixelR[0] == 1)
            {
                extracted[foundBits] = pixelB[0];
                foundBits++;
            }
            break;
            case 1:
            if (pixelG[1] == 1)
            {
                extracted[foundBits] = pixelR[0];
                foundBits++;
            }
            if (pixelG[0] == 1)
            {
                extracted[foundBits] = pixelB[0];
                foundBits++;
            }
            break;
            case 2:
            if (pixelB[1] == 1)
            {
                extracted[foundBits] = pixelR[0];
                foundBits++;
            }
            if (pixelB[0] == 1)
            {
                extracted[foundBits] = pixelG[0];
                foundBits++;
            }
            break;
        }

        for (int bitCount = 0; bitCount < foundBits; bitCount++)
        {
            binary[currChar][currBit] = extracted[bitCount];
            currBit++;
            if (currBit == 8)
            {
                if (binary[binary.size()-1].all() && binary[binary.size()-2].all())
                {
                    return bin_str(binary);
                }
                currChar++;
                currBit = 0;
                binary.push_back(empty);
            }
        }
    }
    cout << "Error: Delimiter not found, decoded string likely incorrect\n";
    return "";
}

//converts an ascii string to binary
//Pre: text is the string to convert, bin is an empty vector of bytes which will be populated with the data
//Post: the string is converted, and the binary data is stored in bin
void str_bin(string text, vector<bitset<8> > &bin)
{
    for (unsigned i = 0; i < text.length(); i++)
    {
        bitset <8> letter(text[i]);
        bin.push_back(letter);
    }
}

//converts binary to an ascii string
//Pre: bin is a vector of bytes to convert to an ASCII equivalent string
//Post: the ASCII string is returned, bin is unchanged
string bin_str(vector<bitset<8> > bin)
{
    string output = "";
    unsigned long ulongChar = 0;
    char character;
    for (unsigned i = 0; i < bin.size(); i++)
    {
        ulongChar = bin[i].to_ulong();
        character = (char) ulongChar;
        output += character;
    }
    return output;
}

//Saves image data into a .png file
//Pre: filename is the name of the file to save, out is the image data to be stored in the file, width and height are the dimensions of the image
//Post: if filename is an existing file, a prompt will verify that the file will be overwritten
//      returns true if the file was successfully saved, returns false otherwise (including if the user chose to not override an existing file)
bool writePNG(string fileName, vector<unsigned char> out, unsigned width, unsigned height)
{
    if (doesFileExist(fileName))
    {
        string overwrite;
        cout << "Warning: the specified file will be overwritten, is this okay? (y/n)\n>>";
        getline(cin, overwrite);

        if (overwrite[0] != 'y' && overwrite[1] != 'Y')
        {
            return false;
        }
    }

    unsigned error = lodepng::encode(fileName, out, width, height);

    if (error)
    {
        cout << "Error: " << lodepng_error_text(error) << " (" << error << ")\n";
        return false;
    }
    return true;
}

//Loads an image (.png) file into memory
//Pre: filename is the file to load, out is an empty vector of characters to save the data to, width and height are where the function will output the image dimensions
//Post: returns false if any error occurred during the load (none of the variables are guarateed in this scenario)
//      returns true if loading was successful. out will be populated with the image data, and width and height will contain the proper image dimensions
bool loadPNG(string fileName, vector<unsigned char> &out, unsigned &width, unsigned &height)
{
    //first, check to see if file exists
    if (!doesFileExist(fileName))
    {
        cout << "Error: file \"" << fileName << "\" does not exist\n";
        return false;
    }

    //okay, the file does exist, lets load it into the output vector
    unsigned error = lodepng::decode(out, width, height, fileName);

    if (error)
    {
        cout << "Error: " << lodepng_error_text(error) << " (" << error << ")\n";
        return false;
    }

    //if we get here, its all good and the image is loaded
    return true;

}

//Checks if a file exists or not
//Pre: filename is the file to check
//Post: opens the file, and then checks if the operation was successful
//      returns true on a good open, returns false otherwise (file doesn't exist, or otherwise is not good to open)
bool doesFileExist(string fileName)
{
    ifstream file(fileName.c_str());
    if (file.good())
    {
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

//checks if a string is raw data, or a filename
//Pre: input is whatever the user typed
//Post: if no file exists by the name of what they entered, return the raw string
//      otherwise, read the file and return its contents
string fileOrRaw(string input)
{
    ifstream f(input.c_str());
    //simply check if we were able to open a file
    if (f.good())
    {
        f.close();
        //we want the contents of the file if it existed
        return readFromFile(input);
    }
    else
    {
        f.close();
        return input;
    }
}

//reads a text file as one long string
//Pre:  fileName is the file to read from
//Post: The contents of the file are returned as a string,
//      with end-of-lines interpreted as a space
string readFromFile(string fileName)
{
    string text = "";
    string totalText = "";
    ifstream infile(fileName.c_str());
    //grab all the lines of the file and concatenate it together (newlines are converted to spaces)
    while (getline(infile, text))
    {
        totalText += text + " ";
    }
    infile.close();
    return totalText;
}
