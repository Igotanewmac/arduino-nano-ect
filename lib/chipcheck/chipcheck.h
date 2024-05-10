

#ifndef THESEAREMYCHIPCHECKTESTS_H
#define THESEAREMYCHIPCHECKTESTS_H

#include <Arduino.h>

#include <Wire.h>

#include <Adafruit_INA219.h>

#include <Adafruit_MCP4725.h>

#include <tests.h>

extern Adafruit_INA219 ina219_c1;
extern Adafruit_INA219 ina219_c2;
extern Adafruit_INA219 ina219_c3;
extern Adafruit_INA219 ina219_c4;
extern Adafruit_MCP4725 mcp4725_c1;
extern Adafruit_MCP4725 mcp4725_c2;




void command_chipcheck( String commandline );


void command_chipcheck_00();


#endif





