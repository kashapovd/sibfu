use std::{rc::{Rc, Weak}, cell::RefCell};

struct Dlist<T> {
    head: Option<Rc<RefCell<Node<T>>>>,
    tail: Option<Rc<RefCell<Node<T>>>>,
}

impl<T> Dlist<T> {
    pub fn new() -> Self {
        Dlist {
            head: None, 
            tail: None 
        }
    }
    pub fn push_back(&mut self, value: T) {

        let mut node = Node::new(value);
        match &self.tail {
            None => {
                let node = Rc::new(RefCell::new(node));
                self.head = Some(Rc::clone(&node));
                self.tail = Some(Rc::clone(&node));
            }
            Some(oldTail) => {
                node.prev = Some(Rc::downgrade(oldTail));
                let newTail = Rc::new(RefCell::new(node));
                oldTail.borrow_mut().next = Some(Rc::clone(&newTail));
                self.tail = Some(newTail);
            }
        }

    } 
    pub fn push_front(value: isize) {
        let mut node = Node::new(value);
        todo!()
    }

}

struct Node<T> {
    value: T,
    next: Option<Rc<RefCell<Node<T>>>>,
    prev: Option<Weak<RefCell<Node<T>>>>
}

impl<T> Node<T> {
    pub fn new(value: T) -> Self {
        Node {
            value, // using shortland struct initializtion
            prev: None,
            next: None
        }
    }
}