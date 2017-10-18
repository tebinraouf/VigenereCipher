//
//  main.cpp
//  VigenereCipher
//
//  Created by Tebin on 9/16/17.
//  Copyright © 2017 Tebin. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <fstream>

using namespace std;


//Helper Functions
string GetAlphabetByNumber(int number) {
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<int, char> dictionary;
    for (int i=0; i<alpha.size(); i++) {
        dictionary[i] = alpha[i];
    }
    return &dictionary[number];
}
int GetAlphabetNumberByLetter(char letter) {
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<char, int> dictionary;
    for (int i=0; i<alpha.size(); i++) {
        dictionary[alpha[i]] = i;
    }
    return dictionary[letter];
}
vector<int> ConvertTextToNumber(string txt){
    size_t size = txt.size();
    vector<int> nums(size);
    
    for (int i=0; i<txt.size(); i++) {
        char c = txt[i];
        nums[i] = GetAlphabetNumberByLetter(toupper(c));
    }
    
    return nums;
}
string ConvertNumberToText(vector<int> nums) {
    string txt = "";
    for (int i=0; i<nums.size(); i++) {
        txt += GetAlphabetByNumber(nums[i]);
    }
    return txt;
}
bool IsLengthProper(string keyword) {
    if (keyword.length() <= 7) {
        return true;
    }else {
        return false;
    }
}
vector<int> ConvertProperKeywordToNum(string keyword) {
    
    vector<int> keyNums;
    
    if (IsLengthProper(keyword)) {
        keyNums = ConvertTextToNumber(keyword);
    }
    return keyNums;
}
string GetEncryptedText(string plainText, string keyword) {
        vector<int> plainTextNums = ConvertTextToNumber(plainText);
        vector<int> keywordNums = ConvertTextToNumber(keyword);
        
        int count = 0;
        
        vector<int> cipherTextNums(plainTextNums.size());
        
        for (int i=0; i<plainText.size(); i++) {
            
            if (count == keywordNums.size()) {
                count = 0;
            }
            
            int p = plainTextNums[i];
            int k = keywordNums[count];
            int pk = p + k;
            
            if (pk >= 26) {
                pk = pk % 26;
            }
            
            cipherTextNums[i] = pk;
            count++;
        }
        return ConvertNumberToText(cipherTextNums);
}
string GetDecryptedText(string cipherText, string keyword) {
    vector<int> cipherTextNums = ConvertTextToNumber(cipherText);
    vector<int> keywordNums = ConvertTextToNumber(keyword);
    
    vector<int> plainTextNums(cipherText.size());
    int count = 0;
    
    for (int i=0; i<cipherText.size(); i++) {
        
        if (count == keywordNums.size()) {
            count = 0;
        }
        
        int c = cipherTextNums[i];
        int k = keywordNums[count];
        int ck = c - k;
        
        if (ck < 0) {
            ck = 26 + ck;
        }
        plainTextNums[i] = ck;
        count++;
    }
    return ConvertNumberToText(plainTextNums);
}
enum Vigenere {
  Encrypt, Decrypt
};
string VigenereCipher(string text, string key, Vigenere type) {
    string result;
    
    if (IsLengthProper(key)) {
        switch (type) {
            case Encrypt:
                result = GetEncryptedText(text, key);
                break;
            case Decrypt:
                result = GetDecryptedText(text, key);
                break;
            default:
                result = "Not Valid";
                break;
        }
    } else {
        result = "Key Length must be <= 7";
    }
    return result;
}
string GetFilePathFromUser() {
    string path;
    cout << "Please enter the full file path: ";
    cin >> path;
    return path;
}
string GetFileData() {
    
    string filePath = GetFilePathFromUser();
    
    string txt;
    string resultTxt;
    
    
    ifstream inFile;
    inFile.open(filePath);
    if (!inFile) {
        cout << "Unable to open file \n";
        exit(1); // terminate with error
    }
    
    inFile >> resultTxt;
    
    while (inFile >> txt) {
        resultTxt += txt;
    }
    
    inFile.close();
    return resultTxt;
}
int main(int argc, const char * argv[]) {

    string txt = GetFileData();
    
    string key = "tebeen";
    
    auto cipher = VigenereCipher(txt, key, Encrypt);
    
    cout << "Cipher Text: " << cipher << '\n';
    
    
    auto plain = VigenereCipher(cipher, key, Decrypt);
    cout << "Plain Text: " << plain << '\n';
    
    return 0;
}




////Result - Success
//
//Please enter the full file path: /Users/Tebin/Desktop/C++/plain.txt
//Cipher Text: MLJWMFFCGMPR
//Plain Text: THISISMYFILE
//
////Result - Key Length Error
//
//Please enter the full file path: /Users/Tebin/Desktop/C++/plain.txt
//Cipher Text: Key Length must be <= 7
//Plain Text: Key Length must be <= 7
//
////Result - File Error
//
//Please enter the full file path: /Users/Tebin/Desktop/C++/plain.txtaaa
//Unable to open file

