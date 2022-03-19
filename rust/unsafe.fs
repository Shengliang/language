
fn main() {
    let mut num = 5;

    let p1 = &num as *const i32;
    let p2 = &mut num as *mut i32;

    unsafe {
        println!("*p1 is: {}", *p1);
	*p2 = 6;
        println!("*p2 is: {}", *p2);
        println!("*p1 is: {}", *p1);
    }
}

