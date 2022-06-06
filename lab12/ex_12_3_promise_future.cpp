#include <iostream>
#include <fstream>
#include <future>
#include <utility>
#include <vector>
#include <mutex>

class FileCounts {
    std::vector<std::pair<std::string, long long>> counts;
    int remainingJoins;
    std::mutex mutex;

    void findPairs() {
        for(auto i=0; i<counts.size(); i++) {
            for(auto j=i+1; j<counts.size(); j++) {
                if(counts[i].second == counts[j].second) {
                    std::cout << "Pair: [" << counts[i].first << "] and [" << counts[j].first << "]\n";
                }
            }
        }
    }

public:

    explicit FileCounts(int remainingJoins) : remainingJoins(remainingJoins) {}

    void add(const std::string& s, long long x) {
        mutex.lock();
        auto p = std::make_pair(s, x);
        counts.emplace_back(p);
        remainingJoins--;

        if(remainingJoins <= 0) {
            findPairs();
        }
        mutex.unlock();
    }
};

class CharCounter {
    std::promise<long long> countPromise;
    std::future<long long> countFuture;
    std::thread thread;
    std::string path;
    FileCounts& fc;

    auto countCharactersInFile() {
        std::ifstream file;
        file.open(path, std::ios::in);

        if(file.good()) {
            long long sum = 0;

            char c;
            file.get(c);

            while (!file.eof()) {
                if (c != '\n')
                    sum += c;

                file.get(c);
            }

            countPromise.set_value(sum);
        } else {
            std::cerr << "Error while opening file" << '\n';
        }
    }

public:

    explicit CharCounter(std::string path, FileCounts& fc) : path(std::move(path)), fc(fc) {
        thread = std::thread(&CharCounter::countCharactersInFile, this);
        countFuture = countPromise.get_future();
    }

    ~CharCounter() {
        thread.join();
        auto sum = countFuture.get();
        std::cout << "File: " << path << '\n';
        std::cout << "Sum of characters: " << sum << '\n';
        std::cout << "----------\n";
        fc.add(path, sum);
    }

};

int main(int argc,char* argv[]) {

    if(argc == 1) {
        std::cout << "No paths given, exiting program...";
        exit(1);
    }

    auto fc = FileCounts{argc-1};

    for(auto i=1; i<argc; i++)
        CharCounter{argv[i], fc};

}