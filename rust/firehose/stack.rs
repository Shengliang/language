fn main() {
    let mut a : i32 = 22;
    let mut b : i32 = add_one(a);

    println!("&a {:p} {}", &a, a);
    println!("&b {:p} {}", &b, b);
    println!("&b - &a : {}", &b - &a);

    swap(&mut a, &mut b);
    println!("&a {:p} {}", &a, a);
    println!("&b {:p} {}", &b, b);
    swap2(&mut a, &mut b);
    println!("&a {:p} {}", &a, a);
    println!("&b {:p} {}", &b, b);
}

fn add_one(i: i32) -> i32 {
    println!("add_one code at {:X}", add_one as u64);
    println!("i at {:p}", &i);
    i + 1
}

fn swap(pi: &mut i32, pj: &mut i32) {
    let stack_tmp = *pi;
    println!("&i {:p} {}", pi, *pi);
    println!("&j {:p} {}", pj, *pj);
    println!("&stack_tmp {:p}", &stack_tmp);
    *pi = *pj;
    *pj = stack_tmp;
}

fn swap2<T: Clone + std::fmt::Debug>(pi: &mut T, pj: &mut T) {
    let stack_tmp = pi.clone();
    println!("&i {:p} {:#?}", pi, *pi);
    println!("&j {:p} {:#?}", pj, *pj);
    println!("&stack_tmp {:p}", &stack_tmp);
    *pi = pj.clone();
    *pj = stack_tmp;
}
