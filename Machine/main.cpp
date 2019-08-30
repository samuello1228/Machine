//
//  main.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "CompositeBlock.hpp"

//Fundamental Block
#include "ControlCenter.hpp"
#include "IOIndicator.hpp"
#include "UIntergerBlock.hpp"
#include "UIModifier.hpp"

//Module
#include "IsNotZero.hpp"
#include "MinusOne.hpp"
#include "UIWriter.hpp"


int main()
{
    //size hierarchy
    vector<unsigned int> sizeHierarchy;
    sizeHierarchy.push_back(5);
    
    //add ControlCenter
    ControlCenter* ControlCenter1 = new ControlCenter("ControlCenter" ,1, RadioReceiver(2,1));
    
    //add UIModifier1
    UIModifier* UIModifier1 = new UIModifier("UIModifier",4,1,"UInterger");
    
    UIModifier1->addReceiver(1,"UIWriter",RadioReceiver(2,1));
    
    //add UIntergerBlock1
    UIntergerBlock* UIntergerBlock1 = new UIntergerBlock("UIntergerBlock",0);
    
    UIntergerBlock1->addReceiver(1, "MinusOne", RadioReceiver(1,1));
    UIntergerBlock1->addEmitter(2, "IsNotZero", RadioEmitter(1,1,0));
    UIntergerBlock1->addEmitter(3, "IsZero", RadioEmitter(2,1,1));
    
    //add block
    CompositeBlock* topmost = new CompositeBlock("Topmost",sizeHierarchy.back());
    topmost->addControlCenter(Coordinate(2,2), ControlCenter1);
    topmost->addBlock(1, Coordinate(4,1), UIModifier1);
    topmost->addBlock(2, Coordinate(4,2), UIntergerBlock1);
    
    topmost->registerAll();
    topmost->PrintMap();
    topmost->execute(topmost,true);
    
    delete topmost;
    
    return 0;
}
