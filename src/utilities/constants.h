#ifndef CONSTANTS_H
#define CONSTANTS_H


#define MAX_REQ_SZ 1024
#define HEADER_SZ 58
#define DELM "\r\n"

#define CS_IDX 0
#define LEN_IDX 1
#define SEQ_IDX 2

#define DATA_SZ 500

/* event types for congestion control */
enum EVENT_TYPE {ACK, TIMEOUT};

enum PKT_STATUS {ACKED, NOT_SEND};

#define MSS 512
#define INITIAL_THRESHOLD 64 * MSS

#endif
