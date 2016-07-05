use feature ':5.10';

package A;
sub new {
    return bless {}, shift;
}
sub speak {
    my $self = shift;
    say 'A';
}
package B;
use parent -norequire, 'A';
sub speak {
    my $self = shift;
    $self->SUPER::speak();
    say 'B';
}
package C;
use parent -norequire, 'B';
sub speak {
    my $self = shift;
    $self->SUPER::speak();
    say 'C';
}
my $c = C->new();
$c->speak();
