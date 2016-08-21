#ifndef _A_H_
#define _A_H_

#include <string>
#include <vector>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <iostream>

class A
{
public:
    A();
    virtual ~A();


    template <typename T>
    A(T val) :   size(sizeof(T))  {
    	std::cout << __PRETTY_FUNCTION__ << std::endl;
     }

    template <typename T>
    operator T() const {
    	std::cout << __PRETTY_FUNCTION__ << std::endl;
        return 1;
    }

    const unsigned int size;

    friend std::ostream& operator<< (std::ostream& os, const A&);
};

#endif
