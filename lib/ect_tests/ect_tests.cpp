


#ifndef THESEAREMYECTTESTS_CPP
#define THESEAREMYECTTESTS_CPP

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

#include <tests.h>

#include <ect_tests.h>



void command_do_all_tests() {

  Serial.println("All Tests");
  // all tests

  Serial.println("ALLTESTSSTART" );
  // power usage

  // gate on power
  test_gate_on_power();

  // gate off power
  test_gate_off_power();

  // rise

  // pinA rise threshold
  test_pinA_rise_threshold();

  // pinB rise threshold
  test_pinB_rise_threshold();

  // pinAB rise threshold
  test_pinAB_rise_threshold();

  // fall

  // pinA fall threshold
  test_pinA_fall_threshold();

  // pinB fall threshold
  test_pinB_fall_threshold();

  // pinAB fall threshold
  test_pinAB_fall_threshold();

  Serial.println( "ALLTESTSEND" );


}









// all tests




// power usage

// gate on power
void test_gate_on_power() {

  Serial.println("GATEONPOWERTESTSTART");

  // set up chip for test.
  mcp4725_c1.setVoltage( 4095 , false );
  mcp4725_c2.setVoltage( 4095 , false );

  show_header();

  do_measure( 0 );

  Serial.println("GATEONPOWERTESTEND");

}


// gate off power
void test_gate_off_power() {

  Serial.println("GATEOFFPOWERTESTSTART");

  // set up chip for test.
  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  do_measure( 0 );

  Serial.println("GATEOFFPOWERTESTEND");
  
}


// rise

// pinA rise threshold
void test_pinA_rise_threshold() {

  Serial.println("PINARISETHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 0 ; counter < HIGHTESTCOUNT ; counter++ ) {

    mcp4725_c1.setVoltage( counter , false );

    do_measure( counter );

  }

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  Serial.println("PINARISETHRESHOLDTESTEND");
  
}


// pinB rise threshold
void test_pinB_rise_threshold() {

  Serial.println("PINBRISETHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 0 ; counter < HIGHTESTCOUNT ; counter++ ) {

    mcp4725_c2.setVoltage( counter , false );

    do_measure( counter );

  }

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );


  Serial.println("PINBRISETHRESHOLDTESTEND");

  
}


// pinAB rise threshold
void test_pinAB_rise_threshold() {

  Serial.println("PINABRISETHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 0 ; counter < HIGHTESTCOUNT ; counter++ ) {

    mcp4725_c1.setVoltage( counter , false );
    mcp4725_c2.setVoltage( counter , false );

    do_measure( counter );

  }

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );


  Serial.println("PINABRISETHRESHOLDTESTEND");

  
}


// fall

// pinA fall threshold
void test_pinA_fall_threshold() {

  Serial.println("PINAFALLTHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 4095 ; counter > LOWTESTCOUNT ; counter-- ) {

    mcp4725_c1.setVoltage( counter , false );

    do_measure( 4095 - counter );

  }
  // mcp4725_c1.setVoltage( 0 , false );
  // do_measure( 4095 );

  mcp4725_c1.setVoltage( FINALTESTCOUNT , false );
  mcp4725_c2.setVoltage( FINALTESTCOUNT , false );  

  Serial.println("PINAFALLTHRESHOLDTESTEND");

  
}


// pinB fall threshold
void test_pinB_fall_threshold() {

  Serial.println("PINBFALLTHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 4095 ; counter > LOWTESTCOUNT ; counter-- ) {

    mcp4725_c2.setVoltage( counter , false );

    do_measure( 4095 - counter );

  }
  // mcp4725_c2.setVoltage( 0 , false );
  // do_measure( 4095 );

  mcp4725_c1.setVoltage( FINALTESTCOUNT , false );
  mcp4725_c2.setVoltage( FINALTESTCOUNT , false );  


  Serial.println("PINBFALLTHRESHOLDTESTEND");

  
}


// pinAB fall threshold
void test_pinAB_fall_threshold() {

  Serial.println("PINABFALLTHRESHOLDTESTSTART");

  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  for ( uint16_t counter = 4095 ; counter > LOWTESTCOUNT ; counter-- ) {

    mcp4725_c1.setVoltage( counter , false );
    mcp4725_c2.setVoltage( counter , false );

    do_measure( 4095 - counter );

  }
  // mcp4725_c1.setVoltage( 0 , false );
  // mcp4725_c2.setVoltage( 0 , false );
  // do_measure( 4095 );

  mcp4725_c1.setVoltage( FINALTESTCOUNT , false );
  mcp4725_c2.setVoltage( FINALTESTCOUNT , false );  

  Serial.println("PINABFALLTHRESHOLDTESTEND");

  
}




#endif
