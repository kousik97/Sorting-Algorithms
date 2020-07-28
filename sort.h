//
// Created by Kousik on 23-07-2020.
//

#ifndef C___SORT_H
#define C___SORT_H

#endif //C___SORT_H

#include<cassert>

static const size_t SORT_THRESHOLD = 16;
static const size_t SELECT_THRESHOLD = 128;



template <typename T>
inline int logarithm(T val){
int log = 0;
while(val >>=1){
log += 1;
}
return log;
}

template <typename I, typename BI>
void merge(I begin, I mid, I end, BI buffer){
    I low = begin;
    I high = mid;
    BI buff = buffer;
    while((low < mid)&&(high < end)){
        if(*low < *high){
            std::iter_swap(low,buff);
            ++low;
        } else{
            std::iter_swap(high,buff);
            ++high;
        }
        ++buff;
    }
    std::move(low,mid,buff);
    std::move(high,end,buff);
    std::ptrdiff_t size = (end-begin);
    std::move(buffer,std::next(buffer,size),begin);
}


template <typename I, typename BI>
void mergesortusingBuffer(I begin, I end, BI buffer){
    std::ptrdiff_t  size = std::distance(begin, end);
    if(size<2){return;}
    std::ptrdiff_t split = size/2;
    I mid = std::next(begin, split);
    BI midbuffer = std::next(buffer,split);
    mergesortusingBuffer(begin, mid, buffer);
    mergesortusingBuffer(mid,end,midbuffer);
    merge(begin,mid,end,buffer);
}

//Main MERGE SORT FUNCTION
template <typename I>
void mergesort(I begin, I end){
    using ValueType = typename std::iterator_traits<I>::value_type;
    std::ptrdiff_t size = (end-begin);
    std::vector<ValueType> buffer(size);
    mergesortusingBuffer(begin,end,buffer.begin());
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
I lomuto_partition(I begin, I end, I pivot){
    if(end -begin < 2){
        return begin;
    }
    using valuetype  = typename std::iterator_traits<I>::value_type;
    valuetype pivot_elem = *pivot;
    std::swap(*begin,*pivot); //swap 2 elems
    auto first = begin;
    do{
        ++first;
        //assert(first < end);
    } while(*first < pivot_elem);
    for(auto read = first + 1; read < end ; ++read){
        auto x = *read;
        if(x < pivot_elem){
            *read = *first;
            *first = x;
            first++;
        }
    }
    first--;
    std::swap(*begin,*first);
    return first;
}

//Branchless?
template <typename I>
I lomuto_partition_branchless(I begin, I end, I pivot){
    if(end -begin < 2){
        return begin;
    }
    end--;
    using valuetype  = typename std::iterator_traits<I>::value_type;
    valuetype pivot_elem = *pivot;
    std::swap(*begin,*pivot); //swap 2 elems
    auto first = begin;
    do{
        ++first;
        assert(first <= end);
    } while(*first < pivot_elem);
    for(auto read = first + 1; read < end ; ++read){
        auto x = *read;
        auto smaller = -int(x < pivot_elem);
        auto deal = smaller & (read - first);
        first[deal] = *first;
        read[-deal] = x;
        first -= smaller;
    }
    --first;
    std::swap(*begin,*first);
    return first;
}

//Small of two elements and swap
template<typename I>
I small(I beg, I end){
    if (*beg > *end) {std::swap(*beg,*end);};
    return beg;
}


//Median of 3 elements
template<typename I>
I median3(I m1, I m2, I m3){
    if(*m1 > *m2) {std::swap(*m1,*m2);}
    if(*m2 < *m3) {return m2;}
    if(*m3 < *m1) {return m1;}
    return m3;
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

//Bubblesort
template <typename I>
void bubblesort(I begin, I end){
    for(I it  = end; it > begin + 1; it--){
        auto max = *begin;
        for(I it2 = begin+1; it2 < it; it2++){
            auto val = *it2;
            it2[-1] = val;
            if(max < val){
                it2[-1] = max;
                max = val;
            }
            //bool is_smaller = max < val;
            //it2[-1] = is_smaller ? max : val;
            //max = is_smaller ? val : max;
        }
        it[-1] = max;
    }
}

//Bubblesort2 - Requires atleast two element
template <typename I>
void bubblesort2(I begin, I end){
    auto _x = *begin;
    auto _y = *(begin+1);
    if(_y < _x) {std::swap(_x,_y);}
    for(I it = end;it > begin + 1;it--){
        auto x = _x;
        auto y = _y;
        for(I it2 = begin+2; it2 < it;it2++){
            auto z = *it2;
            /*bool is_smaller = y <= z;
            auto w = is_smaller ? y : z;
            y = is_smaller ? z : y;
            is_smaller = x <= z;
            *(it2-2) = (is_smaller ? x : z);
            x = is_smaller ? w : x;*/
            auto w = z;
            if(y < z){
                w = y;
                y = z;
            }
            it2[-2] = z;
            if(x < z){
                it2[-2] = x;
                x = w;
            }
        }
        it[-1] = y;
        it[-2] = x;
    }
}

//Main quicksort function
template <typename I>
void quicksort(I begin, I end){
    while(end - begin > SORT_THRESHOLD){
        I pivot = small(begin,end-1);
        pivot = hoare_partition(begin,end,pivot);
        quicksort(pivot+1,end);
        end = pivot;
    }
    insertion_sort(begin,end);
}

//Heapify the vector with i as root
template <typename I>
void heapify(I begin, I end, std::ptrdiff_t i){
    std::ptrdiff_t size = (end-begin);
    std::ptrdiff_t l = 2*i + 1 >= size ? i : 2*i + 1;
    std::ptrdiff_t r = 2*i + 2 >= size ? i : 2*i + 2;
    std::ptrdiff_t largest = begin[l] > begin[r] ? l : r;
    largest = begin[i] > begin[largest] ? i : largest;
    if(largest!=i){
        std::swap(begin[i],begin[largest]);
        heapify(begin,end,largest);
    }
}

//Heapsort
template <typename I>
void heapsort(I begin, I end){
    std::ptrdiff_t size = (end-begin);
    std::ptrdiff_t i = size/2 - 1;
    while(i >= 0){
        heapify(begin,end,i);
        if(i!=0) {i--;} else{break;}
    }
    for(I it = end-1; it!=begin; it--){
        std::swap(*begin,*(it));
        heapify(begin,it,0);
    }
}



//Introsort sub function
template <typename I>
void introsort_main(I begin, I end, int depth){
    while(end - begin > SORT_THRESHOLD){
        if(depth == 0){
            heapsort(begin,end);
            break;
        } else{
            I pivot = small(begin,end-1);
            pivot = hoare_partition(begin,end,pivot);
            introsort_main(pivot+1,end,depth-1);
            end = pivot;
        }
    }
    insertion_sort(begin,end);
}

//Main intro sort function
template <typename I>
void introsort(I begin, I end){
    int max_depth = 2 * logarithm((end-begin));
    introsort_main(begin,end,max_depth);
}

template <typename I, typename T>
I binary_search(I begin, I end, T key) {
    I cop = end;
    while (std::distance(begin, end) > 0) {
        I mid = begin + (end-begin)/2;
        if (*mid == key) {
            return mid;
        } else if (*mid > key) {
            end = mid;
        } else {
            begin = mid + 1;
        }
    }
    return cop;
}
