use std::any::{TypeId};

use std::fmt;

enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}

impl fmt::Display for SpreadsheetCell {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
       match *self {
           SpreadsheetCell::Int(_i32) => write!(f, "i32"),
           SpreadsheetCell::Float(_f64) => write!(f, "f64"),
           _ => write!(f, "str"),
       }
    }
}



fn main() {
    let v = vec![1, 2, 3, 4, 5];

    let third: &i32 = &v[2];
    println!("The third element is {}", third);

    match v.get(2) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element."),
    }

    let mut v = vec![100, 32, 57];
    for i in &mut v {
        *i += 50;
    }

    for i in &v {
        println!("{}", i);
    }
    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];

   let k = row.len();
   for i in 0..k {
        typeid(&row[i]);
        println!("{}", row[i]);
    }
}

fn typeid<T: std::any::Any>(_: &T) {
    println!("{:?}", TypeId::of::<T>());
}
