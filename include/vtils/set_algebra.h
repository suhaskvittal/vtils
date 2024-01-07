/*
 *  author: Suhas Vittal
 *  date:   25 December 2023
 * */

#ifndef VTILS_SET_ALGEBRA_h
#define VTILS_SET_ALGEBRA_h

#include <set>

// Useful operator overloads:
namespace std {

template <class T> set<T>  operator+(set<T>, set<T>);
template <class T> set<T>  operator-(set<T>, set<T>);
template <class T> set<T>  operator*(set<T>, set<T>);
template <class T> set<T>  operator^(set<T>, set<T>);

template <class T> set<T>& operator+=(set<T>&, set<T>);
template <class T> set<T>& operator-=(set<T>&, set<T>);
template <class T> set<T>& operator*=(set<T>&, set<T>);
template <class T> set<T>& operator^=(set<T>&, set<T>);

template <class T> set<T>& operator+=(set<T>&, T);
template <class T> set<T>& operator-=(set<T>&, T);
template <class T> set<T>& operator^=(set<T>&, T);

}   // std

#include "set_algebra.inl"

#endif  // VTILS_SET_ALGEBRA_h
