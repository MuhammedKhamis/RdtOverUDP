//
// Created by abdelrhman on 12/8/18.
//


/**
 *  ack_tests
 *
 *  789123456
 *    ^^
 *    es  e = 3 , s = 3
 *
 *    mark(seq = 9)
 *
 *    real_index = (3  + 8) % 9 = 2 correct
 *
 *    law = (s + seq - data[s]) % size
 *
 *  123456789
 *  ^       ^
 *  s       e  s = 0 , e = 0
 *
 *    mark(seq = 8)
 *
 *    real_index = (0 + 8 - 1) % 9 = 7 correct
 *
 *  234567891
 *         ^^
 *         es  s = 8 , e = 8
 *
 *    mark(seq = 6)
 *
 *    real_index = (8 + 6 - 1) % 9 = 4 correct
 *
 *
 * */

 /*
  * 10000 size = 1 , s = 0 , e = 1
  * insert(seq = 2)
  * 12000 size = 2 , s = 0 , e = 2
  * insert(seq = 3)
  * 12300 size = 3 , s = 0 , e = 3
  * insert(seq = 4)
  * 12340 size = 4 , s = 0 , e = 4
  * insert(seq = 2)
  * 12345 size = 5 , s = 0 , e = 0
  * insert(seq = 2)
  *
  * isfull() size == real_size -> correct
  *
  * mark(2)
  * 10345  size = 5 , s = 0 , e = 0
  * mark(1)
  * 00345  size = 3 , s = 2 , e = 0
  * mark(3)
  * 00045  size = 2 , s = 3 , e = 0
  * mark(4)
  * 00005  size = 1 , s = 4 , e = 0
  * insert(6)
  * 60005  size = 2 , s = 4 , e = 1
  * insert(7)
  * 67005  size = 3 , s = 4 , e = 2
  * mark(7)
  *        real_index = (4 + 7 - 5) % 5  = 1
  *
  * 60005  size =  3 , s = 4 , e = 2
  * mark(6)
  * 00005  size = 3 , s = 4 , e = 2
  * mark(5) --> here must return only 3
  * 00000 size = 0 , s = 2 , e = 2
  *
  * */

/*
 * resize
 *
 * 0000012340000 s = 6 , e = 10 , size = 4 resize t0 ---> 3
 *
 *      put s = 0
 *
 *      law = (seq - data[s]) % n_size
 *
 * --> 123
 *
 * 10 11 12 0 0 0 0 0 0 0 6 7 8 9 s = 10 , e = 3 , size = 8
 *
 * --> 6 7 8 9 10 11 12 0 0
 *
 *  so put all from start :D
 *
 *
 *
 * */





#include <boost/test/unit_test.hpp>
#include "../../src/transport_protocols/transport_control/utilities/packet_window.h"


namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(suite1, * utf::label("circular-array-tests"))

  BOOST_AUTO_TEST_CASE(test_insert){
    circular_array array(8) ;
    array.insert(packet_info{1,0,clock()}) ;
    array.insert(packet_info{2,0,clock()}) ;
    array.insert(packet_info{3,0,clock()}) ;
    array.insert(packet_info{4,0,clock()}) ;
    array.insert(packet_info{5,0,clock()}) ;
    array.insert(packet_info{6,0,clock()}) ;
    array.insert(packet_info{7,0,clock()}) ;
    array.mark_acked(1);
    array.mark_acked(2);
    array.mark_acked(3);
    array.mark_acked(4);
    /*  00005670   */
    array.insert(packet_info{8,0,clock()}) ;
    array.insert(packet_info{9,0,clock()}) ;
    array.insert(packet_info{10,0,clock()}) ;
    /* 9 10 0 0 5 6 7 8 */
    vector<packet_info>::iterator i = array.begin() ;
    BOOST_REQUIRE((*i).seq_no == 9);
    BOOST_REQUIRE((*(i+1)).seq_no == 10);
    BOOST_REQUIRE((*(i+4)).seq_no == 5);
    BOOST_REQUIRE((*(i+5)).seq_no == 6);
    BOOST_REQUIRE((*(i+6)).seq_no == 7);
    BOOST_REQUIRE((*(i+7)).seq_no == 8);
    BOOST_REQUIRE(array.get_index(10).seq_no == 10) ;
    BOOST_REQUIRE(array.get_index(9).seq_no == 9) ;
    BOOST_REQUIRE(array.get_index(5).seq_no == 5) ;
    BOOST_REQUIRE(array.get_index(8).seq_no == 8) ;
    BOOST_REQUIRE(array.get_index(7).seq_no == 7) ;
    BOOST_REQUIRE(array.get_index(6).seq_no == 6) ;

    array.update_array(6) ;
    BOOST_REQUIRE(array.get_index(5).seq_no == 5) ;
    BOOST_REQUIRE(array.get_index(8).seq_no == 8) ;
    BOOST_REQUIRE(array.get_index(7).seq_no == 7) ;
    BOOST_REQUIRE(array.get_index(6).seq_no == 6) ;

}


BOOST_AUTO_TEST_SUITE_END()
