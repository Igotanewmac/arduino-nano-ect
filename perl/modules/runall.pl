#!/usr/local/bin/perl

use warnings;
use strict;

my $filename = $ARGV[0];

print("Gate off.\n");
system( "./gate_off_power_test.pl" , $filename );
print("Gate on.\n");
system( "./gate_on_power_test.pl" , $filename );


print("Pin A rise threshold.\n");
system( "./pin_a_rise_threshold_test.pl" , $filename );
print("Pin B rise threshold.\n");
system( "./pin_b_rise_threshold_test.pl" , $filename );
print("Pin AB rise threshold.\n");
system( "./pin_ab_rise_threshold_test.pl" , $filename );

print("Pin A fall threshold.\n");
system( "./pin_a_fall_threshold_test.pl" , $filename );
print("Pin B fall threshold.\n");
system( "./pin_b_fall_threshold_test.pl" , $filename );
print("Pin AB fall threshold.\n");
system( "./pin_ab_fall_threshold_test.pl" , $filename );

print("Done!\n");







