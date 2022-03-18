
/*
Length	Signed	Unsigned
8-bit	i8	u8
16-bit	i16	u16
32-bit	i32	u32
64-bit	i64	u64
128-bit	i128	u128
arch	isize	usize

Number literals	Example
Decimal	98_222
Hex	0xff
Octal	0o77
Binary	0b1111_0000
Byte (u8 only)	b'A'
*/

use std::any::{Any, TypeId};

fn typeid<T: std::any::Any>(_: &T) {
    println!("{:?}", TypeId::of::<T>());
}

fn is_string<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<String>() == TypeId::of::<T>()
}
fn is_i32<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<i32>() == TypeId::of::<T>()
}
fn is_f64<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<f64>() == TypeId::of::<T>()
}
fn is_u8<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<u8>() == TypeId::of::<T>()
}
fn is_u16<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<u16>() == TypeId::of::<T>()
}
fn is_u32<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<u32>() == TypeId::of::<T>()
}
fn is_u64<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<u64>() == TypeId::of::<T>()
}
fn is_u128<T: ?Sized + Any>(_s: &T) -> bool {
    TypeId::of::<u128>() == TypeId::of::<T>()
}

fn main() {
    let n : u8 = 1;
    assert_eq!(is_u8(&n), true);
    let n : u16 = 1;
    assert_eq!(is_u16(&n), true);
    let n : u32 = 1;
    assert_eq!(is_u32(&n), true);
    let n : u64 = 1;
    assert_eq!(is_u64(&n), true);
    let n : u128 = 1;
    assert_eq!(is_u128(&n), true);

    assert_eq!(is_string(&0), false);
    assert_eq!(is_string(&"cookie monster"), false);
    assert_eq!(is_string(&"cookie monster".to_string()), true);

    let c = 'z';
    typeid(&c);
    let z = 'ℤ';
    typeid(&z);
    let heart_eyed_cat = '😻';
    typeid(&heart_eyed_cat);

    let tup: (i32, f64, u8) = (500, 6.4, 1);
    let tup2 = (500, 6.4, 1);
    let (x, y, z) = tup2;
    typeid(&x);
    typeid(&y);
    typeid(&z);
    assert_eq!(is_i32(&x), true);
    assert_eq!(is_f64(&y), true);
    assert_eq!(is_i32(&z), true);
    assert_eq!(is_u8(&tup.2), true);
    println!("The value of y is:{} {}", y, tup.1);
}

