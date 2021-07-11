//
// Created by linus on 11.07.21.
//

#ifndef LIBFTL_STRJOIN_H
#define LIBFTL_STRJOIN_H

#include "StrBuf.h"
#include "Str.h"

class StrJoin {
public:
    StrBuf strbuf;
    Str join;

    StrJoin(Str join) : join(join) {}


    void add(Str str);

    /**
     * Inserts `join` if strbuf is not empty.
     */
    void _insert_join_if_not_empty();

    /**
     * Converts the contents to a str.
     */
    Str toStr() const;
};


#endif //LIBFTL_STRJOIN_H
