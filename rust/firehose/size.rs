use std::rc::Rc;
use std::cell::RefCell;
use std::sync::Arc;
use std::mem::{align_of, size_of};

// 8 * 5 = 40 bytes
#[allow(unused)]
#[derive(Debug)]
struct Data {
    // ptr, size, capacity
    nums: Vec<usize>,
    dimension: (usize, usize),
}

impl Data {
  #[inline]
  pub fn new(n : usize) -> Self {
    Data {
      nums : vec![0;n],
      dimension: (n, 8),
    }
  }
}

// 32 bytes
#[allow(unused)]
#[derive(Debug)]
enum DataS {
    Empty,
    Number(i32),
    Array(Vec<i32>),
}
// 16 bytes
#[allow(unused)]
#[derive(Debug)]
enum DataH {
    Empty,
    Number(i32),
    Array(Box<Vec<i32>>),
}

#[allow(unused)]
enum Option<T> {
    None,
    Some(T),
}



fn main() {
      let d40 : Data = Data::new(10);
      let d32 : DataS = DataS::Array(vec![0;3]);
      let d16 : DataH = DataH::Array(Box::new(vec![0;4]));

     println!("Data Size: {} {:#?}", size_of::<Data>(), d40);
     println!("DataS Size: {} {:#?}", size_of::<DataS>(), d32);
     println!("DataH Size: {} {:#?}", size_of::<DataH>(), d16);
     println!("Option<Box<i32>> {}", size_of::<Option<Box<i32>>>());

     let a : (char, u8, i32) = ('a', 7, 354);
     println!("(char, u8, i32) size {}", size_of::<(char, u8, i32)>());
     println!("(char, u8, i32) align:{}", align_of::<(char, u8, i32)>());
     println!("{:?} {:p}", a, &a);

     let a: [i32; 3] = [1,2,3];
     let v: Vec<i32> = vec![1,2,2];
     println!("{:?} {:p}", a, &a);
     println!("{:?} {:p}", v, &v);


     let mut s1 : String = String::from("hello");
     let s2 : String = String::from("world");
     // String has {ptr, len, capacity}
     println!("String size:{}", size_of::<String>());
     println!("{:p} {:X} {}", &s1, s1.as_ptr() as u64, s1);
     println!("{:p} {:X} {}", &s2, s2.as_ptr() as u64, s2);

     let ptr = s1.as_mut_ptr();
     let len = s1.len();
     let capacity = s1.capacity();
     println!("add:{:X} len:{}, capacity:{}", ptr as u64, len, capacity);

     // text area
     let s1 : &'static str = "hello";
     let s2 : &'static str = "world";
     println!("{:p} {}", s1, s1);
     println!("{:p} {}", s2, s2);

     let v: Vec<String> = vec![ "Odin".to_string(),
     "Thor".to_string(),
     "Loki".to_string(), 
     ];
     println!("v {:p}", v.as_ptr());
     let v: Rc<Vec<String>> = Rc::new(vec![ "Odin".to_string(),
     "Thor".to_string(),
     "Loki".to_string(), 
     ]);
     // copy pointer only
     /*
      * stack[v] -> vec.heap[2,  ptr[....],  3, 3]
      * stack[v2] --^
      */
     // 24 bytes
     println!("Vec<String> size:{}", size_of::<Vec<String>>());
     // 32 bytes
     println!("RefCell<Vec<String>> size:{}", size_of::<RefCell<Vec<String>>>());
     // 8 bytes
     println!("Rc<Vec<String>> size:{}", size_of::<Rc<Vec<String>>>());
     // 8 bytes
     println!("Rc<RefCell<Vec<String>>> size:{}", size_of::<Rc<RefCell<Vec<String>>>>());
     // 8 bytes
     println!("Option<Rc<RefCell<Vec<String>>>> size:{}", size_of::<Option<Rc<RefCell<Vec<String>>>>>());
     // 8 bytes
     println!("Arc<Vec<String>> size:{}", size_of::<Arc<Vec<String>>>());
     // 8 bytes
     println!("Arc<RefCell<Vec<String>>> size:{}", size_of::<Arc<RefCell<Vec<String>>>>());
     // 8 bytes
     println!("Option<Arc<RefCell<Vec<String>>>> size:{}", size_of::<Option<Arc<RefCell<Vec<String>>>>>());
     let v2 = v.clone();
     println!("v {:p}", v.as_ptr());
     println!("v2 {:p}", v2.as_ptr());
     println!("{} {}", v.capacity(), v2.capacity());

     println!(" size of function ptr: fn()->bool {}", size_of::<fn()->bool>());
}

