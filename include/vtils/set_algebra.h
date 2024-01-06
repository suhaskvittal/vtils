/*
 *  author: Suhas Vittal
 *  date:   25 December 2023
 * */

#ifndef VTILS_SET_ALGEBRA_h
#define VTILS_SET_ALGEBRA_h

#include <set>

// Useful operator overloads:
namespace vtils {

template <class T> std::set<T>  operator+(std::set<T>, std::set<T>)
template <class T> std::set<T>  operator-(std::set<T>, std::set<T>)
template <class T> std::set<T>  operator*(std::set<T>, std::set<T>)
template <class T> std::set<T>  operator^(std::set<T>, std::set<T>)

template <class T> std::set<T>& operator+=(std::set<T>&, std::set<T>);
template <class T> std::set<T>& operator-=(std::set<T>&, std::set<T>);
template <class T> std::set<T>& operator*=(std::set<T>&, std::set<T>);
template <class T> std::set<T>& operator^=(std::set<T>&, std::set<T>);

template <class T> std::set<T>& operator+=(std::set<T>&, T);
template <class T> std::set<T>& operator-=(std::set<T>&, T);
template <class T> std::set<T>& operator^=(std::set<T>&, T);

}   // vtils

#include "set_algebra.inl"

#endif  // VTILS_SET_ALGEBRA_h
