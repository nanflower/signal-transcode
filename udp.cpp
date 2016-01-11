#include "udp.h"

udp::udp()
{

}

udp::~udp()
{

}

int udp::Init()
{

    m_ChannelGet = new udpsocket();
    m_ChannelGet->thread_init();  //udp接收线程

    return 0;
}

