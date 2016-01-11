#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavformat/avformat.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/audio_fifo.h>
#include "libswresample/swresample.h"
#ifdef __cplusplus
};
#endif
#endif

#include <pthread.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<netdb.h>
#include<stdarg.h>
#include<string.h>
#include<errno.h>

//intel encoder
//#include "mfxmvc.h"
#include "mfxvideo.h"
#include "mfxvp8.h"
#include "mfxvideo++.h"
#include "mfxplugin.h"
#include "mfxplugin++.h"
#include "mfxla.h"
#include <vector>
#include <memory>

//#include "tsrecvpool.h"
#include "tspoolqueue.h"
#include "transcodepool.h"

#define VIDEO_NUM 7
#define AUDIO_NUM 7
#define VIDEOBUF_SIZE 10000*188
#define BUF_SIZE 4096*2000 //read buffer
#define BUFFER_SIZE 4096      //recvfrom buffer
#define FILE_NAME_MAX_SIZE 512
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000


class udpsocket
{
public:
    udpsocket();
    ~udpsocket();
    void thread_init(void);
    static void* udp_tsrecv(void *param);
    static void* udp_tsrecv1(void *param);
    void udp_ts_recv(void);
    void udp_ts_recv1(void);
    static int read_data(void *opaque, uint8_t *buf, int buf_size);
    static int read_data1(void *opaque, uint8_t *buf, int buf_size);
    int ts_demux(void);
    int thread_test();
    static void* ts_demuxer( void *param );
    static void* ts_demuxer1(void *param);
    static void* video_encoder(void *param);
    void run_video_encoder(void);
    tspoolqueue* m_tsRecvPool;

private:

};

#endif // UDPSOCKET_H
