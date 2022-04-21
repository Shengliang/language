use bit_set::BitSet;

fn main() {

    let mut s = BitSet::with_capacity(128);
    for x in 0..127 {
        s.insert(x);
        if (x % 2) == 0 {
            s.remove(x);
        }
    }
    for x in 0..127 {
        if s.contains(x) {
            println!("{}", x);
        }
    }

   let other = BitSet::from_bytes(&[0b11010000]);
   
   println!("s.iter:");
   for x in s.iter() {
       println!("{}", x);
   }
   s.union_with(&other);
   
   // Print 0, 1, 3 in some order
   println!("s.iter:");
   for x in s.iter() {
       println!("{}", x);
   }
   println!("\ns: {:#?}", s);
   
   // Can convert back to a `BitVec`
   let bv = s.into_bit_vec();
   assert!(bv[3]);
   println!("{:#?}", bv);
}
