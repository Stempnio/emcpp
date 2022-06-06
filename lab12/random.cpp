#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
#include<mutex>
using namespace std;

template <int N>
struct Array{
    int a[N];
    std::mutex mutex;
    std::mutex mutex2;

	int f(int x){
		int y = x%11;
		return (y*y+1);
	}

	void generateArray(){
        static int i=0;
		while(i<N){
            std::lock_guard<std::mutex> lockGuard(mutex);
		    if(i<N) {
                a[i] = rand();
                i++;
            }
		}
		static int j=0;
		while(j<N){
            std::lock_guard<std::mutex> lockGuard(mutex2);
			if(j<N)  {
                a[j] = f(a[j]);
                j++;
            }
		}
	}

	long long computeSum(){
        auto sum = 0;
        for(auto x : a)
            sum += x;
        return sum;
	}
};

int main(int argc,char* argv[]){

    auto numberOfThreads = argc > 1 ? std::stoi(argv[1]) : 1;

    std::cout << "===========================" << '\n';
    std::cout << "NUMBER OF THREADS: " << numberOfThreads << '\n';
    std::cout << "===========================" << '\n';

	srand(2019);
	using A = Array<1000>;
	A array;

    std::vector<std::thread> threads;

    threads.reserve(numberOfThreads);
    for(auto i=0; i<numberOfThreads; i++)
        threads.emplace_back(std::thread(&A::generateArray, &array));

    for(auto i=0; i<numberOfThreads; i++)
        threads[i].join();

	for(int i=0; i<40; i++){
		cout << array.a[i] << "  ";
	}
	long long sum = array.computeSum();
	cout << "\nsum = " << sum << endl;
}

