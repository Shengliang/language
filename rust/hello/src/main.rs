extern crate lazy_static;

use bitvec::prelude::*;
use lazy_static::lazy_static;
use std::collections::HashMap;
use core::{cell::Cell, mem};
use radium::types::*;

lazy_static! {
    static ref HASHMAP: HashMap<u32, &'static str> = {
        let mut m = HashMap::new();
        m.insert(0, "foo");
        m.insert(1, "bar");
        m.insert(2, "baz");
        m
    };
    static ref COUNT: usize = HASHMAP.len();
    static ref NUMBER: u32 = times_two(21);
}

fn times_two(n: u32) -> u32 { n * 2 }

fn test_bits() {
   let mut bv = bitvec![u8, Msb0;];
   bv.push(false);
   bv.push(true);
   bv.extend([false; 4].iter());
   bv.extend(&15u8.view_bits::<Lsb0>()[.. 4]);
   assert_eq!(bv.as_raw_slice(), &[ 0b01_0000_11, 0b1100_0000 ]);
   assert_eq!(bv.as_raw_slice(), &[ 0b01_0000_11, 0b11_000000 ]);
   println!("{:#?}", bv);
}

fn test2() {
// All data-types have macro
// constructors.
let _arr = bitarr![u32, Lsb0; 0; 80];
let _bits = bits![u16, Msb0; 0; 40];

println!("{:#?}  {:#?}", _arr, _bits);
// Unsigned integers (scalar, array,
// and slice) can be borrowed.
let data = 0x2021u16;
let _bits = data.view_bits::<Msb0>();
println!("{:#?}  {:#?}", data, _bits);
let data = [0xA5u8, 0x3C];
let _bits = data.view_bits::<Lsb0>();
println!("{:#?}  {:#?}", data, _bits);

// Bit-slices can split anywhere.
let (head, rest) = _bits.split_at(4);
assert_eq!(head, _bits[.. 4]);
assert_eq!(rest, _bits[4 ..]);
println!("{:#?}  {:#?}", head, rest);

// And they are writable!
let mut data = [0u8; 2];
let _bits = data.view_bits_mut::<Lsb0>();
// l and r each own one byte.
println!("{:#?}", _bits);
let (l, r) = _bits.split_at_mut(8);
println!(" split at 8: {:#?} {:#?}", l, r);

// but now a, b, c, and d own a nibble!
let ((a, b), (c, d)) = (
  l.split_at_mut(4),
  r.split_at_mut(4),
);

// and all four of them are writable.
a.set(0, true);
b.set(1, true);
c.set(2, true);
d.set(3, true);

println!("{:#?} {:#?} {:#?} {:#?}", a, b, c, d);
assert!(_bits[0]);  // a[0]
assert!(_bits[5]);  // b[1]
assert!(_bits[10]); // c[2]
assert!(_bits[15]); // d[3]

// `BitSlice` is accessed by reference,
// which means it respects NLL styles.
assert_eq!(data, [0x21u8, 0x84]);

// Furthermore, bit-slices can store
// ordinary integers:
let eight = [0u8, 4, 8, 12, 16, 20, 24, 28];
//           a    b  c  d   e   f   g   h
let mut five = [0u8; 5];
for (slot, byte) in five
  .view_bits_mut::<Msb0>()
  .chunks_mut(5)
  .zip(eight.iter().copied())
{
  slot.store_be(byte);
  assert_eq!(slot.load_be::<u8>(), byte);
}

println!("{:#?}", five);

assert_eq!(five, [
  0b00000_001,
//  aaaaa bbb
  0b00_01000_0,
//  bb ccccc d
  0b1100_1000,
//  dddd eeee
  0b0_10100_11,
//  e fffff gg
  0b000_11100,
//  ggg hhhhh
]);
}

#[allow(unused_variables)]
fn test3() {

let a: BitArray = bitarr![0, 1, 0, 0, 1];
println!("a {:#?}", a);

let b: BitArray = bitarr![1; 5];
assert_eq!(b.len(), mem::size_of::<usize>() * 8);
println!("b {:#?}", b);

let c = bitarr![u16, Lsb0; 0, 1, 0, 0, 1];
println!("c {:#?}", c);
let d = bitarr![Cell<u16>, Msb0; 1; 10];
println!("d {:#?}", d);
const E: BitArray<[u32; 1], LocalBits> = bitarr![u32, LocalBits; 1; 15];
println!("E {:#?}", E);
let f = bitarr![RadiumU32, Msb0; 1; 20];
println!("f {:#?}", f);
}

#[allow(unused_variables)]
fn test4() {

let a: &BitSlice = bits![0, 1, 0, 0, 1];
println!("a {:#?}", a);

let b: &BitSlice = bits![1; 5];
println!("b {:#?}", b);
assert_eq!(b.len(), 5);

let c = bits![u16, Lsb0; 0, 1, 0, 0, 1];
println!("c {:#?}", c);
let d = bits![static Cell<u16>, Msb0; 1; 10];
println!("d {:#?}", d);
let e = bits![static mut u32, LocalBits; 0; 15];
println!("e {:#?}", e);
let f = bits![RadiumU32, Msb0; 1; 20];
println!("f {:#?}", f);
}

#[allow(unused_variables)]
fn test5() {
   let a: BitArray = bitarr![1; 8];
   println!("a {:#?} {}", a, a.len());
   let a: BitArray = bitarr![1; 16];
   println!("a {:#?} {}", a, a.len());
   let a: BitArray = bitarr![1; 32];
   println!("a {:#?} {}", a, a.len());
   let a: BitArray = bitarr![1; 64];
   println!("a {:#?} {}", a, a.len());
   let a: BitArray = bitarr![2; 64];
   println!("a {:#?} {}", a, a.len());
   let b: &BitSlice = bits![1; 128];
   println!("b {:#?} {}", b, b.len());
}

fn test_prime() {
let max_prime = 10000;
let bv = bits![mut 1; 10000];

    // Assume all numbers are prime to begin, and then we
    // cross off non-primes progressively

    // Neither 0 nor 1 are prime
    let mut b = bv.get_mut(0).unwrap();
    *b = false;
    drop(b);
    let mut b = bv.get_mut(1).unwrap();
    *b = false;
    drop(b);

    for i in 2.. 1 + (max_prime as f64).sqrt() as usize {
        // if i is a prime
        if bv[i] {
            // Mark all multiples of i as non-prime (any multiples below i * i
            // will have been marked as non-prime previously)
            for j in i.. {
                if i * j >= max_prime {
                    break;
                }
                let mut b = bv.get_mut(i*j).unwrap();
                *b = false;
                drop(b);
            }
        }
    }

// Simple primality tests below our max bound
let print_primes = 20;
print!("The primes below {} are: ", print_primes);
for x in 0..print_primes {
    if bv[x] == true {
        print!("{} ", x);
    }
}
println!("");

let num_primes = bv.iter().filter(|x| **x).count();
println!("There are {} primes below {}", num_primes, max_prime);
assert_eq!(num_primes, 1_229);

}

fn main() {
    println!("The map has {} entries.", *COUNT);
    println!("The entry for `0` is \"{}\".", HASHMAP.get(&0).unwrap());
    println!("The entry for `1` is \"{}\".", HASHMAP.get(&1).unwrap());
    println!("A expensive calculation on a static results in: {}.", *NUMBER);

    test_bits();
    test2();
    test3();
    test4();
    test5();
    test_prime();
}
