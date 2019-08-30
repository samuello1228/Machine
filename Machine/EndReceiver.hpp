//
//  EndReceiver.hpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#ifndef EndReceiver_hpp
#define EndReceiver_hpp

#include "Action.hpp"
class ControlCenter;

class EndReceiver : public Action
{
    public:
    ControlCenter* host;
    
    EndReceiver(unsigned int newPriority, const RadioReceiver& newReceiver, ControlCenter* newHost) : Action(newPriority,newReceiver), host(newHost) {}
    
    FundamentalBlock* getHost();
    void Do() {}
};

#endif /* EndReceiver_hpp */
