/*
 *  author: Suhas Vittal
 *  date:   25 December 2023
 * */

#ifndef VTILS_TWO_LEVEL_MAP_h
#define VTILS_TWO_LEVEL_MAP_h

#include <map>

namespace vtils {

template <class T, class U, class V> using TwoLevelMap = std::map<T, std::map<U, V>>;

template <class T, class U, class V> inline void
tlm_put(TwoLevelMap<T, U, V>& m, T x, U y, V z) {
    if (!m.count(x))    m[x] = std::map<U, V>();
    m[x][y] = z;
}

}   // vtils

#endif  // VTILS_TWO_LEVEL_MAP_h
