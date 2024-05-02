#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

// Scanning...
// I2C device found at address 0x40  !
// I2C device found at address 0x41  !
// I2C device found at address 0x44  !
// I2C device found at address 0x45  !
// I2C device found at address 0x60  !
// I2C device found at address 0x61  !
// done


// RISE MAX
#define HIGHTESTCOUNT 4096

// FALL MIN
#define LOWTESTCOUNT 0
#define FINALTESTCOUNT 0




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




void command_i2cscan();

void command_measureall();

void command_sweepall();




void command_do_all_tests();





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


  Serial.println("CMDINPUTREADY\n");

}








void command_i2cscan() {
  
  byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  return;

}










#define COLUMN_SEPERATOR "\t"

void command_measureall() {


  Serial.print( "Chan" ); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Shunt"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Bus"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Current"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Power");
  Serial.println("");

  //loadvoltage = busvoltage + (shuntvoltage / 1000);



  Serial.print( "1" ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c1.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c1.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c1.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c1.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
  Serial.println("");

  Serial.print( "2" ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c2.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c2.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c2.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c2.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
  Serial.println("");

  Serial.print( "3" ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c3.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c3.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c3.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c3.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
  Serial.println("");

  Serial.print( "4" ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c4.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c4.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c4.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
  Serial.print( ina219_c4.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
  Serial.println("");

  
  
  



}






void command_sweepall() {

  uint32_t counter;
    // Run through the full 12-bit scale for a triangle wave
    for (counter = 0; counter < 4095; counter++)
    {
      mcp4725_c1.setVoltage(counter, false);
      mcp4725_c2.setVoltage(counter, false);
    }
    for (counter = 4095; counter > 0; counter--)
    {
      mcp4725_c1.setVoltage(counter, false);
      mcp4725_c2.setVoltage(counter, false);
    }

    Serial.println("Done!\n");

}


















// all tests


// power usage

// gate on power
void test_gate_on_power();

// gate off power
void test_gate_off_power();

// rise

// pinA rise threshold
void test_pinA_rise_threshold();

// pinB rise threshold
void test_pinB_rise_threshold();

// pinAB rise threshold
void test_pinAB_rise_threshold();

// fall

// pinA fall threshold
void test_pinA_fall_threshold();

// pinB fall threshold
void test_pinB_fall_threshold();

// pinAB fall threshold
void test_pinAB_fall_threshold();



void show_header() {
  Serial.print("test"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Shunt"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Bus"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Current"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Power"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Shunt"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Bus"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Current"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Power"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Shunt"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Bus"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Current"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Power"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Shunt"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Bus"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Current"); Serial.print( COLUMN_SEPERATOR );
  Serial.print("Power");
  Serial.println();
}

void do_measure( uint32_t idcode ) {
    Serial.print( idcode ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c1.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c1.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c1.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c1.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c2.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c2.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c2.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c2.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c3.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c3.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c3.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c3.getPower_mW() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c4.getShuntVoltage_mV() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c4.getBusVoltage_V() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c4.getCurrent_mA() ); Serial.print( COLUMN_SEPERATOR );
    Serial.print( ina219_c4.getPower_mW() );
    Serial.println();
}



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
  mcp4725_c1.setVoltage( 0 , false );
  mcp4725_c2.setVoltage( 0 , false );

  show_header();

  do_measure( 0 );

  Serial.println("GATEONPOWERTESTEND");

}




// gate off power
void test_gate_off_power() {

  Serial.println("GATEOFFPOWERTESTSTART");

  // set up chip for test.
  mcp4725_c1.setVoltage( 4095 , false );
  mcp4725_c2.setVoltage( 4095 , false );

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
















