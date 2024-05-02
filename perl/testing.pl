#!/usr/local/bin/perl

use warnings;
use strict;

use Device::SerialPort;

use Time::HiRes qw(usleep);

my $cmdlinechipname = $ARGV[0];
if ( not defined( $cmdlinechipname ) ) { die( "No chip name spcified!\n") };
# mkdir( $cmdlinechipname ) or die("Cannot create output directory: " . $cmdlinechipname . "\n" );
mkdir( $cmdlinechipname );
mkdir( $cmdlinechipname . "/data" );
mkdir( $cmdlinechipname . "/graphs" );


my $cmdlinefilename = $ARGV[1];
if ( not defined( $cmdlinefilename ) ) { 
    print( "No port specified, using: /dev/cu.usbserial-14120\n");
    $cmdlinefilename = "/dev/cu.usbserial-14120";
 };

my $serialporthandle = Device::SerialPort->new( $cmdlinefilename );

if ( not defined( $serialporthandle ) ) {
    die( "Could not open serial port located at:" . $cmdlinefilename . "\n" );
}

$serialporthandle->baudrate(115200);
$serialporthandle->databits(8);
$serialporthandle->parity("none");
$serialporthandle->stopbits(1);




sub waitforcontent {

    my $searchstring = shift;
    my $rawinputbuffer = "";
    my $loopvar = 1;
    my $inputcounter = 0;

    while ( $loopvar ) {

        my $tempvar = $serialporthandle->read(255);

        if ( $tempvar ) {

            $inputcounter += 1;
            if ( $inputcounter > 1024 ) {
                $inputcounter = 0;
                print ".";
                select()->flush();
            }

            $rawinputbuffer .= $tempvar;

            if ( substr( $rawinputbuffer , -64 ) =~ /$searchstring/) {

                $loopvar = 0;
                print "ok!\n";
            }

        }

        # sleep for 1 millisecond between serial calls.
        #usleep( 1000 );

    }

    return $rawinputbuffer;
}












print "Waiting for uno to report ready.\n";

waitforcontent("CMDINPUTREADY");

print "Running all tests on chip. Please wait.\n";

$serialporthandle->write("doalltests\n");

my $rawresultsvar = waitforcontent("ALLTESTSEND");

print "Tests completed.\n";

print "received " . length( $rawresultsvar ) . " bytes\n";






print "Processing.\n";

# some handy globals!

# the data section of the results for this specific test.
my $datasection = "";

# handy output file structure storage
my $outputfilehandle;
my $outputfilename;

# some handy results storage
my @results;


print "Gate on power test.\n";
$rawresultsvar =~ /GATEONPOWERTESTSTART(.*)GATEONPOWERTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find gate on power test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/gate_on_power_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /-? ?[0-9\.]+/g );
print $outputfilehandle "Channel\tShunt\tBus\tCurrent\tPower\n";
print $outputfilehandle "VCC\t" . $results[1] . "\t" . $results[2] . "\t" . $results[3] . "\t" . $results[4] . "\n";
print $outputfilehandle "OUT\t" . $results[5] . "\t" . $results[6] . "\t" . $results[7] . "\t" . $results[8] . "\n";
print $outputfilehandle "INA\t" . $results[9] . "\t" . $results[10] . "\t" . $results[11] . "\t" . $results[12] . "\n";
print $outputfilehandle "INB\t" . $results[13] . "\t" . $results[14] . "\t" . $results[15] . "\t" . $results[16] . "\n";
close( $outputfilehandle );





print "Gate off power test.\n";
$rawresultsvar =~ /GATEOFFPOWERTESTSTART(.*)GATEOFFPOWERTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find gate off power test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/gate_off_power_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /-? ?[0-9\.]+/g );
print $outputfilehandle "Channel\tShunt\tBus\tCurrent\tPower\n";
print $outputfilehandle "VCC\t" . $results[1] . "\t" . $results[2] . "\t" . $results[3] . "\t" . $results[4] . "\n";
print $outputfilehandle "OUT\t" . $results[5] . "\t" . $results[6] . "\t" . $results[7] . "\t" . $results[8] . "\n";
print $outputfilehandle "INA\t" . $results[9] . "\t" . $results[10] . "\t" . $results[11] . "\t" . $results[12] . "\n";
print $outputfilehandle "INB\t" . $results[13] . "\t" . $results[14] . "\t" . $results[15] . "\t" . $results[16] . "\n";
close( $outputfilehandle );





print "Pin A rise threshold.\n";
$rawresultsvar =~ /PINARISETHRESHOLDTESTSTART(.*)PINARISETHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin A rise threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_a_rise_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );





print "Pin B rise threshold.\n";
$rawresultsvar =~ /PINBRISETHRESHOLDTESTSTART(.*)PINBRISETHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin B rise threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_b_rise_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );





print "Pin AB rise threshold.\n";
$rawresultsvar =~ /PINABRISETHRESHOLDTESTSTART(.*)PINABRISETHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin AB rise threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_ab_rise_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );










print "Pin A fall threshold.\n";
$rawresultsvar =~ /PINAFALLTHRESHOLDTESTSTART(.*)PINAFALLTHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin A fall threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_a_fall_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );



print "Pin B fall threshold.\n";
$rawresultsvar =~ /PINBFALLTHRESHOLDTESTSTART(.*)PINBFALLTHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin B fall threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_b_fall_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );




print "Pin AB fall threshold.\n";
$rawresultsvar =~ /PINABFALLTHRESHOLDTESTSTART(.*)PINABFALLTHRESHOLDTESTEND/sm;
$datasection = $1;
if ( not defined( $datasection ) ) { die( "Could not find pin AB fall threshold test segment!\n" ); }
$outputfilename = $cmdlinechipname . "/data/pin_ab_fall_threshold_test.tsv";
print("Saving to " . $outputfilename . "\n" );
open( $outputfilehandle , ">" , $outputfilename) or die( "Could not open " . $outputfilename . " for output!\n");
@results = ( $datasection =~ /[0-9\-]+[0-9\-\.\t]+/g );
foreach my $resultrow (@results) {
    print( $outputfilehandle  $resultrow . "\n" );
}
close( $outputfilehandle );








# Anger the recursion gods!

my @files = (  
    "pin_a_rise_threshold_test.tsv",
    "pin_b_rise_threshold_test.tsv",
    "pin_ab_rise_threshold_test.tsv",
    "pin_a_fall_threshold_test.tsv",
    "pin_b_fall_threshold_test.tsv",
    "pin_ab_fall_threshold_test.tsv"
);


my @graphs = (
    "plotvoltage.gnuplot",
    "plotcurrent.gnuplot",
    "plotpower.gnuplot"
);


my $filepath = "./" . $cmdlinechipname . "/data/";
my $graphpath = "./" . $cmdlinechipname . "/graphs/";

mkdir( "./" . $cmdlinechipname . "/graphs");

foreach my $file ( @files ) {
    foreach my $graph ( @graphs ) {
        print( "Writing: " . "./graphs/" . $file . "_" . $graph . ".png\n" );
        system( 
            "/opt/local/bin/gnuplot" , 
            "-c" , 
            "../gnuplot/" . $graph ,
            $filepath . $file , 
            $graphpath . $file . "_" . $graph . ".png"
            );
    }
}















