#include "bank.h"
#include "Arduino.h"


int currentBalance = 0;
int balance = 0;


void updateBalance(){
    //noen if setninger, if busstop = true osv.- så aktivere tickets og kaffe etc

    int ticketprice = 38;
    int coffeeprice = 19;

    int ticketssold = random(0,5);
    delay(200);
    int coffeesSold = random(0,ticketssold);
    delay(200);
    currentBalance = (coffeesSold * coffeeprice +  ticketssold * ticketprice );
    balance += currentBalance;
    Serial.println(balance);
}
