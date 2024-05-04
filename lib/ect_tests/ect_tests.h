

#ifndef THESEAREMYECTTESTS_H
#define THESEAREMYECTTESTS_H

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


// RISE MAX
#define HIGHTESTCOUNT 4096

// FALL MIN
#define LOWTESTCOUNT 0
#define FINALTESTCOUNT 0



// all tests


// power usage

void command_do_all_tests();



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




#endif





