#!/usr/bin/perl

use strict;

package csv_parser;

# hash: %h = ()
# ref to hash: $ref_hash = {}

# arr: @arr = ()
# ref to arr: $arr = []

sub new {
        my $type = shift;  # class name
        my $file = shift;  # csv filename
        my $self = { }; # reference to a hash obj
        $self->{debug} = 0;
        $self->{file}  = $file;
        $self->{rows} = [];
        return bless $self, $type;
};



sub read {
        my $self = shift; # same as C++ this pointer.
        my $file = $self->{file};
        open (FH, $file) or die "Can not open $file\n";
        my @arr = <FH>;
        foreach my $line (@arr) {
                chop($line);
                my $cols = [split(/,/, $line)];
                my $rows =  $self->{rows};
                push @$rows, $cols;
        }
        close(FH);
}

sub print_html {
        my $self = shift;
        my $rows = $self->{rows};
        print "<table>";
        foreach my $row (@$rows) {
                print "<tr>\n";
                foreach my $col (@$row) {
                        print "<td> $col</td>\n";
                }
                print "</tr>\n";
        }      
        print "</table>";
}

sub self_test {
   my $file = "input.csv";
   my $p = csv_parser->new($file);
   $p->read();
   $p->print_html();
}

1;

