
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
    let raw_p: *const u32 = &10;
    unsafe {
        println!("*{:#16x} = {}", raw_p as u64, *raw_p);
        assert!(*raw_p == 10);
    }

    let mut num = 5;

    let p1 = &num as *const i32;
    let p2 = &mut num as *mut i32;

    unsafe {
        println!("*p1:{:#16x} is: {}", p1 as u64, *p1);
	    *p2 = 6;
        println!("*p2:{:#16x} is: {}", p2 as u64, *p2);
        println!("*p1:{:#16x} is: {}", p1 as u64, *p1);
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
        println!("*{:#16x}:", raw_p1 as u64);print_rec(&*raw_p1);
        println!("*{:#16x}:", raw_p3 as u64);print_rec(&*raw_p3);
        println!("*{:#16x}:", raw_p2 as u64);print_rec(&(*(*raw_p2)));
    }
}

