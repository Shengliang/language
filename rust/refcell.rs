/*
Interior mutability is a design pattern in Rust that allows you to mutate data even when there are immutable references to that data; normally, this action is disallowed by the borrowing rules.


1. At any given time, you can have either (but not both of) one mutable reference or any number of immutable references.

2. References must always be valid.

3. With references and Box<T>, the borrowing rules’ invariants are enforced
at compile time. 
---------------

4. With RefCell<T>, these invariants are enforced at runtime.
                                                 --------
5. Similar to Rc<T>, RefCell<T> is only for use in single-threaded scenarios and will give you a compile-time error if you try using it in a multithreaded context. 

Here is a recap of the reasons to choose Box<T>, Rc<T>, or RefCell<T>:
Rc<T> enables multiple owners of the same data; Box<T> and RefCell<T> have single owners.
Box<T> allows immutable or mutable borrows checked at compile time; Rc<T> allows only immutable borrows checked at compile time; RefCell<T> allows immutable or mutable borrows checked at runtime.
Because RefCell<T> allows mutable borrows checked at runtime, you can mutate the value inside the RefCell<T> even when the RefCell<T> is immutable.
*/


#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

impl List {
    fn tail(&self) -> Option<&Rc<List>> {
        match self {
            Cons(_, item) => Some(item),
            Nil => None,
        }
    }
    fn head(&self) -> Option<&Rc<RefCell<i32>>> {
        match self {
            Cons(item, _) => Some(item),
            Nil => None,
        }
    }
}


use crate::List::{Cons, Nil};
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil)));

    let b = Cons(Rc::new(RefCell::new(3)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(4)), Rc::clone(&a));

    *value.borrow_mut() += 10;

    println!("a after = {:?}", a);
    println!("b after = {:?} {:?}", b.head(), b.tail().unwrap().head());
    *value.borrow_mut() += 10;
    println!("c after = {:?} {:?}", c.head(), c.tail().unwrap().head());
}

