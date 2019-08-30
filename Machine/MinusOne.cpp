//
//  MinusOne.cpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

#include "MinusOne.hpp"
#include "UIntergerBlock.hpp"

FundamentalBlock* MinusOne::getHost()
{
    return host;
}

void MinusOne::Do()
{
    if(getChannelSignal())
    {
        if(host->properties_UI["UInterger"] == 0)
        {
            cout<<"Error: the unsinged integer value is zero, cannot minus one."<<endl;
            return;
        }
        else
        {
            host->properties_UI["UInterger"] --;
        }
    }
}
