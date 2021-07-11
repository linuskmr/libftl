//
// Created by linus on 11.07.21.
//

#include "StrJoin.h"

void StrJoin::_insert_join_if_not_empty() {
    if (!strbuf.isEmpty()) {
        strbuf.add(join);
    }
}

void StrJoin::add(Str str) {
    _insert_join_if_not_empty();
    strbuf.add(str);
}

Str StrJoin::toStr() const {
    return strbuf.toStr();
}
