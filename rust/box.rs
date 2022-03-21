// https://doc.rust-lang.org/stable/rust-by-example/std/box.html
// default = stack
// box = heap
//
use std::mem;

#[allow(dead_code)]
#[derive(Debug, Clone, Copy)]
// 24 bytes
struct Point {
    x: f64,
    y: f64,
    z: f64,
}

// A Rectangle can be specified by where its top left and bottom right
// corners are in space
#[allow(dead_code)]
// 48 bytes: 24*2
struct Rectangle {
    top_left: Point,
    bottom_right: Point,
}

fn origin() -> Point {
    Point { x: 0.0, y: 0.0, z:0.0}
}

fn boxed_origin() -> Box<Point> {
    // Allocate this point on the heap, and return a pointer to it
    Box::new(Point { x: 0.0, y: 0.0, z: 0.0 })
}

fn main() {
    // (all the type annotations are superfluous)
    // Stack allocated variables
    let point: Point = origin();
    let rectangle: Rectangle = Rectangle {
        top_left: origin(),
        bottom_right: Point { x: 3.0, y: -4.0, z: 0.0 }
    };
    let raw_p1: *const Rectangle = &rectangle;

    // Heap allocated rectangle
    let boxed_rectangle: Box<Rectangle> = Box::new(Rectangle {
        top_left: origin(),
        bottom_right: Point { x: 3.0, y: -4.0, z: 0.0 },
    });
    let raw_p2: *const Box<Rectangle> = &boxed_rectangle;
    let raw_p3: *const Rectangle = &(*boxed_rectangle);

    // The output of functions can be boxed
    let boxed_point: Box<Point> = Box::new(origin());

    // Double indirection
    let box_in_a_box: Box<Box<Point>> = Box::new(boxed_origin());

    println!("Point occupies {} bytes on the stack",
             mem::size_of_val(&point));
    println!("Rectangle occupies {} bytes on the stack",
             mem::size_of_val(&rectangle));

    // box size == pointer size
    println!("Boxed point occupies {} bytes on the stack",
             mem::size_of_val(&boxed_point));
    println!("Boxed rectangle occupies {} bytes on the stack",
             mem::size_of_val(&boxed_rectangle));

    println!("stack addres {:p}", raw_p1);
    println!("stack address {:p}", raw_p2);
    println!("heap address {:p}", raw_p3);

    println!("Boxed box occupies {} bytes on the stack",
             mem::size_of_val(&box_in_a_box));

    // Copy the data contained in `boxed_point` into `unboxed_point`
    let unboxed_point: Point = *boxed_point;
    println!("Unboxed point occupies {} bytes on the stack",
             mem::size_of_val(&unboxed_point));
}

