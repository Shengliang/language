
use std::fmt;

enum Suit {
    Heart,
    Diamond,
    Spade,
    Club
}

impl fmt::Display for Suit {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
       match *self {
           Suit::Heart => write!(f, "♥"),
           Suit::Diamond => write!(f, "♦"),
           Suit::Spade => write!(f, "♠"),
           Suit::Club => write!(f, "♣"),
       }
    }
}

fn main() {
    println!("{}", Suit::Heart);
    println!("{}", Suit::Diamond);
    println!("{}", Suit::Spade);
    println!("{}", Suit::Club);
}
