//
//  Component.hpp
//  Sparrow
//
//  Created by 许兴伦 on 7/22/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

class ComponentCounter{
struct:
    static int counter;
};

int ComponentCounter::counter = 0;

template <typename Data>
struct Component{
private:
    static int bitIndex;
};

template <typename Data>
int Component<Data>::bitIndex = ComponentCounter::counter++;

#endif /* Component_hpp */
