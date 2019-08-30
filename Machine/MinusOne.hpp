//
//  MinusOne.hpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef MinusOne_hpp
#define MinusOne_hpp

#include "Action.hpp"
class UIntergerBlock;

class MinusOne : public Action
{
    public:
    UIntergerBlock* host;
    
    MinusOne(unsigned int newPriority, const RadioReceiver& newReceiver, UIntergerBlock* newHost) : Action(newPriority,newReceiver), host(newHost) {}
    
    FundamentalBlock* getHost();
    void Do();
};

#endif /* MinusOne_hpp */
