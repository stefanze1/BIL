#include "bank.h"
#include "Arduino.h"


int currentBalance = 0;
int balance = 0;


void updateBalance(){
    //noen if setninger, if busstop = true osv.- så aktivere tickets og kaffe etc

    int ticketprice = 38;
    int coffeeprice = 19;

    int ticketssold = random(0,5);
    int coffeesSold = random(0,ticketssold);
    
    currentBalance = (coffeesSold * coffeeprice +  ticketssold * ticketprice );
    balance += currentBalance;
}
