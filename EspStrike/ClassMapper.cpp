#include "ClassMapper.h"
#include "Action_TakeDamage.h"

GenericAction* ClassMapper::mapClass(String clazz) {
    /*Unfortunatly C++ does not allow to dynamically instantiate objects and make function pointer to it :(. 
        Linker must know in advance...*/
    if(clazz == "takeDamage") {   
        return new Action_TakeDamage();
     }
/*    else if(clazz == "sendMessage") {
        return new Action_SendMessage();
    }
    else if(clazz == ("heal") {
        return new Action_Heal();
    }*/
    /*Return 0x0 to indicate that no handler has been defined*/
    else return 0x0;
}
