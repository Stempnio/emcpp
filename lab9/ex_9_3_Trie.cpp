#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Trie{
    std::map<std::string, Trie> data;

    void addSentence(const std::vector<std::string>  & sentence, int i=0) {
        if(sentence.size() > i) {
            auto search = data.find(sentence[i]);

            // element already in map
            if (search != data.end()) {
                search->second.addSentence(sentence, i+1);
            } else {
                Trie newTrie = {};
                newTrie.addSentence(sentence, i+1);
                data.emplace(sentence[i], newTrie);
            }
        }
    }

    void printEnding(std::string result) {
        if(!data.empty()) {
            std::for_each(data.begin(), data.end(), [result](auto p){
                std:string tmp = result;
                tmp.append(p.first);
                tmp.append(" ");
                p.second.printEnding(tmp);
            });
        } else {
            std::cout << result << std::endl;
        }
    }

    void findLastElementOfBeginningSentence(const std::vector<std::string>& beginningOfSentence, int i) {
        if(beginningOfSentence.size() > i) {
            auto search = data.find(beginningOfSentence[i]);

            if (search != data.end()) {
                if(beginningOfSentence.size()-1 == i)
                    search->second.printEnding("");
                else
                    search->second.findLastElementOfBeginningSentence(beginningOfSentence, i + 1);
            }
        }
    }

public:
    static void printSentence(const std::vector<std::string>  & sentence ) {
        for (const auto &w: sentence)
            cout << w << " ";
    }

    void add(const std::vector<std::string>  & sentence ){
        cout << "Adding : ";
        printSentence(sentence);
        cout << "\n";

        addSentence(sentence);
    }

    void printPossibleEndings(const std::vector<std::string>& beginningOfSentence ){
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are :\n";
        findLastElementOfBeginningSentence(beginningOfSentence, 0);
    }

    void load(const std::string & fileName){
        ifstream file(fileName);
        if(!file){
            cerr << "Error when opening file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while( file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if(word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }
};


int main(){

    Trie dictionary;
    dictionary.load("/Users/jakubstepien/Desktop/6-semestr/EMCPP/zadania-rozwiazania/lab9/sample.txt");
    //dictionary.load("hamletEN.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */