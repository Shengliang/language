// Rust provides two main pointer types: the owned pointer (indicated by the tilde: ~ ) and the borrowed reference (denoted with ampersand: & ). 
//
use std::ptr;

#[repr(packed)]
struct Packed816 {
    f1: u8,
    f2: u16,
}
#[repr(packed)]
struct Packed168 {
    f2: u16,
    f1: u8,
}
fn increment(ptr : &mut i32) {
    *ptr = *ptr + 1;
}
fn main() {
    let ptr = &mut 10;
    println!("{:#?} {:#?}", ptr, *ptr);
    let p1 = ptr.clone();
    println!("{:#?} {:#?} {:#?}", ptr, *ptr, p1);
    *ptr += 1;
    println!("{:#?} {:#?} {:#?}", ptr, *ptr, p1);

    let mut x = 110;
    increment(&mut x);
    println!("{:#?}", x);

    let pa = Packed816 { f1: 1, f2: 2};
    let pb = Packed168 { f1: 1, f2: 2};
    let raw_a = ptr::addr_of!(pa);
    let raw_f1a = ptr::addr_of!(pa.f1);
    let raw_f2a = ptr::addr_of!(pa.f2);
    let raw_b = ptr::addr_of!(pb);
    let raw_f1b = ptr::addr_of!(pb.f1);
    let raw_f2b = ptr::addr_of!(pb.f2);

    println!("{:#?} {:#?} {:#?}\n{:#?} {:#?} {:#?}\n",
             raw_a, raw_f1a, raw_f2a,
             raw_b, raw_f2b, raw_f1b);
}
/*
(gdb) info local
x = 110
p1 = 10
ptr = 0x7fffffffced4
(gdb) p ptr
$8 = (*mut i32) 0x7fffffffced4
(gdb) p *ptr
$9 = 11
(gdb) p p1
$10 = 10
(gdb) p &p1
$11 = (*mut i32) 0x7fffffffcf2c
(gdb) p *ptr
$13 = 11
(gdb) p p1
$14 = 10
(gdb) p x
$1 = 111
(gdb) p &x
$2 = (*mut i32) 0x7fffffffcff4
(gdb) info local
x = 111
p1 = 10
ptr = 0x7fffffffced4
*/
