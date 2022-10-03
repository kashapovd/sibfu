use std::boxed::Box;

pub(crate) struct Slist<Language> {
    head: Option<Box<Node<Language>>>,
}

impl<Language> Slist<Language> {
    pub fn new() -> Self {
        Slist {
            head: None
        }
    }
    pub fn push(&mut self, value: Language) {
        let old_head = self.head.take();
        let new_head = Box::new(Node::new(value, old_head));
        self.head = Some(new_head);
    }
    pub fn pop(&mut self) -> Option<Language> {
        self.head.take().map(|n| {
            self.head = n.next;
            n.value
        })
    }
    pub fn peek(&self) -> Option<&Language> {
        self.head.as_ref().map(|n| {
            &n.value
        })
    }
}

struct Node<Language> {
    value: Language,
    next: Option<Box<Node<Language>>>,
}

impl<Language> Node<Language> {
    pub fn new(value: Language, next: Option<Box<Node<Language>>>) -> Self {
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
        let mut list:Slist<i32> = Slist::new();
        list.push(5);
        let r = list.peek();
        assert_eq!(r, Some(&5));
        let mut r = list.pop();
        assert_eq!(r, Some(5));
        r = list.pop();
        assert_eq!(r, None);
    }
}