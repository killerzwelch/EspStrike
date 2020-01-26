#ifndef ACTIONLIST_T
#define ACTIONLIST_T
#include "GenericAction.h"

class ActionList_t {
  public:
    GenericAction *action=0x0;
    ActionList_t *next =0x0;
};

#endif
