fn my_push_back<'a>(v: &mut Vec<&'a str>, s: &'a str) {
    v.push(s);
}

fn main() {
    let mut my_vector: Vec<&str> = Vec::new();
    let my_string = "hello world".to_string();
    my_push_back(&mut my_vector, &my_string);
    println!("{:p} {:p}", &my_string, &my_vector[0]);
    dbg!(my_vector);
}
