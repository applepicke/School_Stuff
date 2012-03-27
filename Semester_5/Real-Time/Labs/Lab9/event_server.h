#include <sys/siginfo.h>
#include <stdint.h>

/* if sharing a target, change this to something unique for you */
#define RECV_NAME "MSG_RECEIVER"

struct reg_msg {
    uint16_t type;
    struct sigevent ev;
};

#define REG_MSG 1024


