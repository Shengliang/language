#[allow(unused)]
fn main() {
    use std::collections::HashMap;

    let mut scores = HashMap::new();

    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);


    for (key, value) in &scores {
        println!("{}: {}", key, value);
    }

    // Only Inserting a Value If the Key Has No Value
    scores.entry(String::from("Yellow")).or_insert(50);
    scores.entry(String::from("Blue")).or_insert(60);
    scores.entry(String::from("Red")).or_insert(70);

    println!("{:?}", scores);


    let team_name = String::from("Blue");
    let score = scores.get(&team_name);
    match score {
        Some(val) => println!("key:{} val: {}", team_name, val),
        _ => println!("key:{} val:unknown.", team_name),
    }
    let team_name = String::from("White");
    let score = scores.get(&team_name);
    match score {
        Some(val) => println!("key:{} val: {}", team_name, val),
        _ => println!("key:{} val:unknown.", team_name),
    }

    let teams = vec![String::from("Blue"), String::from("Yellow")];
    let initial_scores = vec![10, 50];
    let mut scores: HashMap<_, _> =
        teams.into_iter().zip(initial_scores.into_iter()).collect();


    let field_name = String::from("Favorite color");
    let field_value = String::from("Blue");

    let mut map = HashMap::new();
    map.insert(field_name, field_value);
    // field_name and field_value are invalid at this point, try using them and
    // see what compiler error you get!

    freq_map();
}



fn freq_map() {
    use std::collections::HashMap;

    let text = "hello world wonderful world";

    let mut map = HashMap::new();

    for word in text.split_whitespace() {
        let count = map.entry(word).or_insert(0);
        *count += 1;
    }

    println!("{:?}", map);
}

