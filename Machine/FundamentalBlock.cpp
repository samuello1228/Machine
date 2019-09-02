//
//  FundamentalBlock.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include <iostream>
#include <algorithm>

#include "FundamentalBlock.hpp"
#include "CompositeBlock.hpp"
#include "Module.hpp"

//List of Block
#include "ControlCenter.hpp"
#include "UIntergerBlock.hpp"
#include "UIModifier.hpp"

//List of Module
#include "TrueEmitter.hpp"
#include "IsNotZero.hpp"
#include "MinusOne.hpp"
#include "UIWriter.hpp"

FundamentalBlock::FundamentalBlock(const string& newName)
{
    name = newName;
    tier = 1;
}

FundamentalBlock::~FundamentalBlock()
{
    for(map<string,Module*>::iterator it = module.begin(); it!=module.end(); it++)
    {
        delete it->second;
    }
}

void FundamentalBlock::addPropertiesUI(const string& key, unsigned int value)
{
    properties_UI[key] = value;
}

void FundamentalBlock::addEmitter(unsigned int newPriority, string module_name, const RadioEmitter& newEmitter)
{
    if(module_name == "TrueEmitter")
    {
        if(this->module.find(module_name) != module.end())
        {
            cout<<"Error: this fundamental block already has the module \""<<module_name<<"\"."<<endl;
            return;
        }
        
        this->module[module_name] = new TrueEmitter(newPriority,newEmitter,this);
    }
    else if(module_name == "IsNotZero")
    {
        if(this->module.find(module_name) != module.end())
        {
            cout<<"Error: this fundamental block already has the module \""<<module_name<<"\"."<<endl;
            return;
        }
        
        UIntergerBlock* UIntergerBlock1 = dynamic_cast<UIntergerBlock*>(this);
        
        if(UIntergerBlock1) this->module[module_name] = new IsNotZero(newPriority,newEmitter,UIntergerBlock1);
        else
        {
            cout<<"Error: this fundamental block is not UIntergerBlock, cannot add module \""<<module_name<<"\"."<<endl;
            return;
        }
    }
    else
    {
        cout<<"Error: Module name \""<<module_name<<"\" does not exist."<<endl;
        return;
    }
}

void FundamentalBlock::addReceiver(unsigned int newPriority, string module_name, const RadioReceiver& newReceiver)
{
    if(module_name == "MinusOne")
    {
        if(this->module.find(module_name) != module.end())
        {
            cout<<"Error: this fundamental block already has the module \""<<module_name<<"\"."<<endl;
            return;
        }
        
        UIntergerBlock* UIntergerBlock1 = dynamic_cast<UIntergerBlock*>(this);
        
        if(UIntergerBlock1) this->module[module_name] = new MinusOne(newPriority,newReceiver,UIntergerBlock1);
        else
        {
            cout<<"Error: this fundamental block is not UIntergerBlock, cannot add module \""<<module_name<<"\"."<<endl;
            return;
        }
    }
    else if(module_name == "UIWriter")
    {
        if(this->module.find(module_name) != module.end())
        {
            cout<<"Error: this fundamental block already has the module \""<<module_name<<"\"."<<endl;
            return;
        }
        
        UIModifier* UIModifier1 = dynamic_cast<UIModifier*>(this);
        
        if(UIModifier1) this->module[module_name] = new UIWriter(newPriority,newReceiver,UIModifier1);
        else
        {
            cout<<"Error: this fundamental block is not UIModifier, cannot add module \""<<module_name<<"\"."<<endl;
            return;
        }
    }
    else
    {
        cout<<"Error: Module name \""<<module_name<<"\" does not exist."<<endl;
        return;
    }
}

void FundamentalBlock::PrintMap(unsigned int indentation)
{
    cout<<string(indentation, ' ');
    cout<<"Tier:"<<tier<<", ";
    cout<<"Type:"<<name<<", ";
    cout<<"Coordinate:("<<coordinate.x<<","<<coordinate.y<<")";
    //cout<<", Address:"<<this;
    cout<<endl;
    
    cout<<string(indentation, ' ');
    cout<<"Properties: "<<endl;
    for (map<string,unsigned int>::iterator it=properties_UI.begin(); it!=properties_UI.end(); it++)
    {
        cout<<string(indentation+2, ' ');
        cout<<it->first<< ": "<<it->second<<endl;
    }
    
    PrintExtraProperties(indentation);
    
    cout<<string(indentation, ' ');
    cout<<"Radio data: "<<endl;
    for (map<unsigned int,RadioEmitter*>::iterator it=radioData.begin(); it!=radioData.end(); it++)
    {
        cout<<string(indentation+2, ' ');
        cout<<"Channel "<<it->first<< ": "<<it->second->isEmitting<<endl;
    }
    
    cout<<string(indentation, ' ');
    cout<<"Module: "<<endl;
    for (map<string,Module*>::iterator it=module.begin(); it!=module.end(); it++)
    {
        cout<<string(indentation+2, ' ');
        cout<<"Type:"<<it->first<< ", Priority:"<<it->second->priority<<", ";
        it->second->Print();
        cout<<endl;
        
        //check host link
        if(it->second->getHost() != this)
        {
            cout<<"Error: The host link is wrong."<<endl;
            return;
        }
    }
}

void FundamentalBlock::PrintExtraProperties(unsigned int indentation)
{
}

Block* FundamentalBlock::getTierBlock(unsigned int tier)
{
    Block* block_tier = this;
    for(unsigned int i = 1; i <= tier - 1 ; i++)
    {
        block_tier = block_tier->MotherBlock;
    }
    return block_tier;
}

bool FundamentalBlock::isControlCenter()
{
    ControlCenter* controlCenter = dynamic_cast<ControlCenter*>(this);
    if(controlCenter) return true;
    else return false;
}

void FundamentalBlock::registerAll()
{
    //register control center
    ControlCenter* controlCenter = dynamic_cast<ControlCenter*>(this);
    if(controlCenter)
    {
        Block* block_controlCenter_tier = getTierBlock(controlCenter->properties_UI["tier"] + 1);
        CompositeBlock* compositeBlock = dynamic_cast<CompositeBlock*>(block_controlCenter_tier);
        if(compositeBlock)
        {
            if(compositeBlock->controlCenter == nullptr)
            {
                compositeBlock->controlCenter = controlCenter;
            }
            else
            {
                cout<<"Error: The link of control center already exists."<<endl;
                return;
            }
        }
        else
        {
            cout<<"Error: The control center does not has the correct tier."<<endl;
            return;
        }
    }
    
    //register emitter channel
    for(map<string,Module*>::iterator it = module.begin(); it!=module.end(); it++)
    {
        Detector* detector = dynamic_cast<Detector*>(it->second);
        if(detector)
        {
            Block* block_radio_tier = getTierBlock(detector->emitter.tier);
            if(block_radio_tier->radioData.find(detector->emitter.channel) == block_radio_tier->radioData.end())
            {
                block_radio_tier->radioData[detector->emitter.channel] = &(detector->emitter);
            }
            else
            {
                cout<<"Error: this emitter channel has already been registerd: ";
                detector->Print();
                cout<<endl;
                return;
            }
        }
    }
}

unsigned int FundamentalBlock::getPriority()
{
    if(isControlCenter())
    {
        return 0;
    }
    
    std::map<string,unsigned int>::iterator it = properties_UI.find("priority");
    if(it == properties_UI.end())
    {
        return 0;
    }
    else
    {
        return properties_UI["priority"];
    }
}

void FundamentalBlock::execute(CompositeBlock* topmost, bool isPrint)
{
    vector< map<string,Module*>::iterator > sortedModule;
    for(map<string,Module*>::iterator it = module.begin(); it!=module.end(); it++)
    {
        if(it->second->priority != 0) sortedModule.push_back(it);
    }
    
    if(sortedModule.size() != 0)
    {
        //classified by the priority
        sort(sortedModule.begin(), sortedModule.end(), [](map<string,Module*>::iterator a, map<string,Module*>::iterator b)->bool{return a->second->priority < b->second->priority;});
        
        vector<vector< map<string,Module*>::iterator > > classifiedModule;
        vector< map<string,Module*>::iterator > element;
        element.push_back(sortedModule[0]);
        unsigned int index = 0;
        while(true)
        {
            if(index == sortedModule.size() -1)
            {
                classifiedModule.push_back(element);
                element.clear();
                break;
            }
            
            index++;
            if(sortedModule[index]->second->priority == sortedModule[index-1]->second->priority)
            {
                element.push_back(sortedModule[index]);
            }
            else
            {
                classifiedModule.push_back(element);
                element.clear();
                element.push_back(sortedModule[index]);
            }
        }
        
        //check
        for(unsigned int i = 0; i<classifiedModule.size();i++)
        {
            if(classifiedModule[i].size() != 1)
            {
                cout<<"Error: the priority ";
                cout<<classifiedModule[i][0]->second->priority;
                cout<<" for modules: ";
                for(unsigned int j = 0; j<classifiedModule[i].size();j++)
                {
                    cout<<classifiedModule[i][j]->first<<" ";
                }
                cout<<"are repeated."<<endl;
                return;
            }
        }
        
        //Run
        for(unsigned int i = 0; i<classifiedModule.size();i++)
        {
            classifiedModule[i][0]->second->Do();
        }
        
        if(isPrint)
        {
            cout<<"Executing "<<name<<endl;
            topmost->PrintMap();
        }
    }
}
