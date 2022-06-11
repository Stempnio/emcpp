#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

template<typename T>
class Range {
    size_t size;
    T* array;

    size_t calculateSize(T _start, T _stop, T _step) {
        auto result = 0;

        for(auto i=_start; i<_stop; i+=_step)
            result += 1;

        return result;
    }

    template<typename Range>
    class RangeIterator {
    public:
        using ValueType = T;
//        using ValueType = typename Range::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        RangeIterator(PointerType ptr): ptr(ptr) {}

        RangeIterator& operator++() {
            ptr++;
            return *this;
        }

        RangeIterator operator++(int) {
            auto iterator = *this;
            ++(*this);
            return iterator;
        }

        PointerType operator->() {
            return ptr;
        }

        ReferenceType operator*() {
            return *ptr;
        }

        bool operator==(const RangeIterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const RangeIterator& other) const {
            return ptr != other.ptr;
        }

    private:
        PointerType ptr;
    };
public:

//    using ValueType = T;
    using Iterator = RangeIterator<Range<T>>;

    Range(T start, T stop, T step=1){
        size = calculateSize(start, stop, step);
        array = new T(size);

        auto it = 0;
        for(auto i=start; i<stop; i+=step)
            array[it++] = T(i);
    }

    Range(T stop) {
        size = calculateSize(0,stop, 1);
        array = new T(size);

        auto it = 0;
        for(auto i=0; i<stop; i++)
            array[it++] = T(i);
    }

    Iterator begin() {
        return Iterator(array);
    }

    Iterator end() {
        return Iterator(array + size);
    }

};

template<typename T>
Range<T> make_range(T start, T stop, T step) {
    return Range(start, stop, step);
}

template<typename T>
Range<T> make_range(T stop) {
    return Range(stop);
}


//template<typename T>
//class Range {
//    std::vector<T> vector;
//public:
//
//    Range(T start, T stop, T step=1) {
//        for(auto i=start; i<stop; i+=step)
//            vector.emplace_back(i);
//    }
//
//    Range(T stop) {
//        for(auto i=0; i<stop; i++)
//            vector.emplace_back(i);
//    }
//
//    typename std::vector<T>::iterator begin() {
//        return vector.begin();
//    }
//
//    typename std::vector<T>::iterator end() {
//        return vector.end();
//    }
//};


#endif //LAB6_RANGE_H;