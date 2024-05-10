


#ifndef THESEAREMYCHIPCHECKTESTS_CPP
#define THESEAREMYCHIPCHECKTESTS_CPP

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

#include <tests.h>

#include <ect_tests.h>

#include <tgraph.h>


void command_chipcheck_00();



void command_chipcheck( String commandline ) {

    Serial.println( "Chipcheck called with: " );
    Serial.println( commandline );

    commandline = commandline.substring( 10 );

    uint8_t chipnumber = commandline.toInt();

    Serial.print( "chipid: " );
    Serial.println( chipnumber );

    switch (chipnumber)
    {
    case 00: command_chipcheck_00();
        break;
    
    default:
        break;
    }



};




void command_chipcheck_00() {

    Serial.println( "checking 74XX00 Series chip.");

    // 00 series.  2 input nand.

    // tests

    // gate on power usage
    //test_gate_on_power();

    // gate off power usage
    //test_gate_off_power();

    // sweep a
    //test_pinA_fall_threshold();
    //test_pinA_rise_threshold();

    // sweep b
    //test_pinB_fall_threshold();
    //test_pinB_rise_threshold();

    // sweep ab
    //test_pinAB_fall_threshold();
    //test_pinAB_rise_threshold();

    // tgraph
    Serial.println("tgraph 0 1" );
    command_transitioncheck( 1 , 0 );
    Serial.println("tgraph 1 0" );
    command_transitioncheck( 0 , 1 );
    
    
}

#endif
