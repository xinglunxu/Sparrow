//
//  WorldSetting.hpp
//  Sparrow
//
//  Created by 许兴伦 on 8/9/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef WorldSetting_hpp
#define WorldSetting_hpp

#include <stdio.h>

template<typename SystemTypeList, typename EntitySystemTypeList>
struct WorldSetting{
    typedef SystemTypeList systemTypeList;
    typedef EntitySystemTypeList entitySystemTypeList;
};


#endif /* WorldSetting_hpp */
