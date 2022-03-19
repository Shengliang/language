#[allow(unused)]
fn main() {
    let hello = String::from("السلام عليكم");
    let hello = String::from("Dobrý den");
    let hello = String::from("Hello");
    let hello = String::from("שָׁלוֹם");
    let hello = String::from("नमस्ते");
    let hello = String::from("こんにちは");
    let hello = String::from("안녕하세요");
    let hello = String::from("Olá");
    let hello = String::from("Здравствуйте");
    let hello = String::from("Hola");
    let hello = String::from("你好");

    for c in hello.chars() {
      print!("{} ", c);
    }
    println!();

    // For Chinese characters, UTF-8 only uses 6 bits of each byte to store the data.
    for b in hello.bytes() {
       print!("{} ", b);
    }
    println!();

}

