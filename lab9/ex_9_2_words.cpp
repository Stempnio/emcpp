#include <iostream>
#include <vector>
#include <map>
#include <fstream>

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    std::transform(s1.begin(), s1.end(), s1.begin(),
                   [](char c) { return std::tolower(c); });
    s1.erase(std::remove_if(s1.begin(),
                            s1.end(),
                            [](unsigned char c) { return !std::isalnum(c); }),
             s1.end());
}

int main(){
    int count = 0;
    std::string word;
    std::map<std::string, int> m;

    std::fstream file("/Users/jakubstepien/Desktop/6-semestr/EMCPP/zadania-rozwiazania/lab9/hamletEN.txt");

    while( file >> word) {
       toLowerAlpha(word);

       if(!word.empty()){
           if(m[word]++ == 0) {
               count++;
           }
       }
    }
    std::multimap<int, std::string, std::greater<>> m2;

    std::for_each(m.begin(), m.end(), [&m2](const std::pair<std::string, int>& p){
        m2.emplace(p.second, p.first);
    });

    std::cout << "Number of distinct words : " << count << std::endl;
    std::cout << "\nThe top 20 most popular words: \n";

    std::for_each(m2.begin(), std::next(m2.begin(), 20), [](auto p){
        std::cout << p.second << " : " << p.first << std::endl;
    });

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */