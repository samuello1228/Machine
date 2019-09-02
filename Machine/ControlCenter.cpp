//
//  ControlCenter.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

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
    properties_UI["priority"] = 0;
    module["EndReceiver"] = new EndReceiver(1, newReceiver, this);
}

void ControlCenter::PrintMap(unsigned int indentation)
{
    cout<<string(indentation, ' ');
    cout<<name<<": ";
    cout<<"Tier: "<<properties_UI["tier"];
    cout<<", Priority:"<<properties_UI["priority"];
    cout<<", Coordinate:("<<coordinate.x<<","<<coordinate.y<<"), End";
    module["EndReceiver"]->Print();
    cout<<endl;
    
    //check host link
    if(module["EndReceiver"]->getHost() != this)
    {
        cout<<"Error: The host link is wrong."<<endl;
        return;
    }
}
