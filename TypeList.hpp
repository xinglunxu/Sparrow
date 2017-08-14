//
//  TypeList.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/29/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef TypeList_hpp
#define TypeList_hpp

#include <stdio.h>

using namespace std;

template <typename ... TS>
class TypeList{
public:
    template<typename TypeVisitor, typename CumulativeType>
    static CumulativeType CumulateTypes();
    
    template<typename TypeVisitor, typename CumulativeType>
    constexpr static CumulativeType ConstCumulateTypes();
    
    static constexpr int Size();
    
private:
    template<typename TypeVisitor, typename CumulativeType, typename T, typename ...Ts>
    static CumulativeType _CumulateTypes(typename enable_if<sizeof...(Ts)!=0, int>::type i=0);
    
    template<typename TypeVisitor, typename CumulativeType, typename T>
    static CumulativeType _CumulateTypes();
    
    template<typename TypeVisitor, typename CumulativeType>
    static CumulativeType _CumulateTypes();
};

template<typename ... TS>
template <typename TypeVisitor, typename CumulativeType>
CumulativeType TypeList<TS...>::CumulateTypes(){
    return _CumulateTypes<TypeVisitor, CumulativeType, TS...>();
}

template<typename ... TS>
template<typename TypeVisitor, typename CumulativeType, typename T, typename ...Ts>
CumulativeType TypeList<TS...>::_CumulateTypes(typename enable_if<sizeof...(Ts)!=0, int>::type i){
    return TypeVisitor::Concatenate(TypeVisitor::template Visit<T>(), _CumulateTypes<TypeVisitor, CumulativeType, Ts...>());
}

template<typename ... TS>
template<typename TypeVisitor, typename CumulativeType, typename T>
CumulativeType TypeList<TS...>::_CumulateTypes(){
    return TypeVisitor::template Visit<T>();
}

template<typename ... TS>
template<typename TypeVisitor, typename CumulativeType>
CumulativeType TypeList<TS...>::_CumulateTypes(){
    return CumulativeType();
}



template<typename ... TS>
template <typename TypeVisitor, typename CumulativeType>
constexpr CumulativeType TypeList<TS...>::ConstCumulateTypes(){
    return _CumulateTypes<TypeVisitor, CumulativeType, TS...>();
}


template <typename ...TS>
constexpr int TypeList<TS...>::Size(){
    return sizeof...(TS);
};

//template programming utitly------------------------------------

/// base template programming
template<typename bType1, typename bType2>
struct Or: true_type{};

template<>
struct Or<false_type, false_type> : false_type{};


template<bool b1, bool b2>
struct And:false_type{};

template <>
struct And<true, true>:true_type{};

///

///if type is contained inside container class
template < typename Tp, typename... List >
struct contains : std::true_type {};

template < typename Tp, typename Head, typename... Rest >
struct contains<Tp, Head, Rest...>
: std::conditional< std::is_same<Tp, Head>::value,std::true_type,contains<Tp, Rest...>>::type {};

template < typename Tp >
struct contains<Tp> : std::false_type {};


template <typename List, typename T>
struct ListContains{};

template <typename T, typename ...TS>
struct ListContains<TypeList<TS...>, T> : contains<T, TS...>{};
///


///if typelist is contained inside another one
template <typename Parent, typename ...TS>
struct _TypeContainType{};

template <typename Parent, typename T, typename ...TS>
struct _TypeContainType<Parent, T, TS...>{
    typedef And<_TypeContainType<Parent, T>::value::value,  _TypeContainType<Parent, TS...>::value::value> value;
};

template <typename Parent, typename T>
struct _TypeContainType<Parent, T>{
    typedef ListContains<Parent, T> value;
};


template <typename Parent, typename Child>
struct TypeContainType{};

template <typename Parent, typename ...TS>
struct TypeContainType<Parent, TypeList<TS...>>:_TypeContainType<Parent, TS...>::value{};

///

template <typename T, typename ...TS>
struct CombineType{
    
};
template<typename ...TS>
struct CombineType<TS...>{
    typedef TypeList<TS...> valueTypeList;
};

template <bool b,typename T, typename ...TS>
struct _CombineTypeIfNotRepeat{

};

template<typename T, typename ...TS>
struct _CombineTypeIfNotRepeat<true, T, TS...>{
    typedef TypeList<TS...> valueTypeList;
};

template<typename T, typename ...TS>
struct _CombineTypeIfNotRepeat<false, T, TS...>{
    typedef typename CombineType<T, TS...>::valueTypeList valueTypeList;
};

template <typename T, typename ...TS>
struct CombineTypeIfNotRepeat{
    typedef typename _CombineTypeIfNotRepeat<contains<T, TS...>::value, T, TS...>::valueTypeList valueTypeList;
};



template <typename List, typename T>
struct CombineTypeList{
};

template <typename T, typename ...TS>
struct CombineTypeList<TypeList<TS...>, T>{
    typedef typename CombineTypeIfNotRepeat<T, TS...>::valueTypeList valueTypeList;
};

template <typename List, typename ...TS>
struct _Union{
    
};

template <typename List>
struct _Union<List>{
    typedef List valueTypeList;
};

template <typename List, typename T, typename ...TS>
struct _Union<List, T, TS...>{
    typedef typename _Union<typename CombineTypeList<List, T>::valueTypeList, TS...>::valueTypeList valueTypeList;
};

template <typename List1, typename List2>
struct Union{
    
};

template <typename List, typename ...TS>
struct Union<List, TypeList<TS...>>{
    typedef typename _Union<List, TS...>::valueTypeList valueTypeList;
};






#endif /* TypeList_hpp */
