#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template<typename Container>
double calcMedian(Container set, std::random_access_iterator_tag) {
    std::sort(set.begin(), set.end());
    auto size = set.size();
    if(size%2 != 0)
        return set[size/2];
    else
        return (set[size/2] + set[(size/2)-1])/2.;
}

template<typename Container>
double calcMedian(Container set, std::forward_iterator_tag) {
    set.sort();
    auto evenSize = set.size() %2 == 0;

    auto limit = !evenSize ? set.size()/2 : (set.size()/2)-1;
    auto it = set.begin();

    std::advance(it, limit);
//    for(auto i = 0; i < limit; i++)
//        it++;

    return !evenSize ? *it : ( *it + *(++it) ) / 2.;
}

template<typename Container>
double median(Container set) {
//    return calcMedian(set,typename std::iterator_traits<decltype(set.begin())>::iterator_category());
    return calcMedian(set,typename std::iterator_traits<typename Container::iterator>::iterator_category());
}

int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    std::cout << median(a) << std::endl; // 3
    std::vector<int> v{3, 1, 4, 2};
    std::cout << median(v) << std::endl; // 2.5
}
