//
//  Item.cpp
//  Auction_app4
//
//  Created by  Maulik Patel on 15/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#include "Item.h"



std::ostream& operator<<(std::ostream &out, const Item& item )
{

    if(item.m_status  == "SOLD")
    {
        std::ostringstream streamObj;
        streamObj << std::fixed;
        streamObj << std::setprecision(2);

        streamObj << std::to_string(item.m_close_time) << "|" << item.m_code << "|" << std::to_string(item.m_winner_id)
        << "|" << item.m_status << "|" << item.m_price_paid  << "|" << std::to_string(item.m_bid_count)
        << "|" << item.m_highest_bid << "|" << item.m_lowest_bid ;
        std::string outstr = streamObj.str();
        out << outstr <<  std::endl;

    }
    else
    {
        std::ostringstream streamObj;
        streamObj << std::fixed;
        streamObj << std::setprecision(2);

        streamObj << std::to_string(item.m_close_time) << "|" << item.m_code << "|"
        << "|" << item.m_status << "|" << item.m_price_paid  << "|" << std::to_string(item.m_bid_count)
        << "|" << item.m_highest_bid << "|" << item.m_lowest_bid;
        std::string outstr = streamObj.str();
        
        out << outstr <<  std::endl;
    }
    return out;
}
    




Item::Item( std::string code, long int start_time, long int close_time, int seller_id, double reserve_price ) :
    m_code{ code }, m_start_time { start_time }, m_close_time { close_time },  m_seller_id { seller_id }, m_reserve_price { reserve_price }
{
//    std::cout  << "Listing "<< m_code << ", start time: " << m_start_time << ", close time: " << m_close_time
//    << ", seller id: " << m_seller_id << ", Reserve price: " << m_reserve_price  << std::endl;
}


bool Item::submitBid(  long int current_time, int bidder_id, double bid_amount )
{
    if( (current_time < m_start_time ) || ( current_time > m_close_time ) )     return false;       // invalid bid - outside time range
    if ( bid_amount <= m_current_sp )      return false;        // invalid bid - need to enter high amount
    if ( m_seller_id == bidder_id )     return false;           // seller cannot bid on his own item
    addBid( bidder_id, bid_amount );
    return true;
}

void Item::addBid( int bidder_id, double bid_amount )
{
    m_bid_count++; // update bid count
    if( m_bid_count == 1 )      // first bid on item;
        m_lowest_bid = bid_amount;          // log lowest bid
    
    if( !m_reserve_met )
    {
        if( bid_amount >= m_reserve_price )
        {
            m_reserve_met = true;
            m_status = "SOLD";
            m_price_paid = m_reserve_price;     // for single bid, buyer pays the reserve amount
            m_winner_id = bidder_id;            // log bidder id
        }
        m_current_sp = m_highest_bid;       // update current selling price . i.e 2nd highest bid
        m_highest_bid = bid_amount;         // update bid amount to highest bid
    }
    else
    {
        m_current_sp = m_highest_bid;       // update current selling price . i.e 2nd highest bid
        m_highest_bid = bid_amount;         // update bid amount to highest bid
        m_price_paid = m_current_sp;        // price paid should be current selling price or second highest bid;
        m_winner_id = bidder_id;            // log bidder id
    }
}
    
void Item::updateStatus ( long int current_time, std::string& log )
{
    if( (current_time >= m_close_time) && (!m_status_printed) )
    {
        m_status_printed = true;
//        std::cout << *this;
        if(m_status  == "SOLD")
         {
             std::ostringstream streamObj;
             streamObj << std::fixed;
             streamObj << std::setprecision(2);

             streamObj << std::to_string(m_close_time) << "|" << m_code << "|" << std::to_string(m_winner_id)
             << "|" << m_status << "|" << m_price_paid  << "|" << std::to_string(m_bid_count)
             << "|" << m_highest_bid << "|" << m_lowest_bid ;
             log = streamObj.str();
             std::cout << log <<  std::endl;

         }
         else
         {
             std::ostringstream streamObj;
             streamObj << std::fixed;
             streamObj << std::setprecision(2);

             streamObj << std::to_string(m_close_time) << "|" << m_code << "|"
             << "|" << m_status << "|" << m_price_paid  << "|" << std::to_string(m_bid_count)
             << "|" << m_highest_bid << "|" << m_lowest_bid;
             log = streamObj.str();
             std::cout << log <<  std::endl;
         }
    }
    
    
    
    
}
