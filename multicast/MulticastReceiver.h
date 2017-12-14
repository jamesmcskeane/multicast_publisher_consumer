#ifndef Included_MULTICAST_RECEIVER_H
#define Included_MULTICAST_RECEIVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "ModuleRegisterInterface.h"
#include "ConfigManager.h"

using namespace std;

// Class for receiving multicast packets
class MulticastReceiver : public MulticastReceiverModule
{
    public:
    MulticastReceiver(ModuleRegister&       mod,
                      ConfigManager&        cfgMan)
                      : mMulticastReceiver (mod)
                      , mConfigMan         (cfgMan)
                      , mPort              (0)
    {
        // Here we register out module
        mMulticastReceiver.Register (this);
        //mPort = cfgMan.find("Port");
    }

    void setSource  (const char* source);
    void setGroup   (const char* group);
    void setPort    (int     port);
    void listen     ();

    private:
    ModuleRegister&         mMulticastReceiver;
    ConfigManager&          mConfigMan;
    string                  mSource;
    string                  mGroup;
    int                     mPort;
};
#endif
