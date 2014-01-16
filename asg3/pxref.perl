#!/usr/bin/perl
# $Id: pxref.perl,v 1.4 2012-10-31 14:45:07-07 - - $
use strict;
use warnings;
use Getopt::Std;

$0 =~ s|^(.*/)?([^/]+)/*$|$2|;
my $exit_status = 0;
END {exit $exit_status}
sub note (@) {print STDERR "$0: @_"}
$SIG{'__WARN__'} = sub {note @_; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my $word_regex = qr(\w+([-'.:/]\w+)*);
my %opts;
getopts ("cdf", \%opts);
warn "-d option not supported in perl version\n" if $opts{'d'};

for my $filename (@ARGV ? @ARGV : "-") {
   my %xref;
   open my $file, "<$filename" or do warn "$filename: $!\n" and next;
   my $sep = "\n" . ":" x 65 . "\n";
   print "$sep$filename$sep\n";
   while (defined (my $line = <$file>)) {
      push @{$xref{$opts{'f'} ? lc $& : $&}}, $.
           while $line =~ s|$word_regex||;
   }
   close $file;
   for my $word (sort keys %xref) {
      my $list = $xref{$word};
      printf "%s [%d]", $word, @$list + 0;
      print " @$list" unless $opts{'c'};
      print "\n";
   }
}

