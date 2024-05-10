#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>



#include <tests.h>
#include <ect_tests.h>
#include <tgraph.h>
#include <chipcheck.h>


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

  


  // gate on power
  if ( commandline.startsWith( "gate_on_power" ) ) { test_gate_on_power(); }

  // gate off power
  if ( commandline.startsWith( "gate_off_power" ) ) { test_gate_off_power(); }

  // rise

  // pinA rise threshold
  if ( commandline.startsWith( "pinA_rise_threshold" ) ) { test_pinA_rise_threshold(); }

  // pinB rise threshold
  if ( commandline.startsWith( "pinB_rise_threshold" ) ) { test_pinB_rise_threshold(); }

  // pinAB rise threshold
  if ( commandline.startsWith( "pinAB_rise_threshold" ) ) { test_pinAB_rise_threshold(); }

  // fall

  // pinA fall threshold
  if ( commandline.startsWith( "pinA_fall_threshold" ) ) { test_pinA_fall_threshold(); }

  // pinB fall threshold
  if ( commandline.startsWith( "pinB_fall_threshold" ) ) { test_pinB_fall_threshold(); }

  // pinAB fall threshold
  if ( commandline.startsWith( "pinAB_fall_threshold" ) ) { test_pinAB_fall_threshold(); }


  // do all available tests
  if ( commandline.startsWith( "doalltests" ) ) { command_do_all_tests(); }


  // transition graph test
  if ( commandline.startsWith( "tgraph" ) ) { command_tgraph( commandline ); }






  if ( commandline.startsWith( "transitioncheck00" ) ) { command_transitioncheck( 0 , 0 ); }
  if ( commandline.startsWith( "transitioncheck01" ) ) { command_transitioncheck( 0 , 1 ); }
  if ( commandline.startsWith( "transitioncheck10" ) ) { command_transitioncheck( 1 , 0 ); }
  if ( commandline.startsWith( "transitioncheck11" ) ) { command_transitioncheck( 1 , 1 ); }

  if ( commandline.startsWith( "chipcheck " ) ) { command_chipcheck(commandline); }



  Serial.println("CMDINPUTREADY\n");

}















































