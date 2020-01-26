#include "ActionHandler.h"
#include "ClassMapper.h"

/*Helper class to build action execution chain*/
ActionList_t* ActionHandler::addAction(ActionList_t *list, String clazz)
{
    ActionList_t *curr = list;
    //Go until end of list
    while (curr->next != 0x0) {
        curr=curr->next;
    }
    if (curr->action!=0x0)
    {
        curr->next = new ActionList_t(); //(struct actionList_t*)malloc(sizeof(struct actionList_t));
        curr=curr->next;
    }
    curr->next=0x0;
    curr->action =ClassMapper::mapClass(clazz);
    return curr;
}
void ActionHandler::executeActions(ActionList_t *list, vector<Parameter_t> params)
{
    ActionList_t *curr=list;
    while(curr != 0x0)
    {
        if (curr->action!= 0x0) {
            curr->action->execute(params);
        }
        curr=curr->next;
    }

}
