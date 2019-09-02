//
//  ControlCenter.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef ControlCenter_hpp
#define ControlCenter_hpp

#include "FundamentalBlock.hpp"

class ControlCenter : public FundamentalBlock
{
    public:
    ControlCenter(const string& newName, unsigned int newTier, const RadioReceiver& newReceiver);
    void PrintMap(unsigned int indentation = 0);
};

#endif /* ControlCenter_hpp */
