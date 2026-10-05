#include "markov.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cstdlib>

using namespace std;

string joinWords(const string words[], int startIndex, int count){
    // open empty string to add words to and return later
    string temp = "";
    
    // check index is positive and within limits of array sizes
    if(startIndex < 0 /*|| (startIndex + count) > (sizeof(words))*/){ return temp; }
    
    // take elements of words[] at starting index for
    for(int i = 0; i < count; i++){
        temp = temp + words[startIndex + i];
        if(i != count - 1){
            temp = temp + " ";
        }
    }
    
    // return a string with words selected
    return temp;
}


int readWordsFromFile(string filename, string words[], int maxWords){
    
    // open file
    ifstream inputFile;
    inputFile.open(filename);
    
    // check if file is open, return -1 if not
    if(!inputFile.is_open()){ return -1; }
    
    // initialize count
    int count = 0;
    
    // counts the amount of words in file, stopping if max is reached
    while(count < maxWords && inputFile >> words[count]){
        count++;
    }
    
    // close file
    inputFile.close();
    
    // return word count
    return count;
}

int buildMarkovChain(const string words[], int numWords, int order, string prefixes[], string suffixes[], int maxChainSize){
    
    // checks conditions of order between 1-3, words used is less than or equal to order checked, and max size is positive, if not return 0
    if(order > 3 || order < 1 || numWords <= order || maxChainSize <= 0){ return 0; }
    
    // initialize count to be returned and loop variable
    int count = 0;
    int i = 0;
    string prefix, suffix;
    
    // loop to add prefixes and suffixes from words array and check each time until selected size is reached or max chain
    while(i <= (numWords - order) && count < maxChainSize){
        // find words before placement
        prefix = joinWords(words, i, order);
//        cout << endl << prefix << endl;
        // find words after placement
        suffix = words[i + order];
//        cout << suffix;
        // save prefixes and suffixes
        prefixes[count] = prefix;
        suffixes[count] = suffix;
        // increment for next loop
        count++;
        i++;
    }
    
    cout << endl << "prefix size: " << prefixes->length() << endl;
    cout << endl << "suffix size: " << suffixes->length() << endl;
    // return count of how many additions were made to prefixes and suffixes
    return count;
}


string getRandomSuffix(const string prefixes[], const string suffixes[], int chainSize, string currentPrefix){
    
    // initialize the counter for matches
    int matchCount = 0;
    
    // check each prefix if it matches the current prefix and count
    for(int i = 0; i < chainSize; i++){
        if(prefixes[i] == currentPrefix){ matchCount++; }
    }
    
    // return blank if chainSize is not positive or no matches are found
    if(chainSize <= 0 || matchCount == 0){ return ""; }
    
    // generate a random integer from 0 to match count and initialize a new count
    int pick = rand() % matchCount;
    int match = 0;
    
    // run through prefixes again and return suffix when random number is reached
    for(int i = 0; i < chainSize; i++){
        if(prefixes[i] == currentPrefix){ match++; }
        if((match - 1) == pick){ return suffixes[i]; }
    }
    
    // return blank if random match is not found
    return "";
}

string getRandomPrefix(const string prefixes[], int chainSize){
    
    // return blank if chainSize is not positive
    if(chainSize <= 0){ return ""; }
    
    // find random integer from 0 to chainSize
    int index = rand() % chainSize;
    
    // return the prefix with random index
    return prefixes[index];
}


string generateText(const string prefixes[], const string suffixes[], int chainSize, int order, int numWords){
    
    if(chainSize <= 0 || order < 1 || order > 3 || numWords < order){ return ""; }
    
    string currentPrefix = getRandomPrefix(prefixes, chainSize);
    
    string result = currentPrefix;
    
    string currentWords[3];
    int wordIndex = 0;
    string temp = "";
    
    for(int i = 0; i < currentPrefix.length(); i++){
        if(currentPrefix == " "){
            currentWords[wordIndex] = temp;
            wordIndex++;
            temp = "";
        }
        else {
            temp += currentPrefix[i];
        }
    }
    
    currentWords[wordIndex] = temp;
    string newWord;
    
    for(int i = 0; i < numWords - order; i++){
        newWord = getRandomSuffix(prefixes, suffixes, chainSize, currentPrefix);
        
        if(newWord == ""){ break; }
        
        result += " ";
        result += newWord;
        
        for(int j = 0; j < (order - 1); j++){
            currentWords[j] = currentWords[j + 1];
        }
        
        currentWords[order - 1] = newWord;
        currentPrefix = joinWords(currentWords, 0, order);
    }
    
    return result;
    
}
