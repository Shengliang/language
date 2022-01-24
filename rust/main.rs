#![allow(dead_code)]
fn print(_numbers: &[i64]) {
    for it in _numbers.iter() {
        print!("{} ", *it);
    }
    println!();
}

fn findmax1(_numbers: &[i64]) -> i64 {
    let maxv = _numbers.iter().fold(std::i64::MIN, |a,b| a.max(*b));
    return maxv;
}

fn findmax2(_numbers: &[i64]) -> i64 {
    let mut maxv:i64 = std::i64::MIN;
    for it in _numbers.iter() {
        if *it > maxv {
            maxv = *it;
        }
    }
    return maxv;
}

fn word_start_with_c(my_str:String)-> String {
    let mut my_updated_string = "".to_string();
    for word in my_str.split(" "){
         if word.starts_with("c"){
             my_updated_string.push_str(word);
             my_updated_string.push(' ');
         }
    }
    my_updated_string.pop();
    my_updated_string
}

fn reverse_vec(my_vec: &mut Vec<u32>) -> &mut Vec<u32> {
   let n = my_vec.len();
   let k = n/2;
   for i in 0..k {
       let j = n - 1 - i;
       let t = my_vec[i];
       my_vec[i] = my_vec[j];
       my_vec[j] = t;
   }
   my_vec
}

fn determine_isogram(_word: &str) -> i32 {
   let mut mp :[i64;256] = [0; 256];
   for x in _word.chars() {
      if x == ' ' {
          continue;
      }
      if x == '-' {
          continue;
      }
      let i = x as usize;
      if mp[i] == 1 {
         return 0;
      }
      mp[i] += 1;
   }
   return 1;
}

fn test(my_vec: &mut Vec<u32>)-> &mut Vec<u32>{
   let middle = (my_vec.len())/2;
   my_vec.pop();
   my_vec.remove(middle - 1);
   let mut sum : u32 = 0;
   for v in my_vec.iter()
   {
      sum = sum + v;
   }
   my_vec.push(sum);
   my_vec
}

struct Point {
	x: i32,
	y: i32
}

fn dist(point1: Point, point2: Point)-> f32 {
    let distance = i32::pow(point1.x - point2.x,2) + i32::pow(point1.y - point2.y,2);
    let d = distance as f32;
    d.sqrt()
}

enum Days {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
}

impl Days{
    // if the day is a weekend
    fn is_weekend(&self)->i32{
      match self{
        &Days::Saturday=> return 1,
        &Days::Sunday  => return 1,
        _ => return 0
      }
    }
}


struct Car {
   owner_age:i32,
}

struct Motorbike {
   owner_age:i32,
}

trait Drive {
   fn can_drive(&self)->i32;
}

//implement the trait
impl Drive for Car{
   fn can_drive(&self)->i32{
      if self.owner_age>=18 {
         1
      }
      else {
         0
      }
   }
}

//implement the trait
impl Drive for Motorbike{
   fn can_drive(&self)->i32{
      if self.owner_age>=14{
         1
      }
      else {
         0
      }
   }
}



fn main() {

    let mut colors: [String; 2] = ["red".to_string(), "blue".to_string()];
    let suffix : String = " color".to_string();
    for value in colors.iter_mut() {
        *value += &suffix;
        println!("{}", value);
    }


  let a = 5;
  let b = 6;
  println!("Operand 1: {}, Operand 2: {}", a , b);
  println!("AND: {}", a & b);
  println!("OR: {}", a | b);
  println!("XOR: {}", a ^ b);
  println!("inverse bits: {}", !a);
  println!("Left shift: {}", a << 2);
  println!("Right shift: {}", a >> 1);

  let words: [&str; 3] = ["bird", "frog", "apple"];
  for w in words  {
    println!("{} isogram:{}" ,  w, determine_isogram(w));
  }

    let mut v1 = vec![1, 5, 7, 9];
    println!("Original Vector: {:?}", v1);
    println!("Updated Vector: {:?}", test(&mut v1));
    reverse_vec(&mut v1);
    println!("reversed vector: {:?}", v1);
    v1.push(17);
    reverse_vec(&mut v1);
    println!("reversed vector: {:?}", v1);

    let arr:[i64;4] = [1, 2, 3, 14];
    println!("Length of array: {}", arr.len());
    println!("{}", findmax1(&arr));
    println!("{}", findmax2(&arr));
    print(&arr);

   let mut c = Car { owner_age:16 };
   println!("Can age = 16 drive a car ? - {}", c.can_drive());
   c.owner_age = 23;
   println!("Can age = 23 drive a car ? - {}", c.can_drive());
   let mut d = Motorbike  { owner_age:10 };
   println!("Can age = 10 drive a motorbike? - {}", d.can_drive());
   d.owner_age = 17;
   println!("Can age = 17 drive a motorbike? - {}", d.can_drive());

    let mut check_day = Days::Saturday;
    println!("Is Saturday a weekend ? : {}", check_day.is_weekend());
    check_day = Days::Monday;
    println!("Is Monday a weekend ? : {}", check_day.is_weekend());

    let point1 = Point { x: 0, y: 0 };
    let point2 = Point { x: 3, y: 4 };
    print!("Distance between two points:");
    println!("{}", dist(point1, point2));

    let my_str = "apple bike cafe car color";
    let c_words = word_start_with_c(my_str.to_string());
    println!("word start with c: {}", c_words);

    {
      let mut arr =[8,7,6,5,4,3,2,1];
      for (i, value) in  arr.iter_mut().enumerate(){
          if (i&1) == 1 {
             println!("{} {}", i, value);
             *value *= -1;
          }
      }
      print(&arr);
    }
}
