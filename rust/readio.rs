//https://doc.rust-lang.org/book/ch09-02-recoverable-errors-with-result.html

#![allow(unused)]
use std::env;
use std::fs;
use std::fs::File;
use std::io;
use std::io::Read;

fn read_file1(filename: &String) -> Result<String, io::Error> {
    let mut s = String::new();
    File::open(filename)?.read_to_string(&mut s)?;
    Ok(s)
}

fn read_file2(filename: &String) -> Result<String, io::Error> {
    fs::read_to_string(filename)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut filename = String::new();
    if args.len() > 1 {
      filename.push_str(&args[1]);
    } else {
      filename.push_str(&String::from("hello.txt"));
    }
    println!("{:?}", filename);

    let  name1 = read_file1(&filename);
    let  name2 = read_file2(&filename);

    println!("{:?}", name1);
    println!("{:?}", name2);
}

