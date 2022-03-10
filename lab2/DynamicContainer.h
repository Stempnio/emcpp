#pragma once
#include <iostream>
#include "Box.h"

class Container{
    // Exercise 2: Use smart pointer.
    Box * pbox = nullptr;
public:
    static bool verbose;
    Container(int content): pbox(new Box){
        if(verbose) std::cout << "Creating Container" << std::endl;
        pbox->setContent(content);
    }
    Container(const Container & container): pbox(new Box{*(container.pbox)}){
        if(verbose) std::cout << "Creating copy of Container\n";
    }
    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) std::cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }
    ~Container(){
        if(verbose) std::cout << "Destroying Container \n";
        delete pbox;
    }
    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
