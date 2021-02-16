#pragma once

/* resources and credit:

http://akrzemi1.wordpress.com/2012/03/19/meta-functions-in-c11/
http://bartoszmilewski.com/2009/10/21/what-does-haskell-have-to-do-with-c/
http://bartoszmilewski.com/2011/01/09/monads-for-the-curious-programmer-part-1/
http://bartoszmilewski.com/2011/07/11/monads-in-c/
*/

namespace pre {

// count

template<class... list>
struct count;

template<>
struct count<> {
  static const int value = 0;
};

template<class head, class... tail>
struct count<head, tail...> {
  static const int value = 1 + count<tail...>::value;
};

template<template<class> class f1, template<class> class f2>
struct or_combinator {
  template<class T>
  struct lambda {
    static const bool value = f1<T>::value || f2<T>::value;
  };
};

// all
template<template<class> class predicate, class... list> struct
all;

template<template<class> class predicate> struct
all<predicate> {
    static const bool value = true;
};

template<
    template<class> class predicate, 
    class head, 
    class... tail> struct
all<predicate, head, tail...> {
    static const bool value = 
        predicate<head>::value 
        && all<predicate, tail...>::value;
};

// fold_right

template<template<class, int> class, int, class...> struct
fold_right;

template<template<class, int> class f, int init> struct
fold_right<f, init> {
    static const int value = init;
};

template<template<class, int> class f, int init, class head, class...tail> struct
fold_right<f, init, head, tail...> {
    static const int value = f<head, fold_right<f, init, tail...>::value>::value;
};

} // namespace pre