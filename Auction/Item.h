//
//  Item.h
//  Auction_App2
//
//  Created by  Maulik Patel on 13/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Item{
    std::string m_status {"UNSOLD"};
    std::string m_code;
    std::time_t m_start_time;
    std::time_t m_close_time;
    int m_seller_id;
    double m_reserve_price;     //TODO: remove reserve price visibility to public, if not required
    int m_bid_count{0};
    double m_highest_bid{0};
    double m_current_sp{0};
    double m_lowest_bid{0};
    double m_price_paid{0};
    bool m_reserve_met{false};
    bool m_status_printed{false};
    std::string m_output{""};
    int m_winner_id;
    
public:
    ~Item()   {
//        std::cout << "Removing " << m_code<< std::endl;
    }

    Item( std::string code, long int start_time, long int close_time, int seller_id, double reserve_price ) ;

    friend std::ostream& operator<<(std::ostream &out, const Item& item );
        
    std::string getCode() const { return m_code;}
        
    bool submitBid(  long int current_time, int bidder_id, double bid_amount );

    void addBid( int bidder_id, double bid_amount );

    void updateStatus ( long int current_time, std::string& log );

};
