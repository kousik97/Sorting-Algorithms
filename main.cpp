#include <iostream>
#include<vector>
#include<memory>
#include<utility>
#include<iterator>
#include<random>
#include<algorithm>
#include<chrono>

#include "sort.h"

/*
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    std::uniform_int_distribution<unsigned long long> distr;
    distr(eng)
    T q=std::numeric_limits<T>::max();

 */

template <class T>
void sorted(T begin, T end){
    for(T it = begin + 1;it!=end;it++){
        if(*it > *(it+1)) {std::cout << *it <<  std::endl << *(it + 1) << std::endl << std::distance(begin,it); return; }
    }
}



int main(){
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr;
    auto sort = 0;
    std::vector<double> a = {};
    long long int i = 0;
    while (i < 10000000) {a.push_back(-i); i++;}
    for(int j = 0; j<10; j++){
        std::shuffle(a.begin(),a.end(),std::default_random_engine(1947));
        auto t1 = std::chrono::high_resolution_clock::now();
        introsort(a.begin(),a.end());
        auto t2 = std::chrono::high_resolution_clock::now();
        sort += std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        std::cout << std::is_sorted(a.begin(),a.end());
    }
    std::cout << std::endl << sort/10;

}






