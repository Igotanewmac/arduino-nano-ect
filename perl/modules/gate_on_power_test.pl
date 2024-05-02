#!/usr/local/bin/perl

use warnings;
use strict;

use Data::Dumper qw(Dumper);

my $filename = $ARGV[0];

print( "Opening file: " . $filename . "\n" );

open(my $filehandle, '<', $filename) or die "FAIL: $filename : $!\n";
my $filecontents = do { local($/); <$filehandle> };
close($filehandle);

print( "read " . length($filecontents) . " bytes of data.\n" );

$filecontents =~ s/\r//g;
$filecontents =~ s/\t([0-9])/\t $1/g;


$filecontents =~ /^GATEONPOWERTESTSTART\n(.*)^GATEONPOWERTESTEND$/sm;

my $datasection = $1;

my @results = ( $datasection =~ /-? ?[0-9\.]+/g );


print( "Channel\tShunt\tBus\tCurrent\tPower\n");
print( "VCC\t" . $results[1] . "\t" . $results[2] . "\t" . $results[3] . "\t" . $results[4] . "\n" );
print( "OUT\t" . $results[5] . "\t" . $results[6] . "\t" . $results[7] . "\t" . $results[8] . "\n" );
print( "INA\t" . $results[9] . "\t" . $results[10] . "\t" . $results[11] . "\t" . $results[12] . "\n" );
print( "INB\t" . $results[13] . "\t" . $results[14] . "\t" . $results[15] . "\t" . $results[16] . "\n" );
