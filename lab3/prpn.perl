#!/usr/bin/perl
# $Id: prpn.perl,v 1.3 2012-01-26 14:53:20-08 - - $

use Scalar::Util qw (looks_like_number);

sub error {print "$.: $word: @_\n"}

sub binop {
   if (@stack >= 2) {
      push @stack, $_[0]->(splice @stack, -2);
   }else {
      error "stack underflow";
   }
}

%switch = (
   "+"=> sub {binop sub {$_[0] + $_[1]}},
   "-"=> sub {binop sub {$_[0] - $_[1]}},
   "*"=> sub {binop sub {$_[0] * $_[1]}},
   "/"=> sub {binop sub {$_[0] * ($_[1] ? 1 / $_[1] : 1e1000000)}},
   ";"=> sub {map {printf "%22.15g\n", $_} @stack},
);

LINE: while (<STDIN>) {
   for $word (split " ") {
      next LINE if $word =~ m/^#/;
      if (looks_like_number $word) {
         @stack < 16 ? push @stack, $word : error "stack overflow"
      }else {
         $sub = $switch{$word};
         $sub ? $sub->($word) : error "invalid operator"
      }
   }
}

