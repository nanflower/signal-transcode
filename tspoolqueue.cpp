#include "tspoolqueue.h"

pthread_mutex_t locker;
//pthread_cond_t cond;
uint8_t* q_buf;
uint8_t* dst;
uint8_t* src;
int bufsize;
volatile int write_ptr;
volatile int read_ptr;

tspoolqueue::tspoolqueue()
{
    pthread_mutex_init(&locker, NULL);
//    pthread_cond_init(&cond, NULL);
    q_buf = (uint8_t*)av_mallocz(sizeof(uint8_t)*1024*1024*50);
    write_ptr = 0;
    read_ptr = 0;
    bufsize = 1024*1024*50;
    printf("buffer size = %d\n",bufsize);
    dst = q_buf;
    src = q_buf;
}


tspoolqueue::~tspoolqueue()
{
    pthread_mutex_destroy(&locker);
    av_free(q_buf);
    av_free(dst);
    av_free(src);
}


void tspoolqueue::free_queue(void) {
    pthread_mutex_destroy(&locker);
//    pthread_cond_destroy(&cond);
    av_free(q_buf);
}


void tspoolqueue::put_queue(unsigned char* buf, int size) {
//    printf(" put queue :   tid %lu\n",(unsigned long)pthread_self());
    dst = q_buf + write_ptr;
    pthread_mutex_lock(&locker);
    if ((write_ptr + size) > bufsize) {
        memcpy(dst, buf, (bufsize - write_ptr));
        memcpy(q_buf, buf+(bufsize - write_ptr), size-(bufsize - write_ptr));
    } else {
        memcpy(dst, buf, size*sizeof(uint8_t));
    }
    write_ptr = (write_ptr + size) % bufsize;
//    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&locker);
}

int tspoolqueue::get_queue(uint8_t* buf, int size) {
 //   printf(" get queue : tid %lu write_ptr : %d read_ptr : %d\n",(unsigned long)pthread_self(),write_ptr,read_ptr);
    src = q_buf + read_ptr;
    int wrap = 0;
  //  printf("size = %d\n",size);

    pthread_mutex_lock(&locker);

    int pos = write_ptr;

    if (pos < read_ptr) {
        pos += bufsize;
        wrap = 1;
    }

    if ( (read_ptr + size) > pos) {
        pthread_mutex_unlock(&locker);
        return 1;
    }

    if (wrap) {
        fprintf(stdout, "wrap...\n");
        memcpy(buf, src, (bufsize - read_ptr));
        memcpy(buf+(bufsize - read_ptr), src+(bufsize - read_ptr), size-(bufsize - read_ptr));
    } else {
        memcpy(buf, src, sizeof(uint8_t)*size);
    }
    read_ptr = (read_ptr + size) % bufsize;
    pthread_mutex_unlock(&locker);

    return 0;
}


