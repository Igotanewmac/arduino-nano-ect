


#ifndef THESEAREMYTGRAPHTESTS_CPP
#define THESEAREMYTGRAPHSTESTS_CPP

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

#include <tests.h>

#include <tgraph.h>





void command_tgraph(String commandline) {

    commandline = commandline.substring( commandline.indexOf( " " ) + 1 );
    
    
    if ( commandline.startsWith( "and" ) ) {
      Serial.println("Transition Graph for AND gate.");
      show_header();
      Serial.println( "0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0" );
      command_transitioncheck(0,0);
      command_transitioncheck(1,1);
      Serial.println( "5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0" );
      Serial.println("ALLTESTSEND");
    }





}








/// @brief Perform a sweep test for a transition value
/// @param direction Direction to sweep. 0 = up, 1 = down.
/// @param checktype Type of output to check for. 0 = low to high, 1 = high to low.
void command_transitioncheck( uint8_t direction , uint8_t checktype ) {

  // show_header();

  if ( !direction ) {
    // sweep up
    mcp4725_c1.setVoltage( 0 , false );
    mcp4725_c2.setVoltage( 0 , false );
    for ( uint16_t loopcounter = 0 ; loopcounter < 4096 ; loopcounter++ ) {
      mcp4725_c1.setVoltage( loopcounter , false );
      mcp4725_c2.setVoltage( loopcounter , false );
      delay(1);
      float busvoltage = ina219_c2.getBusVoltage_V();
      if (!checktype) {
        // low to high
        if ( busvoltage > 0.5 ) { 
          //low to high has triggered
          do_measure(0);
          break;
        }
      }
      else {
        // high to low
        if ( busvoltage < 4.0 ) {
          // high to low has triggered
          do_measure(0);
          break;
        }
      }
    }
  }
  else {
    // sweep down
    mcp4725_c1.setVoltage( 0 , false );
    mcp4725_c2.setVoltage( 0 , false );
    for ( uint16_t loopcounter = 4095 ; loopcounter > 0 ; loopcounter-- ) {
      mcp4725_c1.setVoltage( loopcounter , false );
      mcp4725_c2.setVoltage( loopcounter , false );
      delay(1);
      float busvoltage = ina219_c2.getBusVoltage_V();
      if (!checktype) {
        // low to high
        if ( busvoltage > 1.0 ) { 
          //low to high has triggered
          do_measure(0);
          break;
        }
      }
      else {
        // high to low
        if ( busvoltage < 4.0 ) {
          // high to low has triggered
          do_measure(0);
          break;
        }
      }
    }
  }





  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );
   




}







#endif


