fn create_closure() -> impl Fn() {
    let msg = String::from("hello");
    let v: Vec<i32> = vec![1,2,3];
    move || {
        println!("{}", msg);
        println!("{:?}", v);
    }
}

fn create_fn() -> impl Fn() {
    let text = "Fn".to_owned();

    move || println!("This is a: {}", text)
}

fn create_fnmut() -> impl FnMut() {
    let text = "FnMut".to_owned();

    move || println!("This is a: {}", text)
}

fn create_fnonce() -> impl FnOnce() {
    let text = "FnOnce".to_owned();

    move || println!("This is a: {}", text)
}



fn main() {
    let mut i : i32 = 0;
    let mut f = || { i += 1; };
    f();
    f();
    println!("{}", i);

    let g =  create_closure();
    g();
    g();

    let fn_plain = create_fn();
    let mut fn_mut = create_fnmut();
    let fn_once = create_fnonce();

    fn_plain();
    fn_mut();
    fn_once();
}
