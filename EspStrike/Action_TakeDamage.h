#ifndef ACTION_TAKEDAMAGE_H
#define ACTION_TAKEDAMAGE_H

#include "GenericAction.h"

/*One specific implementation of an action, here the logic of taking damage*/
class Action_TakeDamage: public GenericAction {
    public:
        void execute(vector<Parameter_t> params);
        void init(vector<Parameter_t> params);
        void init();
        void execute();
         
    
};
#endif;
