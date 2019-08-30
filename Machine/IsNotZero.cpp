//
//  IsNotZero.cpp
//  Machine
//
//  Created by Samuel Lo on 5/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

#include "IsNotZero.hpp"
#include "UIntergerBlock.hpp"

FundamentalBlock* IsNotZero::getHost()
{
    return host;
}

void IsNotZero::Do()
{
    bool result = (host->properties_UI["UInterger"] != 0);
    emitter.isEmitting = result;
}
