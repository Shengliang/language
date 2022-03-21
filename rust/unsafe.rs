use std::ptr;

// 24 bytes
struct Point {
    x: f64,
    y: f64,
    z: f64,
}
struct Rectangle {
    top_left: Point,
    bottom_right: Point,
}

fn origin() -> Point {
    Point { x: 0.0, y: 0.0, z:0.0}
}

fn print(p : &Point) {
    println!("{} {} {}", p.x, p.y, p.z); 
}
fn print_rec(rec : &Rectangle) {
   print(&rec.top_left); 
   print(&rec.bottom_right); 
}
fn main() {

   // Create some data, a raw pointer pointing to it and a null pointer
   let data: u32 = 42;
   let raw_ptr = &data as *const u32;
   let null_ptr = ptr::null() as *const u32;

   // the {:p} mapping shows pointer values as hexadecimal memory addresses
   println!("Data address: {:p}", &data);
   println!("Raw pointer address: {:p}", raw_ptr);
   println!("Null pointer address: {:p}", null_ptr);

   // Let's take a mutable piece of data, a 4-byte integer in this case
   let mut some_data: u32 = 14;
   // Create a mutable raw pointer pointing to the data above
   let data_ptr: *mut u32 = &mut some_data as *mut u32;
   // Note: creating a raw pointer is totally safe but dereferencing a raw pointer requires an
   // unsafe block
   unsafe {
       *data_ptr = 20;
       println!("Dereferenced data: {}", some_data);
   }

    let raw_p: *const u32 = &10;
    unsafe {
        println!("*{:p} = {}", raw_p, *raw_p);
        assert!(*raw_p == 10);
    }

    let mut num = 5;

    let p1 = &num as *const i32;
    let p2 = &mut num as *mut i32;

    unsafe {
        println!("*p1:{:p} is: {}", p1, *p1);
	    *p2 = 6;
        println!("*p2:{:p} is: {}", p2, *p2);
        println!("*p1:{:p} is: {}", p1, *p1);
    }

    // Stack allocated variables
    let rectangle: Rectangle = Rectangle {
        top_left: origin(),
        bottom_right: Point { x: 3.0, y: -4.0, z: 0.1 }
    };
    let raw_p1: *const Rectangle = &rectangle;

    // Heap allocated rectangle
    let boxed_rectangle: Box<Rectangle> = Box::new(Rectangle {
        top_left: origin(),
        bottom_right: Point { x: 3.0, y: -4.0, z: 0.2 },
    });
    let raw_p2: *const Box<Rectangle> = &boxed_rectangle;
    let unboxed_rec: Rectangle = *boxed_rectangle;
    let raw_p3: *const Rectangle = &unboxed_rec;

    unsafe {
        println!("*{:p}:", raw_p1);print_rec(&*raw_p1);
        println!("*{:p}:", raw_p3);print_rec(&*raw_p3);
        println!("*{:p}:", raw_p2);print_rec(&(*(*raw_p2)));
    }
}

