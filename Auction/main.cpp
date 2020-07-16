//
//  main.cpp
//  Auction_App4
//
//  Created by  Maulik Patel on 13/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//

#include <fstream>
#include <vector>
#include "Item.h"
#include <filesystem>

//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/directory.hpp>
//#include <boost/filesystem/path.hpp>

extern void Item_UT( void );
void extractAllInputs( std::vector<std::string> &inputVector, std::string &line, size_t numInputs, char delimiter);
size_t searchItemByCode( const std::vector<Item> &items, std::string code );


int main(int argc, const char * argv[]) {

    {
//        Item_UT();
//        std::string cd = "/Users/Emsys/Projects/Xcode_c++/Auction/Auction/";
        std::string cd = std::filesystem::current_path();   //for eclipse.. does not work in xcode
//        auto path{boost::filesystem::path full_path( boost::filesystem::current_path() );};
        std::string inputFileName {"input.txt"};
        std::string inputFilePath = cd+'/'+inputFileName;

        std::ifstream inputFile{ inputFilePath };            // Input file handle
        if( !inputFile )
        {
            std::cout << "Cannot open input file : " << inputFilePath<< std::endl;
            return 1;
        }
        
//        std::cout << "Start of auction !\n";
        std::vector<Item> items;

        const char pipe {'|'};
        std::string line;
        std::string output_log {};
        while( std::getline( inputFile, line ))
        {
            size_t numInputs{1};
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());  // remove all white space
            std::vector<std::string> inputVector;            // input string vector for storing all inputs on line
            extractAllInputs( inputVector, line, numInputs, pipe);

            int current_time { std::stoi (inputVector.at(0)) }; // update current time;

            //TODO: CHECK INPUT  MESSAGE VALIDITY
            if(inputVector.size() >  1)
            {
                int user_id = std::stoi (inputVector.at(1));
                if( inputVector.at(2).compare("SELL") == 0 )        // Selling an item?
                {
                    long int start_time { std::stoll (inputVector.at(0))};
                    std::string item_code {inputVector.at(3)};
                    double reserve_price {std::stod (inputVector.at(4))};
                    long int close_time {std::stoll (inputVector.at(5))};
                   
                    size_t itemId = searchItemByCode(items, item_code );
                    if (itemId >= items.size())
                    {
                        items.push_back ( {item_code, start_time, close_time, user_id, reserve_price} );   //new item
                    }
                    else
                    {
                        std::cerr << "Item already exist in Database, please relist with new code" << std::endl;
                    }
                }
                else if( inputVector.at(2).compare("BID") == 0 )    // Bidding on item?
                {
                    long int bid_time { std::stoll (inputVector.at(0))};
                    std::string item_code {inputVector.at(3)};
                    double bid_amount {std::stod (inputVector.at(4))};

                    size_t itemId = searchItemByCode(items, item_code );
                    if (itemId >= items.size())
                    {
                        std::cerr << "Bidding on item which do not exist! please check code " << std::endl;
                    }
                    else
                    {
                        items.at(itemId).submitBid( bid_time, user_id, bid_amount );
                    }
                }
                else
                {
                    std::cerr << "Invalid input :: CHECK BID OR SELL ACTION!" << std::endl;
                }
            }

            for( size_t i{0}; i<items.size(); i++ )
            {
                items.at(i).updateStatus( current_time, output_log );
            }
            
        }       // end of while( std::getline( inputFile, line ))
    }       // end of auction block

    
    return 0;
}


void extractAllInputs( std::vector<std::string> &inputVector, std::string &line, size_t numInputs, char delimiter)
{
    std::string inputString;
    for(size_t i{0}; i < line.size(); i++)
    {
        if(line.at(i) == delimiter)
        {
            inputVector.push_back( inputString );  // store the extracted string to vector
            inputString="";
        }
        else
            inputString+=line[i];
    }
    inputVector.push_back( inputString );  // store the extracted string to vector
}


size_t searchItemByCode( const std::vector<Item> &items, std::string code )
{
    for( size_t i{0}; i<items.size(); i++ )
    {
        if(items.at(i).getCode() == code)
            return i;
    }
    return ( items.size() );
}
