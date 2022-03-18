fn main() {
    print_labeled_measurement(5, 'h');
}

fn print_labeled_measurement(value: i32, unit_label: char) {
    println!("The measurement is: {}{}", value, unit_label);

    let y = {
        let x = 3;
        x*x + 1 
    };

    println!("The value of y is: {}", y);
}

