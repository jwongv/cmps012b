#!/usr/local/bin/perl -w
# $Id: pkeyvalue.perl,v 1.3 2012-10-24 12:43:21-07 - - $
#
# A reference implementation of the keyvalue program.
#
use strict;
use warnings;
use Getopt::Std;

$0 =~ s|/*$||;
$0 =~ s|^.*/||;
my $STATUS = 0;
END {exit $STATUS; }
sub note(@) {print STDERR "$0: @_"; }
$SIG{'__WARN__'} = sub {note @_; $STATUS = 1; };
$SIG{'__DIE__'} = sub {warn @_; exit; };

my %hash;
getopts "al", \%hash;

sub trim($) {
   my ($str) = @_;
   $str =~ s/^\s*(.*?)\s*$/$1/;
   return $str;
}

sub printkeyvalue($) {
   my ($key) = @_;
   my $value = $hash{$key};
   print $key, defined $value ? "=$value" : ": not found", "\n";
}

push @ARGV, "-" unless @ARGV;
for my $filename (@ARGV) {
   open FILE, "<$filename" or warn "$filename: $!\n" and next;
   while (defined (my $line = <FILE>)) {
      print "$filename:$.:$line";
      next if $line =~ m/^\s*(#|$)/;
      my ($key, $value) = split m/=/, $line, 2;
      $key = trim $key;
      $value = trim $value if defined $value;;
      if (! defined $value) {
         printkeyvalue $key;
      }elsif ($key eq "") {
         for my $hkey (sort keys %hash) {
            printkeyvalue $hkey
                  if $value eq "" or $value eq $hash{$hkey};
         }
      }else {
         printkeyvalue $key if $hash{$key};
         if ($value eq "") {delete $hash{$key}; }
                      else {$hash{$key} = $value; }
      }
   }
   close FILE;
}

