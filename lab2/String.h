#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;

class String{
   using string = emcpp::MyString;
//    using string = std::string;

/// Store a pointer to dynamically allocated string!
    std::shared_ptr<string> ptr = nullptr;
public:
    String() {
        ptr = std::make_shared<string>();
    }     /// creates an empty string

    String(const char * str) {
        ptr = std::make_shared<string>(str);
    }           /// copy C-string

    String(const String & s) {
        this->ptr = s.ptr;
    }            /// no copy

    String& operator=(const String & s) {
        if(this != &s) {
            this->ptr = s.ptr;
        }
        return *this;
    } /// no copy

    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
        if(ptr.use_count() > 1) {
            ptr = std::make_shared<string>(*ptr);
        }

        ptr->at(index) = ch;
    }

    /// no copy
    char get(int index) const {
        return ptr->at(index);
    }

    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {
        if( !( a.ptr->empty() || b.ptr->empty() ) ) {
            auto tmp = *(a.ptr) + *(b.ptr);
            return { tmp.data() };
        } else if(!a.ptr->empty()) {
            return a;
        } else {
            return b;
        }
    }

    friend std::ostream & operator<< (std::ostream & out, String s) {
        out << s.ptr->data();
        return out;
    }
};
