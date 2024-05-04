

#ifndef THESEAREMYTESTS_H
#define THESEAREMYTESTS_H

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>



#define COLUMN_SEPERATOR "\t"


extern Adafruit_INA219 ina219_c1;
extern Adafruit_INA219 ina219_c2;
extern Adafruit_INA219 ina219_c3;
extern Adafruit_INA219 ina219_c4;
extern Adafruit_MCP4725 mcp4725_c1;
extern Adafruit_MCP4725 mcp4725_c2;




void show_header();

void do_measure( uint32_t idcode );

void command_i2cscan();

void command_measureall();

void command_sweepall();






#endif





