#ifndef GENERICACTION_H
#define GENERICACTION_H

#include "Parameter_t.h"
#include <vector>

using namespace std;
/*Abstract super class for all actions that can be defined in XML*/
class GenericAction {
    public: 
     virtual void execute(vector<Parameter_t> params) =0;
     virtual void execute() =0;
     virtual void init(vector<Parameter_t> params) = 0;
     virtual void init() = 0;

};



#endif
