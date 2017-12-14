#include "ConfigManager.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Load config ahead of time
std::map<string,string> ConfigManager::mConfigList = ConfigManager::loadConfig();

// Dump config to show what values we
void ConfigManager::dumpConfig()
{
    std::map<string,string>::iterator it;
    it=mConfigList.begin();

    for (it=mConfigList.begin(); it != mConfigList.end(); it++)
    {
        cout << it->first << " : " << it->second << "\n";
    }
}

// Find config value
string& ConfigManager::findValue(const char* name)
{
    std::map<string,string>::iterator it;
    it=mConfigList.find(name);
    return it->second;
}

// Load config from file
std::map<string,string>  ConfigManager::loadConfig()
{
    // TODO create logging
    //Log::mLog << "I am being read by the logger " << "\n";
    std::cout << "I am being read" << "\n";
    string line, name, value;
    size_t found;
    string envPath, fileName;
    envPath     = getenv ("PROGRAM_PATH");
    fileName    = "config.cfg";
    string fullPath = envPath + "/" fileName;

    std::cout << "Full path is" << fullPath <<  "\n";

    if(pEnvPath != NULL)
    {
        strncpy(pFullPath, pEnvPath, sizeof(pEnvPath));
        strncat(pFullPath, pFileName, sizeof(pFileName));
    }
    else
    {
        strncpy(pFullPath, pFileName, sizeof(pFileName));
    }

    ifstream configFile (pFullPath);
    std::map<string,string> T_Map;
    if (configFile.is_open())
    {
        while (getline(configFile, line))
        {
            found=line.find('#');
            if (found != std::string::npos)
            {
                line = line.substr(0, found);
            }
            //  Remove all whitespace
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty()) continue;

            found=line.find('=');
            if (found == std::string::npos) continue; // Was not found

            name    = line.substr(0,found);
            value   = line.substr(found+1);

            std::pair<std::map<string,string>::iterator,bool> ret;

            ret = T_Map.insert(std::pair<string,string>(name,value));

            if (ret.second==true)
            {
                //  TODO create logging
                cout << "New config added, name : " << name << " value : " << value << "\n";
            }
            else
            {
                // TODO create logging
                cout << "Duplicate config, name : " << name << "\n";
            }
        }
    }

    return  T_Map;
}
