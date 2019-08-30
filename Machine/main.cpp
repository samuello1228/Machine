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

int main()
{
    //size hierarchy
    vector<unsigned int> sizeHierarchy;
    sizeHierarchy.push_back(5);
    
    //add ControlCenter
    ControlCenter* ControlCenter1 = new ControlCenter("ControlCenter" ,1, RadioReceiver(2,2));
    
    //add UIModifier1
    UIModifier* UIModifier1 = new UIModifier("UIModifier1",2,1,"UInterger");
    UIModifier1->addReceiver(1, "UIWriter", RadioReceiver(2,2));
    
    //add UIntergerBlock1
    UIntergerBlock* UIntergerBlock1 = new UIntergerBlock("UIntergerBlock1",0);
    UIntergerBlock1->addReceiver(1, "MinusOne", RadioReceiver(2,1));
    UIntergerBlock1->addEmitter(2, "IsNotZero", RadioEmitter(2,1,0));
    
    //add NOT gate
    UIntergerBlock* NotGateModifier1 = new UIModifier("NotGateModifier1",1,1,"UInterger");
    NotGateModifier1->addEmitter(1, "TrueEmitter", RadioEmitter(1,1));
    NotGateModifier1->addReceiver(2, "UIWriter", RadioReceiver(1,1));
    
    UIntergerBlock* NotGateModifier2 = new UIModifier("NotGateModifier2",0,4,"UInterger");
    NotGateModifier2->addReceiver(1, "UIWriter", RadioReceiver(2,1));
    
    UIntergerBlock* NotGateBlock1 = new UIntergerBlock("NotGateBlock1",1);
    NotGateBlock1->addEmitter(1, "IsNotZero", RadioEmitter(2,2,1));
    
    //add block
    CompositeBlock* topmost = new CompositeBlock("Topmost",sizeHierarchy.back());
    sizeHierarchy.pop_back();
    topmost->addControlCenter(Coordinate(2,2), ControlCenter1);
    topmost->addBlock(1, Coordinate(4,1), UIModifier1);
    topmost->addBlock(2, Coordinate(4,2), UIntergerBlock1);
    topmost->addBlock(3, Coordinate(4,3), NotGateModifier1);
    topmost->addBlock(4, Coordinate(5,4), NotGateModifier2);
    topmost->addBlock(5, Coordinate(4,4), NotGateBlock1);
    
    topmost->registerAll();
    topmost->PrintMap();
    topmost->execute(topmost,true);
    
    delete topmost;
    
    return 0;
}
