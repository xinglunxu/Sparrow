//
//  ComponentManager.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/29/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef ComponentManager_hpp
#define ComponentManager_hpp

#include <stdio.h>
#include <unordered_map>

using namespace std;

template <typename DataType>
class ComponentManager{
private:
    unordered_map<int, unordered_map<int, DataType>> datas;
    ComponentManager();
public:
    static ComponentManager inst;
};



#endif /* ComponentManager_hpp */
