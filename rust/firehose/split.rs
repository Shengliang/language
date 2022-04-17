fn main() {
let mut char_array: [char; 2] = ['a', 'b'];
let (first_slice, rest_slice) =
    char_array.split_at_mut(1);

let first_element = &mut first_slice[0];
let second_element = &rest_slice[0];

*first_element = *second_element;
assert_eq!(char_array[0], 'b');
}
