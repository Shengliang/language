
use std::time::{SystemTime};

struct Sheep {}
struct Cow {}

trait Animal {
    // Instance method signature
    fn noise(&self) -> &'static str;
}

// Implement the `Animal` trait for `Sheep`.
impl Animal for Sheep {
    fn noise(&self) -> &'static str {
        "baaaaah!"
    }
}

// Implement the `Animal` trait for `Cow`.
impl Animal for Cow {
    fn noise(&self) -> &'static str {
        "moooooo!"
    }
}

// Returns some struct that implements Animal, but we don't know which one at compile time.
fn random_animal(random_number: f64) -> Box<dyn Animal> {
    if random_number < 0.5 {
        Box::new(Sheep {})
    } else {
        Box::new(Cow {})
    }
}

fn main() {
    let mut random_number = 0.1;
    let now = SystemTime::now();
    match now.duration_since(SystemTime::UNIX_EPOCH) {
      Ok(n) => {println!("{}", n.as_secs()%10); random_number *= (n.as_secs()%10) as f64},
      Err(_) => panic!("SystemTime before UNIX EPOCH!"),
    }
    let animal = random_animal(random_number);
    println!("You've randomly chosen an animal, and it says {}", animal.noise());
}


