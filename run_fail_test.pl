#!/usr/bin/perl

# This script verifies that test whose file name begins with "fail" with the
# expected error.
use strict;
use warnings;

my $cxx = "g++";

my $count = 0;
my $err_count = 0;

foreach my $file (<./test/fail_*>) {
    ++$count;

    my $output = `$cxx -std=c++11 -fsyntax-only $file 2>&1`;

    open(FILE, $file)
        or warn("Error: could not open $file."), ++$err_count, next;
    my $error = <FILE>;
    $error = substr $error, 3, -1;

    $output =~ m/$error/
        or warn("Error: test did not fail: $file"), ++$err_count, next;
}

print "Run $count tests, $err_count failed.\n";

