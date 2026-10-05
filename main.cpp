#include <iostream>
#include <fstream>
#include <string>
#include "markov.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, const char * argv[]) {
    
    // testing
/*    string words[] = {"the", "cat", "sat", "down"};
    
    cout << endl << joinWords(words, 0, 2) << endl;
    cout << endl << joinWords(words, 1, 2) << endl;
    cout << endl << joinWords(words, 1, 3) << endl;
*/
    
/*    string fixes[] = {"the", "cat", "sat", "down"};
    string prefixes[2];
    string suffixes[2];
    
    cout << endl << buildMarkovChain(fixes, 4, 2, prefixes, suffixes, 5) << endl;
    for(int i = 0; i < 2; i++){
        cout << "prefix: " << prefixes[i] << ", suffix: " << suffixes[i] << endl;
    }
*/
    
    // establish a random reference
    srand(time(0));
    string fileName = "taylor-swift-all-lyrics.txt";
    
/*    string prefixes[]  = {"the", "cat", "the", "the"};
    string suffixes[] = {"cat", "sat", "dog", "bird"};
    string currentPrefix = "the";
    
    getRandomSuffix(prefixes, suffixes, 5, currentPrefix);
    
    
    cout << endl << getRandomSuffix(prefixes, suffixes, 4, currentPrefix) << endl;
*/
/*
    // step 2
    // implement joinWords test
    string testWords[] = {"the", "cat", "sat", "down"};
    cout << joinWords(testWords, 0, 2) << endl; // expect: the cat
    cout << joinWords(testWords, 1, 3) << endl; // expect: cat sat down
    // passed
    
    // step 3
    // impliment readWordsFromFile test
    string words[1000];
    int count = readWordsFromFile(fileName, words, 1000);
    cout << "Read " << count << " words" << endl;
    for(int i = 0; i < 10 && i < count; i++){
        cout << words[i] << endl;
    }
    // passed
    
    // step 4
    // implement buildMarkovChain test
    string prefixes[1000], suffixes[1000];
    int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 1000);
//    cout  << endl << endl << prefixes[10] << endl << endl;
    for(int i = 0; i < 20 && i < chainSize; i++){
        cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << endl;
    }
    // passed
    
    // step 5
    // impliment getRandomSuffix test
    for(int i = 0; i < 10; i++){
        cout << getRandomSuffix(prefixes, suffixes, chainSize, "a") << endl;
    }
    // passed
    
    // step 6
    // impliment getRandomPrefix test
    for(int i = 0; i < 5; i++){
        cout << getRandomPrefix(prefixes, chainSize) << endl;
    }
    // passed
    
    // step 7
    // impliment generateText
    string output = generateText(prefixes, suffixes, chainSize, 1, 10);
    cout << output << endl;
    // passed
*/
    // step 8
    // complete main
    // initialize variables and bools for tests
    string file;
    int inputOrder;
    bool validOrder = false;
    int numWords;
    bool validNum = false;
    
    // input  filename to be used
//    cout << "Enter input filename: ";
//    cin >> file;
    cout << endl;
    file = "taylor-swift-all-lyrics.txt";
    // loop until valid order of 1, 2, or 3 is inputed
    while(!validOrder){
        cout << "Enter order (1, 2, or 3): ";
        cin >> inputOrder;
        cout << endl;
        if(inputOrder >= 1 && inputOrder <= 3){ validOrder = true; }
    }
    
    // loop until maxWords being positive and greater than order is met
    while(!validNum){
        cout << "Enter number of words to generate: ";
        cin >> numWords;
        cout << endl;
        if(numWords > 0 && numWords > inputOrder){ validNum = true; }
    }
    
    // set max words limit and declare arrays with this size
    int MAX_WORDS = 5000;
    string words[MAX_WORDS], prefixes[MAX_WORDS], suffixes[MAX_WORDS];
    
    // open file and create words array, return -1 if not opened, end program if word count is too small for order
    int count = readWordsFromFile(file, words, MAX_WORDS);
    if(count == -1){
        cout << "File was not opened" << endl;
    }
    else if(count <= inputOrder){
        cout << "At least order + 1 training words are requred" << endl;
        return 0;
    }
    
    // build Markov Chain to fill in prefixes, suffixes and save amount of indexes created. If max is reached explain
    int chainSize = buildMarkovChain(words, numWords, inputOrder, prefixes, suffixes, MAX_WORDS);
    if(chainSize <= 0){
        return 0;
    }
    else if(chainSize == MAX_WORDS){
        cout << "Size filled to capacity of: " << MAX_WORDS << ". Any further words ignored" << endl;
    }
    
    // generate an output text using supplied words array, prefix and suffix arrays, and state how many words were given. If max is reached explain
    cout << "One possible run using input file to train:" << endl;
    string output = generateText(prefixes, suffixes, chainSize, inputOrder, numWords);
    cout << output << endl;
    cout << "Number of words made: " << chainSize << endl;
    if(chainSize < numWords){
        cout << "Generated " << chainSize << " of at most " << MAX_WORDS << " words. Stopped early: no successor for \"" << "\"" << endl;
    }
    
    return 0;
}
