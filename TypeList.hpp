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
    
private:
    template<typename TypeVisitor, typename CumulativeType, typename T, typename ...Ts>
    static CumulativeType _CumulateTypes(typename enable_if<sizeof...(Ts)!=0, int>::type i=0);
    
    template<typename TypeVisitor, typename CumulativeType, typename T>
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
//    cout<<"1"<<endl;
    return TypeVisitor::Concatenate(TypeVisitor::template Visit<T>(), _CumulateTypes<TypeVisitor, CumulativeType, Ts...>());
}

template<typename ... TS>
template<typename TypeVisitor, typename CumulativeType, typename T>
CumulativeType TypeList<TS...>::_CumulateTypes(){
//    cout<<"2"<<endl;
    return TypeVisitor::template Visit<T>();
}



#endif /* TypeList_hpp */
