#include "System.h"
#include "Action_TakeDamage.h"
#include "ActionList_t.h"

bool System::printSerial=true;



ActionList_t System::on_Hit;
ActionList_t System::on_Tick;
ActionList_t System::on_Hit_interrupts;
ActionList_t System::on_LifeLoss;
ActionList_t System::on_Death;
