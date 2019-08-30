//
//  UIWriter.hpp
//  Machine
//
//  Created by Samuel Lo on 4/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef UIWriter_hpp
#define UIWriter_hpp

#include "Action.hpp"
class UIModifier;

class UIWriter : public Action
{
    public:
    UIModifier* host;
    
    UIWriter(unsigned int newPriority, const RadioReceiver& newReceiver, UIModifier* newHost) : Action(newPriority,newReceiver), host(newHost) {}
    
    FundamentalBlock* getHost();
    void Do();
};

#endif /* UIWriter_hpp */
