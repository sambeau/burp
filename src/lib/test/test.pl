#!/usr/bin/perl

use strict;

my $tests_tested = 0;
my $tests_passed = 0;
my $tests_failed = 0;

for my $f (split "\n",`ls -1 test/bin`) {

    next if $f eq 'trace.log';

    my $result = `test/bin/$f test/in/$f`;
    $tests_tested++;

    my $expected_result = `cat test/out/$f`;
    my $spaces = ' ' x (12 - length($f));
    print '-' x 40; print "\n";
    print ".. $f:$spaces.. ";

    if ($result eq $expected_result) {

        print "PASS";
        $tests_passed++;

    } else {

        print "FAIL\t\tX\n\n   Errors:\n";
        $tests_failed++;
	my @rs = split "\n", $result;
	my @xs = split "\n", $expected_result;
	for my $r (@rs) {

	    my $x = shift @xs;

	    if ($x ne $r) {

		print "\n   ---" . $f . ('-' x (34 - length($f)));
		print "\n        ";
		my $n = 0;
		my @xx = split //, $x;
		my @rr = split //, $r;

		while($xx[$n] eq $rr[$n] and $xx[$n] ne "\n"){
		    print " ";
		    $n++;
		}

		print "v\n";
		print "   [old:$x\n";
		print "   [new:$r\n";
		print('        ');if($n>0){while($n--){print ' '}; }print("^");

	    }
	}
    }

    print "\n";
}

print '=' x 40; print "\n";
print "Tests: $tests_tested, Passed: $tests_passed, Failed: $tests_failed\n";
print '=' x 40; print "\n";
