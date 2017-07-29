//
//  ComponentManager.cpp
//  Sparrow
//
//  Created by 许兴伦 on 7/29/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "ComponentManager.hpp"

template <typename T>
ComponentManager<T> ComponentManager<T>::inst = ComponentManager<T>();
