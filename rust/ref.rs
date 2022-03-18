
fn main() {
    let s1 = String::from("hello");

    let len = calculate_length(&s1);

    println!("The length of '{}' is {}.", s1, len);

    let mut s = String::from("hello");

    change(&mut s);
    println!("The length of '{}' is {}.", s, s.len());

    let s = no_dangle();
    println!("The length of '{}' is {}.", s, s.len());
}

fn calculate_length(s: &String) -> usize {
    s.len()
}


fn change(some_string: &mut String) {
    some_string.push_str(", world");
}


fn no_dangle() -> String {
    let s = String::from("hello");

    s
}

