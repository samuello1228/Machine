//
//  RadioReceiver.cpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
using namespace std;

#include "RadioReceiver.hpp"

RadioReceiver::RadioReceiver(unsigned int newTier, unsigned int newChannel)
{
    tier = newTier;
    channel = newChannel;
}

void RadioReceiver::Print()
{
    cout<<"Receiver:(Tier:"<<tier<<", Channel:"<<channel<<")";
}
