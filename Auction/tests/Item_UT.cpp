//
//  Item_UT.cpp
//  Auction_App2
//
//  Created by  Maulik Patel on 13/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>


#include "../Item.h"

TEST_CASE("GIVEN INPUT AGAINST GIVEN OUTPUT"){
    std::string status{};
    REQUIRE( 1==1 );
    Item I1 { "toaster_1", 10, 20, 1, 10.00 };          //  code, start_time, close_time, seller_id, reserve_price
    REQUIRE( I1.submitBid(12, 8, 7.5) == true );        //  Verify if valid bid submitted - format current_time,  bidder_id,  bid_amount
    REQUIRE( I1.submitBid(13, 5, 12.5) == true );       //  Verify if valid bid submitted - format current_time,  bidder_id,  bid_amount
    Item I2 { "tv_1", 15, 20, 8, 250.00 };              //  code, start_time, close_time, seller_id, reserve_price

    I1.updateStatus(16, status);
    REQUIRE ( status.compare("") == 0);                 // Auction not closed, no status update yet
    I2.updateStatus(16, status);
    REQUIRE ( status.compare("") == 0);                  // Auction not closed, no status update yet

    REQUIRE( I1.submitBid(17, 8, 20.00) == true );      //  Verify if valid bid submitted - format current_time,  bidder_id,  bid_amount
    REQUIRE( I2.submitBid(18, 1, 150.00) == true);      //  Verify if valid bid submitted - format current_time,  bidder_id,  bid_amount
    REQUIRE( I2.submitBid(19, 3, 200.00) == true);      //  Verify if valid bid submitted - format current_time,  bidder_id,  bid_amount

    I1.updateStatus(20, status);
    REQUIRE ( status.compare("20|toaster_1|8|SOLD|12.50|3|20.00|7.50") == 0);       // Verify item status  against given output @ close of auction

    I2.updateStatus(20, status);
    REQUIRE ( status.compare("20|tv_1||UNSOLD|0.00|2|200.00|150.00") == 0);         // Verify item status  against given output @ close of auction

    REQUIRE( I2.submitBid(21, 3, 300.00) == false);           //  Invalid bid, outside auction close time, do not accept here so check aginst false  - format current_time,  bidder_id,  bid_amount
    
}

