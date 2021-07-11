//
// Created by linus on 11.07.21.
//

#ifndef LIBFTL_VEC_H
#define LIBFTL_VEC_H


#include <cstdint>
#include <malloc.h>
#include <cassert>
#include <iostream>

#include "Str.h"

/**
 * Vector (Vec) is a growable array, like Vec in Rust, std::vector in C++ or ArrayList in Java.
 */
template<class T>
class Vec {
public:
    /**
     * The raw c-array.
     */
    T* _data = nullptr;

    /**
     * The length of the array.
     */
    uint64_t _len = 0;

    /**
     * The capacity of the underlying raw array.
     */
    uint64_t _cap = 0;

    /**
     * Pushes the element onto the vector.
     */
    void push(T element) {
        _grow_if_needed();
        _push_unsafe(element);
    }

    /**
     * Returns the element at index.
     * @param index The index to get the element from.
     * @return The element or nullptr if the index exceeds the boundaries of the vector.
     */
    T* get(uint64_t index) {
        if (index >= _len) {
            std::cout << "WARN: Vec::get(): index >= _len: Returning nullptr." << std::endl;
            return nullptr;
        }
        return &_data[index];
    }

    /**
     * Returns the last element of the vector and deletes it from the vector.
     * @return The last element or nullptr if the vector is empty, i.e. no element can be popped.
     */
    T* pop() {
        if (_len == 0) {
            std::cout << "WARN: Vec::pop(): _len == 0: Returning nullptr." << std::endl;
            return nullptr;
        }
        return _pop_unsafe();
    }


    /**
     * Checks if growing is needed to insert a new element. If needed, calls _grow().
     */
    void _grow_if_needed() {
        if (_len == _cap) {
            _grow();
        }
    }

    /**
     * Grows the vector so that at least one element can be appended.
     */
    void _grow() {
        // Double capacity or set to 2 at minimum (LU stands for long unsigned)
        _cap = std::max(_len*2, 2LU);
        _resize_data_to_cap();
    }

    /**
     * Resizes _data to _cap, i.e. increases or decreases the space of _data according to _cap.
     */
    void _resize_data_to_cap() {
        // In case _data is nullptr, realloc behaves like malloc, see https://www.cplusplus.com/reference/cstdlib/realloc/
        _data = static_cast<T*>(realloc(_data, _cap * sizeof(T)));
        if (_data == nullptr) {
            std::cout << "ERROR: Vec::_grow: realloc failed, i.e. returned nullptr." << std::endl;
        }
    }

    /**
     * Adds element to the end of this vector ignoring possible buffer overflows.
     */
    void _push_unsafe(T element) {
        _data[_len] = element;
        _len++;
    }

    /**
     * Pops one element from the array by copying it to a newly allocated space, ignoring possible buffer
     * over/underflows.
     */
    T* _pop_unsafe() {
        _len--;
        T* element = malloc(sizeof(T));
        memcpy(element, _data[_len], sizeof(T));
        return element;
    }
};


#endif //LIBFTL_VEC_H
