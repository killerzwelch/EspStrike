#ifndef CLASSMAPPER_H
#define CLASSMAPPER_H

#include "GenericAction.h"

class ClassMapper {
    public:
        static GenericAction* mapClass(String clazz);
};
#endif
