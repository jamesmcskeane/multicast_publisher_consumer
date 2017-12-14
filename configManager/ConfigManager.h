#ifndef Included_CONFIG_MANAGER_H
#define Included_CONFIG_MANAGER_H

#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "ModuleRegisterInterface.h"
//#include "Log.h"

using namespace std;

class ConfigManager : public ConfigManagerModule
{
    public:
    static ConfigManager& getInstance()
    {
        static ConfigManager    mConfigManager;
        return mConfigManager;
    }

    void        dumpConfig();
    string&     findValue(const char* name);
    static map<string,string> loadConfig();

    private:
    ConfigManager()
    {
        //  Registering the ConfigManager with the module list
        //  As there is only ever one module list there is no need
        //  to pass it, we can call it here and register the ConfigManager
        //  which is also a singleton
        ModuleRegister::getInstance().Register(this);
    }

    //  Static map as we are loading the config before main
    //  Staitc
    static  std::map<string, string>    mConfigList;
    //TODO create logging
    //Log                                   mLog;
};

#endif

