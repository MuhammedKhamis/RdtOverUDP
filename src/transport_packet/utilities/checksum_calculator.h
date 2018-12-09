//
// Created by abdelrhman on 12/8/18.
//

#ifndef RDTOVERUDP_CHECKSUM_H
#define RDTOVERUDP_CHECKSUM_H

#include <cstdint>
#include <string>
#include "../packet.h"

using namespace std ;

class checksum_calculator {

   private:
     checksum_calculator();

   public:
     static checksum_calculator inst;
     static uint16_t get_checksum(string) ;
     static bool validate(uint16_t sent_checksum, uint16_t new_checksum) ;

};

#endif //RDTOVERUDP_CHECKSUM_H
