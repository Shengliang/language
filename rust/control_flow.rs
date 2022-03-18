fn main() {
    let number = 6;

    if number % 4 == 0 {
        println!("number is divisible by 4");
    } else if number % 3 == 0 {
        println!("number is divisible by 3");
    } else if number % 2 == 0 {
        println!("number is divisible by 2");
    } else {
        println!("number is not divisible by 4, 3, or 2");
    }

    let eo = if number % 2 == 0 { "even" } else { "odd" };
    println!("The value of number is: {} {}", number, eo);
    lcount(5);
    wcount(5);
    parr();
    p1to4();
}


fn lcount(n : u32) {
    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == n {
            break counter * 2;
        }
    };
    println!("The result is {}", result);
}

fn wcount(n : u32) {
    let mut number = n;

    while number != 0 {
        println!("{}!", number);

        number -= 1;
    }

    println!("LIFTOFF!!!");
}

fn parr() {
    let a = [10, 20, 30, 40, 50];

    for element in a {
        println!("the value is: {}", element);
    }

    let mut index = 0;
    while index < a.len() {
        println!("the value is: {}", a[index]);

        index += 1;
    }
}

fn p1to4() {
    for number in (1..4).rev() {
        println!("{}!", number);
    }
    println!("LIFTOFF!!!");
}


