//
//  CompositeBlock.cpp
//  Machine
//
//  Created by Samuel Lo on 3/8/2019.
//  Copyright © 2019年 Samuel Lo. All rights reserved.
//

#include "FundamentalBlock.hpp"
#include "CompositeBlock.hpp"
#include "ControlCenter.hpp"

#include "Module.hpp"
#include "EndReceiver.hpp"

CompositeBlock::CompositeBlock(const string& newName, unsigned int newSize) : size(newSize)
{
    name = newName;
    controlCenter = nullptr;
}

CompositeBlock::~CompositeBlock()
{
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        delete (*it);
    }
}

void CompositeBlock::PrintMap(unsigned int indentation)
{
    cout<<string(indentation, ' ');
    cout<<"Tier:"<<tier<<", ";
    cout<<"Type:"<<name<<", ";
    cout<<"Size:"<<size<<", ";
    cout<<"Coordinate:("<<coordinate.x<<","<<coordinate.y<<")";
    //cout<<", Control Center:"<<controlCenter;
    cout<<endl;
    
    //Check Control Center
    ControlCenter* controlCenter2 = dynamic_cast<ControlCenter*>(controlCenter);
    if(!controlCenter2) cout<<"Error: The ControlCenter link is not ControlCenter."<<endl;
    if(tier != controlCenter->properties_UI["tier"] + 1) cout<<"Error: The ControlCenter link has wrong value of tier."<<endl;
    
    cout<<string(indentation, ' ');
    cout<<"Radio data: "<<endl;
    for (map<unsigned int,RadioEmitter*>::iterator it=radioData.begin(); it!=radioData.end(); it++)
    {
        cout<<string(indentation+2, ' ');
        cout<<"Channel "<<it->first<< ": "<<it->second->isEmitting<<endl;
    }
    
    cout<<string(indentation, ' ');
    cout<<"Composition:"<<endl;
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        (*it)->PrintMap(indentation+2);
        cout<<endl;
        
        //check MotherBlock link
        if((*it)->MotherBlock != this)
        {
            cout<<"Error: The MotherBlock link is wrong."<<endl;
            return;
        }
    }
}

void CompositeBlock::addControlCenter(const Coordinate& newCoordinate, ControlCenter* newControlCenter)
{
    tier = newControlCenter->properties_UI["tier"] + 1;
    newControlCenter->MotherBlock = this;
    newControlCenter->coordinate = newCoordinate;
    this->Composition.insert(newControlCenter);
}

void CompositeBlock::addBlock(unsigned int newPriority, const Coordinate& newCoordinate, Block* newBlock)
{
    newBlock->MotherBlock = this;
    newBlock->coordinate = newCoordinate;
    FundamentalBlock* FundamentalBlock1 = dynamic_cast<FundamentalBlock*>(newBlock);
    if(FundamentalBlock1)
    {
        FundamentalBlock1->properties_UI["priority"] = newPriority;
    }
    
    CompositeBlock* CompositeBlock1 = dynamic_cast<CompositeBlock*>(newBlock);
    if(CompositeBlock1)
    {
        CompositeBlock1->controlCenter->properties_UI["priority"] = newPriority;
    }
    
    this->Composition.insert(newBlock);

}

void CompositeBlock::registerAll()
{
    for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
    {
        (*it)->registerAll();
    }
    
    if(controlCenter == nullptr)
    {
        cout<<"Error: Control center cannot be found."<<endl;
        return;
    }
}

unsigned int CompositeBlock::getPriority()
{
    if(controlCenter == nullptr)
    {
        cout<<"Error: Control center cannot be found."<<endl;
        return 0;
    }
    
    return controlCenter->properties_UI["priority"];
}

void CompositeBlock::execute(CompositeBlock* topmost, bool isPrint)
{
    unsigned int count = 1;
    while(true)
    {
        vector<Block*> sortedBlock;
        for(set<Block*>::iterator it = Composition.begin(); it!=Composition.end(); it++)
        {
            if((*it)->getPriority() != 0) sortedBlock.push_back(*it);
        }
        
        if(sortedBlock.size() != 0)
        {
            //classified by the priority
            sort(sortedBlock.begin(), sortedBlock.end(), [](Block* a, Block* b)->bool{return a->getPriority() < b->getPriority();});
            
            vector<vector< Block* > > classifiedBlock;
            vector< Block* > element;
            element.push_back(sortedBlock[0]);
            unsigned int index = 0;
            while(true)
            {
                if(index == sortedBlock.size() -1)
                {
                    classifiedBlock.push_back(element);
                    element.clear();
                    break;
                }
                
                index++;
                if(sortedBlock[index]->getPriority() == sortedBlock[index-1]->getPriority())
                {
                    element.push_back(sortedBlock[index]);
                }
                else
                {
                    classifiedBlock.push_back(element);
                    element.clear();
                    element.push_back(sortedBlock[index]);
                }
            }
            
            //check
            for(unsigned int i = 0; i<classifiedBlock.size();i++)
            {
                if(classifiedBlock[i].size() != 1)
                {
                    cout<<"Error: the priority ";
                    cout<<classifiedBlock[i][0]->getPriority();
                    cout<<" for modules: ";
                    for(unsigned int j = 0; j<classifiedBlock[i].size();j++)
                    {
                        cout<<classifiedBlock[i][j]->name<<" ";
                    }
                    cout<<"are repeated."<<endl;
                    return;
                }
            }
            
            if(isPrint) cout<<name<<": The number of loop: "<<count<<endl;
            
            //Run
            for(unsigned int i = 0; i<classifiedBlock.size();i++)
            {
                classifiedBlock[i][0]->execute(topmost,isPrint);
            }
            count++;
            
            //check end
            if(controlCenter == nullptr)
            {
                cout<<"Error: Control center cannot be found."<<endl;
                return;
            }
            
            EndReceiver* endReceiver = dynamic_cast<EndReceiver*>(controlCenter->module["EndReceiver"]);
            if(endReceiver)
            {
                if(endReceiver->getChannelSignal()) return;
            }
            else
            {
                cout<<"Error: The end receiver of the control center is corrupted."<<endl;
                return;
            }
            
        }
    }
}

