


#ifndef THESEAREMYTESTS_CPP
#define THESEAREMYTESTS_CPP

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

#include <tests.h>



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



#endif
