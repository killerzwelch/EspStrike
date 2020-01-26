#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <vector>
#include "ActionList_t.h"
#include "Parameter_t.h"
#include "System.h"


/*Helper class to build action execution chain*/
class ActionHandler {
    public:
        ActionList_t* addAction(ActionList_t *list, String clazz);
        void executeActions(ActionList_t *list, vector<Parameter_t> params);
    
};

#endif;
