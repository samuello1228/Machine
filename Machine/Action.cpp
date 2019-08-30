//
//  Action.cpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "Action.hpp"
#include "FundamentalBlock.hpp"
#include "CompositeBlock.hpp"

void Action::Print()
{
    receiver.Print();
}

bool Action::getChannelSignal()
{
    Block* block_radio_tier = getHost();
    for(unsigned int i = 1; i <= receiver.tier - 1 ; i++)
    {
        block_radio_tier = block_radio_tier->MotherBlock;
    }
    
    if(block_radio_tier->radioData.find(receiver.channel) == block_radio_tier->radioData.end())
    {
        return false;
    }
    else
    {
        return block_radio_tier->radioData[receiver.channel]->isEmitting;
    }
}
