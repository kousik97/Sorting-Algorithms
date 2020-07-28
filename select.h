//
// Created by Kousik on 20-07-2020.
//

#ifndef C___ALGOS_H
#define C___ALGOS_H

#endif //C___ALGOS_H

#include<cassert>
static const size_t SELECT_THRESHOLD = 32;

template <class I>
I select(I, I, std::size_t, I(I, I, I), void(I, I));

template<typename I>
void small(I beg, I end){
    if (*beg > *end) {std::swap(*beg,*end);};
    return;
}

//Partition 2 pointer style
template <typename I>
I hoare_partition(I begin, I end, I pivot){
    --end;
    auto val = *pivot;
    std::swap(*begin,*pivot);
    I first = begin, last = end;
    for(;;){
        ++first;
        auto f = *first;
        while(f < val){
            f = *++first;
        }
        auto l = *last;
        while(l > val){
            l = *--last;
        }
        if(first >= last){
            break;
        }
        *first = l;
        *last = f;
        --last;
    }
    --first;
    std::swap(*first,*begin);
    return first;
}

template<typename I>
void unguarded_linear_insert(I last) {
    auto val = *last;
    --last;
    auto x = *last;
    if (val >= x)
        return;
    for (;;) {
        last[1] = x;
        --last;
        x = *last;
        if (val >= x)
            break;
    }
    last[1] = val;
}

template<typename I>
void insertion_sort(I first, I last) {
    for (I i = first + 1; i < last; ++i) {
        auto val = *i;
        if (val < *first) {
            size_t n = i - first - 1;
            do {
                first[n + 1] = first[n];
            }
            while (n--);
            *first = val;
        }
        else
            unguarded_linear_insert(i);
    }
}

template <typename I>
void easy_median(I begin, I end){
    insertion_sort(begin, end);
}

template <typename  I>
void empty(I m1, I m2){
    return;
}

template <typename I>
I BFPRT(I begin, I end) {
    std::size_t size = end - begin;
    while (size >= 5) {
        std::size_t i = 0, j = 0;
        while (i + 4 < size) {
            easy_median(begin + i, begin + i + 5);
            std::swap(*(begin + i + 2), *(begin + j));
            i += 5;
            j += 1;
        }
        size = j;
        //end = begin + j;
    }
    easy_median(begin, begin + size);
    return hoare_partition(begin,end,begin + size/2);
}

template <class I>
I modified_hoare(I begin, I end){
    small(begin, end-1);
    return hoare_partition(begin, end, begin);
}

template <typename I>
I repeated_step(I begin, I end){
    std::size_t size = end - begin;
    while (size >= 9) {
        std::size_t i = 0, j = 0, m=0;
        while (i + 2 < size) {
            easy_median(begin + i, begin + i + 3);
            std::swap(*(begin + i + 1), *(begin + j));
            i += 3;
            j += 1;
        }
        i=0;
        while(i+2 < j){
            easy_median(begin + i, begin + i + 3);
            std::swap(*(begin + i + 1), *(begin + m));
            i += 3;
            m += 1;
        }
        size = m;
    }
    easy_median(begin, begin + size);
    return hoare_partition(begin,end,begin + size/2);
}

template <typename T>
inline int logarithm(T val){
    int log = 0;
    while(val >>=1){
        log += 1;
    }
    return log;
}

template <typename I>
I select(I begin, I end, std::size_t order, I partition(I, I)){
    int attempts = 0;
    int cap = logarithm(end - begin);
    while(true){
        I pivot = partition(begin,end);
        std::size_t num = pivot-begin;
        if(num+1 == order){
            return pivot;
        } else if(num + 1 > order){
            end = pivot;
        } else{
            begin = pivot+1;
            order -= (num+1);
        }
        attempts++;
        if(attempts > cap){
            partition = BFPRT;
        }
    }
}

template <typename I>
I select(I begin, I end, std::size_t order){
    return select(begin, end, order, modified_hoare);
}

