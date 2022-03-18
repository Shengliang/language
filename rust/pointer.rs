// This derive will use the equality of the underlying fields
#[derive(PartialEq)]
struct Pt {
    x: f32,
    y: f32,
}

impl Pt {
    fn new(x: f32, y: f32) -> Self {
        Self { x, y }
    }
}

struct Tr<'a> {
    a: &'a Pt,
}

impl<'a> Tr<'a> {
    fn new(a: &'a Pt) -> Self {
        Self { a }
    }
}

// Here we use std::ptr::eq to compare the *addresses* of `self.a` and `other.a`
impl<'a> PartialEq for Tr<'a> {
    fn eq(&self, other: &Tr<'a>) -> bool {
        std::ptr::eq(self.a, other.a)
    }
}

use std::ptr;

#[allow(dead_code)]
struct Foo<'a> {
    bar: &'a str,
}

fn check_ptr() {
    let foo_instance = Foo { bar: "bar" };
    let some_vector: Vec<&Foo> = vec![&foo_instance];

    assert!(some_vector[0] as *const Foo == &foo_instance as *const Foo);
    assert!(ptr::eq(some_vector[0], &foo_instance));
}

fn main() {
    check_ptr();

    let tr_base1 = Pt::new(0.0, 0.0);
    let tr_base2 = Pt::new(0.0, 0.0);
    assert!(tr_base1 == tr_base2);

    let tr1 = Tr::new(&tr_base1);
    let tr2 = Tr::new(&tr_base2);
    let tr3 = Tr::new(&tr_base1);

    assert!(tr1 == tr3);
    assert!(tr1.a == tr2.a);
    assert!(tr1 != tr2);
}
