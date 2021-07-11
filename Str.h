//
// Created by linus on 11.07.21.
//

#ifndef LIBFTL_STR_H
#define LIBFTL_STR_H


#include <cstdint>
#include <cstring>

/**
 * A wrapper around a c-string.
 */
class Str {
public:
    /**
     * The underlying raw c-string.
     */
    char* _cstr = nullptr;

    /**
     * The length of this string.
     */
    uint64_t _len = 0;

    /**
     * Creates a new Str by referencing a c-string.
     */
    Str(char* cstr) : _cstr(cstr), _len(strlen(cstr)) {}

    /**
     * Returns the char at index or `\0` if the index is out of bounds.
     */
    char charAt(uint64_t index) const;

    Str toStr() const;
};


#endif //LIBFTL_STR_H
