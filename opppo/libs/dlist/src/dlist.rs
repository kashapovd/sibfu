use std::boxed::Box;

struct Dlist<T> {
    head: Option<Box<Node<T>>>,
}

impl<T> Dlist<T> {
    pub fn new() -> Self {
        Dlist {
            head: None
        }
    }
    pub fn push(&mut self, value: T) {
        let old_head = self.head.take();
        let new_head = Box::new(Node::new(value, old_head));
        self.head = Some(new_head);
    }
    pub fn pop(&mut self) -> Option<T> {
        self.head.take().map(|n| {
            self.head = n.next;
            n.value
        })
    }
    pub fn peek(&self) -> Option<&T> {
        self.head.as_ref().map(|n| {
            &n.value
        })
    }
}

struct Node<T> {
    value: T,
    next: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    pub fn new(value: T, next: Option<Box<Node<T>>>) -> Self {
        Node { 
            value, 
            next 
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn basics() {
        let mut list:Dlist<i32> = Dlist::new();
        list.push(5);
        let r = list.peek();
        assert_eq!(r, Some(&5));
        let mut r = list.pop();
        assert_eq!(r, Some(5));
        r = list.pop();
        assert_eq!(r, None);
    }
}