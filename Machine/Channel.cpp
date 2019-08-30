//
//  Channel.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Channel.hpp"

Channel::Channel(unsigned int newTier, unsigned int newChannel)
{
    tier = newTier;
    channel = newChannel;
}

void Channel::Print()
{
    cout<<"(Tier:"<<tier<<", Channel:"<<channel<<")";
}
