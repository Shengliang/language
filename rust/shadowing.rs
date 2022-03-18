
const PRIME_NUM: u32 = 7;

fn main() {
    let x = PRIME_NUM;

    let x = x + 1;

    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {}", x);
    }

    println!("The value of x is: {}", x);
}

