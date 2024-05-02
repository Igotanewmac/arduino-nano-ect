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
# $filecontents =~ s/\t([0-9])/\t $1/g;


$filecontents =~ /^PINBFALLTHRESHOLDTESTSTART\n(.*)^PINBFALLTHRESHOLDTESTEND$/sm;

my $datasection = $1;

my @results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );

mkdir("output");
my $outputfilename = "output/pin_b_fall_threshold_test.csv";
print("Saving to " . $outputfilename . "\n" );
open( my $outputfilehandle , ">" , $outputfilename );

foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}


close( $outputfilehandle );


