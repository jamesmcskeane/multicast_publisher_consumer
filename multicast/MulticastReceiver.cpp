#include "MulticastDataConsumer.h"

// set source
void MulticastReceiver::setSource(const char* source)
{
    mSource = source;
}

// set group
void MulticastReceiver::setGroup(const char* group)
{
    mGroup = group;
}

// set port
void MulticastReceiver::setPort(int port)
{
    mPort = port;
}

// listen to muticast address
void MulticastReceiver::listen()
{
    // read values from config manager
    mSource     = mConfigMan.findValue("source");
    mGroup      = mConfigMan.findValue("group");
    mPort       = 5321;
    //TODO Fix logging
    std::cout << "JAMES LOG 1 " << mSource << " : " << mGroup << " : " << mPort << "\n";
    // Create the receiver socket
    // This attempts to open the socket to listen on
    // if we cannot open the socket the then throw a perror (Platform error)
    int recieverSocket;
    if ((recieverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror  ("Could not open socket..");
        exit    (1);
    }

    // REUSEADDER does some work around ensuring there are no conflicts on the ports
    // REUSEPOART is better but was added later any may not work in all platforms.
    int reuseSocket = 1;
    if ((setsockopt(recieverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseSocket, sizeof(reuseSocket)) < 0))
    {
        perror  ("Could not set SO_REUSEADDR..");
        close   (recieverSocket);
        exit    (1);
    }

    // Assigned socket attributes
    struct sockaddr_in addr;
    memset((char*) & addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(mPort);
    addr.sin_addr.s_addr = (mGroup.empty() ? //  Basically we either assign a group or let it get choosen for us.
                            htonl(INADDR_ANY) :
                            inet_addr(mGroup.c_str()));

    // bind the socket
    if (bind(recieverSocket,(struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror  ("Could not bind..");
        close   (recieverSocket);
        exit    (1);
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(mGroup.c_str());
    mreq.imr_interface.s_addr = (mSource.empty() ?
                                 htonl(INADDR_ANY) :
                                 inet_addr(mSource.c_str()));

    if (setsockopt(recieverSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)& mreq, sizeof(mreq)) < 0)
    {
        perror  ("Could not add multicast group..");
        close   (recieverSocket);
        exit    (1);
    }

    //  Read the data
    int     dataLength;
    char    dataBuffer[1024];

    dataLength = sizeof(dataBuffer);
    while (true)
    {
        if (read(recieverSocket, dataBuffer, dataLength) < 0)
        {
            perror  ("Could not read datagram..");
            close   (recieverSocket);
            exit    (1);
        }

        int x=0;
        // read all the data in the current buffer
        while (dataBuffer[x] != '\0')
        {
            cout << dataBuffer[x];
            x++;
        }
        cout << "\n";
    }
}
