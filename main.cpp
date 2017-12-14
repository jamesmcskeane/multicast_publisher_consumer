#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "ConfigManager.h"

using namespace std;
import ConfigManager;

// Create a program to read data from a file and publish it to
// a specific multicast source and group
int main(int argc, char *argv[])
{
    ConfigManager* pCfg = new ConfigManager();

    string source ="source";
    string group  ="group";
    //string port   ="port";
    //cout << pCfg->findValue(source);
    //cout << pCfg->findValue(group);
    //cout << pCfg->findValue(port);

    // Open socket
    int senderSocket;
    if ((senderSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror  ("Could not open socket..");
        exit    (1);
    }

    //string  source;//     ("203.106.93.94");
    //string  group     ("226.1.1.1");
    int     port = 5321;

    struct sockaddr_in addr;
    memset((char*) & addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = (group.empty() ?
                            htonl(INADDR_ANY) :
                            inet_addr(group.c_str()));

    struct in_addr localInterface;
    localInterface.s_addr = (source.empty() ?
                             htonl(INADDR_ANY) :
                             inet_addr(source.c_str()));

    // set up multicast interface
    if (setsockopt(senderSocket, IPPROTO_IP, IP_MULTICAST_IF, (char*)& localInterface, sizeof(localInterface)) < 0)
    {
        perror  ("Could not set up multicast interface..");
        close   (senderSocket);
        exit    (1);
    }


    // set msgNum
    int msgNum = 0;
    string line;
    // Read some raw data from a file
    ifstream myfile ("playback.pb");
    if (myfile.is_open())
    {
        // Send date per line in playback file sleep then send the next
        while (getline (myfile,line))
        {
            sleep(1);
            char databuf[1024];
            strncpy(databuf, line.c_str(), 100);
            int datalen = sizeof(databuf);

            if (sendto(senderSocket, databuf, datalen, 0, (struct sockaddr*)&addr, sizeof(addr)) < 0)
            {
                perror  ("Datagram sending error..");
                close   (senderSocket);
                exit    (1);
            }
        }
    }

    return 0;
}
