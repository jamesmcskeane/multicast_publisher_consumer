#ifndef Included_MODULE_REGISTER_INTERFACE_H
#define Included_MODULE_REGISTER_INTERFACE_H

#include "ModuleRegister.h"

// TODO create logging (Logging has been created but complexity issue need to be resolved
// leaving out for now.)
//class LogModule
//{
//  public:
//      static const unsigned ModuleID = 1;
//      virtual ~LogModule(){};
//};

class ConfigManagerModule
{
    public:
        static const unsigned ModuleID = 2;
        virtual ~ConfigManagerModule(){};
};

class MulticastReceiverModule
{
    public:
        static const unsigned ModuleID = 3;
        virtual ~MulticastReceiverModule(){};
};

#endif
