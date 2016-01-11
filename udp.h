#ifndef UDP_H
#define UDP_H

#include "udpsocket.h"

class udp
{
public:
    udp();
    ~udp();
    int Init();
private:
    udpsocket* m_ChannelGet;
};

#endif // UDP_H
