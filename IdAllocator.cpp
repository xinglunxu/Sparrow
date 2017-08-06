//
//  IdAllocator.cpp
//  Sparrow
//
//  Created by 许兴伦 on 8/6/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "IdAllocator.hpp"


IdAllocator::IdAllocator(){
    curId = 0;
    retIntList = list<int>();
}

int IdAllocator::GetId(){
    if(retIntList.size()>0){
        return retIntList.front();
    }
    else{
        int temp = curId;
        curId++;
        return temp;
    }
}

void IdAllocator::ReturnId(int i){
    retIntList.push_front(i);
}
