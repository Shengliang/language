
fn first_word_end(s: &String) -> usize {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }

    s.len()
}

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}


#[allow(unused)]
fn main() {

   let s = String::from("hello world");
   let slice1 = &s[0..5];
   let slice2 = &s[..5];
   let slice3 = &s[6..];
   println!("'{}' '{}' '{}'", slice1, slice2, slice3);

   let mut s = String::from("hello world");
   let c = first_word_end(&s); // word will get the value 5
   s += "!";
   //s.clear();
   println!("{} first word:{}", s,c); 

   let w1 = first_word(&s);
   println!("first word:{}", w1);

}

