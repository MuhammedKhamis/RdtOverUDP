/* import libraries */
/******************************************/
#include <zconf.h>
#include <netinet/in.h>
#include <transport_control/rdt_strategy.h>
#include "selective_repeat.h"

/* constructor */
/******************************************/
selective_repeat::selective_repeat(port_handler *p) : rdt_strategy(p){}
