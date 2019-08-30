//
//  EndReceiver.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>

#include "EndReceiver.hpp"
#include "ControlCenter.hpp"

FundamentalBlock* EndReceiver::getHost()
{
    return host;
}
