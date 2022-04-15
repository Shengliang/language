// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
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

//use std::borrow::BorrowMut;
use std::rc::Rc;
use std::cell::RefCell;
use std::cmp::Ordering;
type OptNode = Option<Rc<RefCell<TreeNode>>>;

pub fn search_bst_r(root: OptNode, val: i32) -> OptNode {
     if let Some(r) = &root {
        if r.borrow().val < val {
            return search_bst_r(r.borrow().right.clone(), val);
        } else if r.borrow().val > val {
            return search_bst_r(r.borrow().left.clone(), val);
        }
    }
    return root;
}


pub fn search_bst(root: OptNode, val: i32) -> OptNode {
    let mut node = root;
    while let Some(rc_node) = node.clone() {
        let cur_node = rc_node.borrow();
        match cur_node.val.cmp(&val) {
            Ordering::Equal => return node,
            Ordering::Less if cur_node.right.is_some() => node = cur_node.right.clone(),
            Ordering::Greater if cur_node.left.is_some() => node = cur_node.left.clone(),
            _ => break,
        }
    }
    None
}


fn inorder(root: OptNode) -> Vec<i32> {
    fn helper(node: &OptNode, ret: &mut Vec<i32>) {
        if let Some(v) = node {
            let v = v.borrow();
            helper(&v.left, ret);
            ret.push(v.val);
            helper(&v.right, ret);
        }
    }
    let mut ret = vec![];
    if let Some(v) = root {
        helper(&Some(v), &mut ret);
    }
    ret
}

/*
fn inorder(node: &TreeNode, ret: &mut Vec<i32>) {
   // right: Option<Rc<RefCell<TreeNode>>>
   if let Some(ref left) = node.left {
       inorder(& left.borrow(), ret);
   }
   ret.push(node.val);
   if let Some(ref right) = node.left {
       inorder(& right.borrow(), ret);
   }
}
*/

fn main() {
  let arr = [0, 1, 2, 3, 4, 5, 6];
  let sum = arr.iter().fold(0, |acc, x| acc + x);
  let nodes: Vec<OptNode> = arr.iter().map(|x| Some(Rc::new(RefCell::new(TreeNode::new(*x))))).collect();
  println!("{} {:?}", sum, nodes);
  //nodes.iter().map(|x| { println!("{:p} {}", &x, x.take().val) });
  /*
     3
    / \
   1   5
  / \  /\
  0 2 4  6
  let mut i: usize = 0;
  let mut j: usize = 6;
  while i < j {
      let m = i + (j-i)/2;
  }
   */
  println!("{:#?} {:p}", nodes[3], &nodes[3]);
  nodes[3]
      .as_ref()
      .map(|n| {
          let mut n = n.borrow_mut();
          n.left = nodes[1].clone();
          n.right = nodes[5].clone();
          println!("{:#?} {:p} {:p} {:p}", n, &n, &n.left, &n.right)
      });
  nodes[1]
      .as_ref()
      .map(|n| { let mut n = n.borrow_mut(); n.left = nodes[0].clone(); n.right = nodes[2].clone();
          println!("{:#?} {:p} {:p} {:p}", n, &n, &n.left, &n.right)
      });
  nodes[5]
      .as_ref()
      .map(|n| {
          let mut n = n.borrow_mut();
          n.left = nodes[4].clone();
          n.right = nodes[6].clone();
          println!("{:#?} {:p} {:p} {:p}", n, &n, &n.left, &n.right)
      });

  //let mut ret = vec![];
  //inorder(&nodes[3], &mut ret);
  let ret = inorder(nodes[3].clone());
  println!("{:#?}", ret);
  println!("{:#?} {:p}", nodes[3], &nodes[3]);
  let x = search_bst(nodes[3].clone(), 2);
  let y = search_bst_r(nodes[3].clone(), 2);
  println!("{:#?} {:#?}", x, y);

}
