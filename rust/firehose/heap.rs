use std::rc::Rc;
use std::cell::RefCell;
type OptNode = Option<Rc<RefCell<TreeNode>>>;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: OptNode,
  pub right: OptNode,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

fn main() {
    let a = heap_i32();
    println!("&a {:p} a:{:p} a {} ", &a, a, a);
    println!("heap function at {:X}", heap_i32 as u64);

    let a = heap_tree_node();
    println!("&a {:p} a:{:p} a {:#?} ", &a, a, a);
    println!("heap function at {:X}", heap_tree_node as u64);
}
fn heap_i32() -> Box<i32> {
   let b = Box::new(42);
   println!("&b {:p} b {} ", &b, b);
   b
}

fn heap_tree_node() -> Box<TreeNode> {
   let b = Box::new(TreeNode::new(42));
   println!("&b {:p} b {:#?} ", &b, b);
   b
}

/*
output:

&b 0x7fff88b70198 b 42 
&a 0x7fff88b70328 a:0x5627f5280ba0 a 42 
heap function at 5627F3D4CC70
&b 0x7fff88b70180 b TreeNode {
    val: 42,
    left: None,
    right: None,
} 
&a 0x7fff88b70400 a:0x5627f5280bc0 a TreeNode {
    val: 42,
    left: None,
    right: None,
} 
heap function at 5627F3D4CE00
*/
