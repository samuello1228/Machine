//
//  Detector.cpp
//  Machine
//
//  Created by Samuel Lo on 24/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Detector.hpp"

void Detector::Print()
{
    cout<<"Emitter:(Tier:"<<emitter.tier<<", Channel:"<<emitter.channel<<", isEmitting:"<<emitter.isEmitting<<")";
}
