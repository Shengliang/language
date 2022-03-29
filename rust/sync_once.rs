
use std::sync::Once;
use std::thread;



fn init() {
    println!("init...");
}

fn test_ok() {

static INIT: Once = Once::new();
assert_eq!(INIT.is_completed(), false);
let handle = thread::spawn(|| {
    assert_eq!(INIT.is_completed(), false);
    INIT.call_once(|| {
        assert_eq!(INIT.is_completed(), false);
        init();
        assert_eq!(INIT.is_completed(), false);
    });
    assert_eq!(INIT.is_completed(), true);
});

println!("test main INIT state:{}", INIT.is_completed());
assert_eq!(INIT.is_completed(), false);
assert_eq!(handle.join().is_err(), false);
println!("test main INIT state:{}", INIT.is_completed());
assert_eq!(INIT.is_completed(), true);

}

fn test_panic() {

static INIT: Once = Once::new();
assert_eq!(INIT.is_completed(), false);
let handle = thread::spawn(|| {
    assert_eq!(INIT.is_completed(), false);
    INIT.call_once(|| {
        assert_eq!(INIT.is_completed(), false);
        println!("panic here.");
        panic!();
    });
    assert_eq!(INIT.is_completed(), false);
});

println!("test main INIT state:{}", INIT.is_completed());
assert_eq!(INIT.is_completed(), false);
assert_eq!(handle.join().is_err(), true);
println!("test main INIT state:{}", INIT.is_completed());
assert_eq!(INIT.is_completed(), false);

}

fn main() {
    println!("\n1. test ok");
    test_ok();
    println!("\n2. test panic");
    test_panic();
}
