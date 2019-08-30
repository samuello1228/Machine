//
//  IsZero.cpp
//  Machine
//
//  Created by Samuel Lo on 6/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "IsZero.hpp"
#include "UIntergerBlock.hpp"

FundamentalBlock* IsZero::getHost()
{
    return host;
}

void IsZero::Do()
{
    bool result = (host->properties_UI["UInterger"] == 0);
    emitter.isEmitting = result;
}
