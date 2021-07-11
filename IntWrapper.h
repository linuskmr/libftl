//
// Created by linus on 11.07.21.
//

#ifndef LIBFTL_INTWRAPPER_H
#define LIBFTL_INTWRAPPER_H

#include <malloc.h>
#include <string>

#include "Str.h"


/**
 * Wraps an int with a toStr() method.
 */
class IntWrapper {
public:
    int value = 0;

    IntWrapper(int value): value(value) {}

    /**
     * Converts this int to a str.
     */
    Str toStr() const;
};


#endif //LIBFTL_INTWRAPPER_H
