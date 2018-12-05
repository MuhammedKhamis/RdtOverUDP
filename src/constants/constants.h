#ifndef CONSTANTS_H
#define CONSTANTS_H


#define MAX_REQ_SZ 1024
#define MSS 512
#define INITIAL_THRESHOLD 64 * MSS


/* event types for congestion control */
enum EVENT_TYPE {ACK, TIMEOUT};



#endif
