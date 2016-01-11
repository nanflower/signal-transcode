#ifndef TSPOOLQUEUE_H
#define TSPOOLQUEUE_H

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
#ifdef __cplusplus
};
#endif
#endif

#include <pthread.h>

typedef unsigned char uint8_t;

class tspoolqueue
{
public:
    tspoolqueue();
    ~tspoolqueue();
    void init(void);
    void init_buffer(void);
    void init_queue( int size);
    void free_queue();
    void put_queue(unsigned char* buf, int size);
    int get_queue(uint8_t* buf, int size);

};

#endif // TSRECVPOOL_H
