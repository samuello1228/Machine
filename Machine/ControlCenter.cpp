//
//  ControlCenter.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "ControlCenter.hpp"
#include "EndReceiver.hpp"

ControlCenter::ControlCenter(const string& newName, unsigned int newTier, const RadioReceiver& newReceiver) : FundamentalBlock(newName)
{
    if(newTier == 0)
    {
        cout<<"Error: The tier of control center cannot be 0."<<endl;
        return;
    }
    properties_UI["tier"] = newTier;
    module["EndReceiver"] = new EndReceiver(1, newReceiver, this);
}
