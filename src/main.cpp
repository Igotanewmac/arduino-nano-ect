#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>



#include <tests.h>
#include <ect_tests.h>
#include <tgraph.h>



// Scanning...
// I2C device found at address 0x40  !
// I2C device found at address 0x41  !
// I2C device found at address 0x44  !
// I2C device found at address 0x45  !
// I2C device found at address 0x60  !
// I2C device found at address 0x61  !
// done






#define INA219_addr_c1 0x40
#define INA219_addr_c2 0x41
#define INA219_addr_c3 0x44
#define INA219_addr_c4 0x45

#define MPC4725_addr_c1 0x60
#define MPC4725_addr_c2 0x61

Adafruit_INA219 ina219_c1( INA219_addr_c1 );
Adafruit_INA219 ina219_c2( INA219_addr_c2 );
Adafruit_INA219 ina219_c3( INA219_addr_c3 );
Adafruit_INA219 ina219_c4( INA219_addr_c4 );

Adafruit_MCP4725 mcp4725_c1;
Adafruit_MCP4725 mcp4725_c2;



#define COLUMN_SEPERATOR "\t"





void command_transitioncheck( uint8_t direction , uint8_t checktype );







void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ina219_c1.begin();
  ina219_c1.setCalibration_16V_400mA();
  ina219_c2.begin();
  ina219_c2.setCalibration_16V_400mA();
  ina219_c3.begin();
  ina219_c3.setCalibration_16V_400mA();
  ina219_c4.begin();
  ina219_c4.setCalibration_16V_400mA();
  
  mcp4725_c1.begin( MPC4725_addr_c1 );
  mcp4725_c2.begin( MPC4725_addr_c2 );

  Serial.println("CMDINPUTREADY\n");
  Serial.println("Ready!\n");
  Serial.print("<< ");
  
}




void loop() {
  // put your main code here, to run repeatedly:

  // await serial input.
  if (!Serial.available()) {
    return;
  }

  // get first line
  String commandline = Serial.readStringUntil( 0x0A );

  // discard the rest
  while ( Serial.available() ) { Serial.read(); }

  // repeat it
  Serial.print(">> " );
  Serial.println( commandline );


  // enumerate the i2c bus.
  if ( commandline.startsWith( "i2cscan" ) ) { command_i2cscan(); }


  // measure all voltages now
  if ( commandline.startsWith( "measureall" ) ) { command_measureall(); }

  // sweep all dacs now
  if ( commandline.startsWith( "sweepall" ) ) { command_sweepall(); }

  
  // do all available tests
  if ( commandline.startsWith( "doalltests" ) ) { command_do_all_tests(); }


  // transition graph test
  if ( commandline.startsWith( "tgraph" ) ) { 
    commandline = commandline.substring( commandline.indexOf( " " ) + 1 );
    
    if ( commandline.startsWith( "and" ) ) {
      Serial.println("Transition Graph for AND gate.");
      show_header();
      Serial.println( "0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0\t0.0" );
      command_transitioncheck(0,0);
      command_transitioncheck(1,1);
      Serial.println( "5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0\t5.0" );
    }

    

   }



  if ( commandline.startsWith( "transitioncheck00" ) ) { command_transitioncheck( 0 , 0 ); }
  if ( commandline.startsWith( "transitioncheck01" ) ) { command_transitioncheck( 0 , 1 ); }
  if ( commandline.startsWith( "transitioncheck10" ) ) { command_transitioncheck( 1 , 0 ); }
  if ( commandline.startsWith( "transitioncheck11" ) ) { command_transitioncheck( 1 , 1 ); }



  Serial.println("CMDINPUTREADY\n");

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






















