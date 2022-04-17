
use std::mem;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::sync::MutexGuard;
use rayon::prelude::*;
use std::sync::Arc;
use std::fs::File;
use std::thread;

use std::sync::RwLock;
use std::sync::RwLockWriteGuard;


fn vector_of_ints() -> Vec<i32> {
    vec![1,2,3,4]
}

fn test1() {
    fn f(s1: &mut String) {
        let mut s2 = "".to_string();
        mem::swap(s1, &mut s2);
        dbg!(s2);
    }
    
    fn g() {
        let mut s1 = "foo".to_string();
        f(&mut s1);
        dbg!(s1);
    }
    g()
}

fn test2() {
    fn f(s1: &mut Option<String>) {
        let s2 = s1.take().unwrap();
        dbg!(s2);
    }
    
    fn g() {
        let mut s1: Option<String> =
            Some("foo".to_string());
        f(&mut s1);
        dbg!(s1);
    }
    g();
}

fn test3() {
    fn f(v: &mut Vec<String>) {
        let s2 = v.remove(0);
        dbg!(s2);
    }
    
    fn g() {
        let mut v = vec![
            "foo".to_string(),
            "bar".to_string(),
            "baz".to_string(),
        ];
        f(&mut v);
        dbg!(v);
    }
    g();
}

fn test4() {
    // drop is the empty function
    //pub fn drop<T>(_x: T)
    let file = File::open("/dev/null");
    drop(file);
}

fn test5() {
    let my_string: Arc<Mutex<String>> =
    Arc::new(Mutex::new(String::new()));
    let mut thread_handles = Vec::new();
    for _ in 0..10 {
        let arc_clone = my_string.clone();
        let thread_handle = thread::spawn(move || {
            let mut guard: MutexGuard<String> =
                arc_clone.lock().unwrap();
            guard.push_str("some characters");
        });
        thread_handles.push(thread_handle);
    }
    for thread_handle in thread_handles {
        thread_handle.join().unwrap();
    }
}

fn test6() {
   let my_string: Arc<RwLock<String>> =
      Arc::new(RwLock::new(String::new()));
   let mut thread_handles = Vec::new();
   for _ in 0..10 {
       let arc_clone = my_string.clone();
       let thread_handle = thread::spawn(move || {
           let mut guard : RwLockWriteGuard<String> = arc_clone.write().unwrap();
           guard.push_str("some characters");
       });
       thread_handles.push(thread_handle);
   }
   for thread_handle in thread_handles {
       thread_handle.join().unwrap();
   }
}

fn main() {
   let mut v: Vec<i32> = vector_of_ints();
   for x in &mut v {
       *x += 1;
   }
   println!("{:?}", v);
   
   let mut v: Vec<i32> = vector_of_ints();
   v.iter_mut().for_each(|x| {
       *x += 1;
   });
   println!("{:?}", v);
   
   let mut v: Vec<i32> = vector_of_ints();
   v.par_iter_mut().for_each(|x| {
       *x += 1;
   });
   println!("{:?}", v);

   let mut v: Vec<i32> = vector_of_ints();
   let sum: AtomicI32 = AtomicI32::new(0);
   v.par_iter_mut().for_each(|x| {
       *x += 1;
       sum.fetch_add(*x, Ordering::Relaxed);
   });
   println!("{:?} {:?}", v, sum);
   
   let mut v: Vec<i32> = vector_of_ints();
   let sum: Mutex<i32> = Mutex::new(0);
   v.par_iter_mut().for_each(|x| {
       *x += 1;
       let mut guard: MutexGuard<i32> = sum.lock().unwrap();
       *guard += *x;
   });
   println!("{:?} {:?}", v, sum);


   test1();
   test2();
   test3();
   test4();
   test5();
   test6();
}
