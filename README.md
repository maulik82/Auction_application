# Auction_application
Demo auction application which takes input from file and output all listing status

For detailed info on the application functionality, please refer to C++ Coding Challenge.rtf in this folder.

How to Build / Run Info:
===========================
1. To build application ( on command prompt / terminal )
-> cd Auction
-> make


2. To run applicaiton   ( on command prompt / terminal )
-> ./Auction


3. To build Unit Test (uses Catch2)  ( on command prompt / terminal )
-> cd Auction
-> make test


4. To run Unit test   ( on command prompt / terminal )
-> ./test



Some Notes
===================
=> g++ compiler with C++17 is used.
=> Might not work if you try to create project in X-Code using source files as std::filesystem is not yet available (as of today in Xcode), however with above mentioned commands on terminal, it should work fine.

