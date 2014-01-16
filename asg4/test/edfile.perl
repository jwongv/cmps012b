#!/usr/local/bin/perl -w
my $RCSID = '$Id: edfile.perl,v 1.1 2008-02-15 13:06:04-08 - - $';
use strict;
use warnings;
#
# See the listedit utility man page for specifications.
#

$0 =~ s|^(.*/)?([^/]+)/*$|$2|;
my $exit_status = 0;
END { exit $exit_status; }
sub note(@) { print STDERR "@_"; };
$SIG{'__WARN__'} = sub { note @_; $exit_status = 1; };
$SIG{'__DIE__'} = sub { warn @_; exit; };

select STDOUT; $| = 1;
select STDERR; $| = 1;

my %Options;
my @Linelist = ();
my $Dotline = $#Linelist;

sub readfile ($) {
   my ($filename) = @_;
   if (open my $file, "<$filename") {
      my @readlines = <$file>;
      close $file;
      splice @Linelist, $Dotline + 1, 0, @readlines;
      $Dotline += @readlines;
      note sprintf "$0: %d lines read from %s\n",
                   scalar @readlines, $filename;
   }else {
      warn "$0: $filename: $!";
   }
}

sub writefile ($) {
   my ($filename) = @_;
   $filename = $ARGV[0] unless $filename =~ m/./;
   if (open my $file, ">$filename") {
      print $file @Linelist;
      close $file;
      $Dotline = $#Linelist;
      note sprintf "$0: %d lines written to %s\n",
                   scalar @Linelist, $filename;
   }else {
      warn "$0: $filename: $!";
   }
}

sub printcurr () {
   $Dotline = 0 if $Dotline < 0;
   $Dotline = $#Linelist if $Dotline > $#Linelist;
   if ($Dotline >= 0) {
      printf "%6d: %s", $Dotline, $Linelist[$Dotline];
   }else {
      warn "$0: no lines in file";
   }
}


my %Commandswitch = (
#  key => [hasoperand, printcurr, sub].
   '#' => [1, 0, sub {}],
   '$' => [0, 1, sub {$Dotline = $#Linelist}],
   '*' => [0, 0, sub {$Dotline = $_, printcurr for 0..$#Linelist}],
   '.' => [0, 1, sub {}],
   '0' => [0, 1, sub {$Dotline = 0}],
   '<' => [0, 1, sub {--$Dotline}],
   '>' => [0, 1, sub {++$Dotline}],
   'a' => [1, 1, sub {splice @Linelist, ++$Dotline, 0, "$_[0]\n"}],
   'd' => [0, 1, sub {splice @Linelist, $Dotline, 1 if @Linelist}],
   'i' => [1, 1, sub {$Dotline = 0 if $Dotline < 0;
                      splice @Linelist, $Dotline, 0, "$_[0]\n"}],
   'r' => [1, 0, sub {readfile $_[0]}],
   'w' => [1, 0, sub {writefile $_[0]}],
);

unless (@ARGV == 1) {
   print STDERR "Usage: $0 filename\n";
   $exit_status = 1;
   exit;
}
my $bothttys = -t STDIN and -t STDOUT;
readfile $ARGV[0];
for (;;) {
   print "$0: ";
   last unless defined (my $command = <STDIN>);
   print $command unless $bothttys;
   chomp $command;
   next if $command =~ m/^\s*$/;
   my ($key, $operand) = $command =~ m/(.)(.*)/;
   my $sub = $Commandswitch{$key};
   if (defined ($sub) and ($sub->[0] or length ($operand) == 0)) {
      $sub->[2] ($operand);
      printcurr if $sub->[1];
   }else {
      warn "$0: $command: invalid command\n";
   }
}
print "^D\n";

