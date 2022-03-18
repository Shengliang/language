fn main() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(s);             // s's value moves into the function...
                                    // ... and so is no longer valid here

    let x = 5;                      // x comes into scope

    makes_copy(x);                  // x would move into the function,
                                    // but i32 is Copy, so it's okay to still
                                    // use x afterward
    println!("x is {}", x);

    let v = vec![1,2,3];
    let v_ref = &v;  // v_ref borrows v
    let s = sum_ref(v_ref);
    println!("sum of {:?} : {}", v_ref, s); // no error

    print!("sum of {:?} ",  v);
    let s = sum(v);
    // v was MOVED!
    println!(": {}",  s);


} // Here, x goes out of scope, then s. But because s's value was moved, nothing
  // special happens.

fn takes_ownership(some_string: String) { // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) { // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.



fn sum(vector: Vec<i32>) -> i32 {
    let mut sum = 0;

    for item in vector {
        sum = sum + item
    }

    sum
}

fn sum_ref(vector: &Vec<i32>) -> i32 { // borrow signature
    let mut sum = 0;

    for item in vector {
        sum = sum + item
    }

    sum
}
