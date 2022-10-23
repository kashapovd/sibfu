use std::ptr;
use std::fmt;
use crate::entities::Language;

#[derive(Debug)]
pub struct Slist {
    head: Link,
    tail: *mut Node,
}

impl fmt::Display for Slist {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Customize so only `x` and `y` are denoted.
        write!(f, "head: {:?}, tail: {:?}", self.head, self.tail)
    }
}

type Link = *mut Node;

#[derive(Debug)]
struct Node {
    elem: Box<dyn Language>,
    next: Link,
}

impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Customize so only `x` and `y` are denoted.
        write!(f, "value: {:?}, next: {:?}", self.elem, self.next)
    }
}

pub struct IntoIter(Slist);

pub struct Iter<'a> {
    next: Option<&'a Node>,
}

pub struct IterMut<'a> {
    next: Option<&'a mut Node>,
}

impl Slist {
    pub fn new() -> Self {
        Slist { head: ptr::null_mut(), tail: ptr::null_mut() }
    }

    pub fn push(&mut self, elem: Box<dyn Language>) {
        unsafe {
            let new_tail = Box::into_raw(Box::new(Node {
                elem: elem,
                next: ptr::null_mut(),
            }));

            if !self.tail.is_null() {
                (*self.tail).next = new_tail;
            } else {
                self.head = new_tail;
            }

            self.tail = new_tail;
            (*self.tail).next = self.head;
        }
    }
    pub fn pop(&mut self) -> Option<Box<dyn Language>> {
        unsafe {
            if self.head.is_null() {
                None
            } else {
                let head = Box::from_raw(self.head);

                if self.head != self.tail  {
                    self.head = head.next;
                    (*self.tail).next = self.head;
                } else {
                    self.tail = ptr::null_mut();
                    self.head = ptr::null_mut();
                }

                Some(head.elem)
            }
        }
    }

    pub fn peek(&self) -> Option<& Box<dyn Language>> {
        unsafe {
            self.head.as_ref().map(|node| &node.elem)
        }
    }

    pub fn peek_mut(&mut self) -> Option<&mut Box<dyn Language>> {
        unsafe {
            self.head.as_mut().map(|node| &mut node.elem)
        }
    }

    pub fn clean(&mut self) {
        while let Some(_) = self.pop() { }
    }

    //iter
    pub fn into_iter(self) -> IntoIter {
        IntoIter(self)
    }

    pub fn iter(&self) -> Iter<'_> {
        unsafe {
            Iter { next: self.head.as_ref() }
        }
    }

    pub fn iter_mut(&mut self) -> IterMut<'_> {
        unsafe {
            IterMut { next: self.head.as_mut() }
        }
    }
}

impl Drop for Slist {
    fn drop(&mut self) {
        self.clean();
    }
}

impl Iterator for IntoIter {
    type Item = Box<dyn Language>;
    fn next(&mut self) -> Option<Self::Item> {
        self.0.pop()
    }
}

impl<'a> Iterator for Iter<'a> {
    type Item = &'a Box<dyn Language>;

    fn next(&mut self) -> Option<Self::Item> {
        unsafe {
            self.next.map(|node| {
                self.next = node.next.as_ref();
                &node.elem
            })
        }
    }
}

impl<'a> Iterator for IterMut<'a> {
    type Item = &'a mut Box<dyn Language>;

    fn next(&mut self) -> Option<Self::Item> {
        unsafe {
            self.next.take().map(|node| {
                self.next = node.next.as_mut();
                &mut node.elem
            })
        }
    }
}

#[cfg(test)]
mod test {
    use crate::entities::{OopLang, InheritanceType};

    use super::*;
    #[test]
    fn basics() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1928)) as Box<dyn Language>);
        println!("{:?}", list);

        let r = list.peek();
        let l = Box::new(OopLang::new(InheritanceType::Single, 1928)) as Box<dyn Language>;
        assert_eq!(r, Some(&l));
        let mut r = list.pop();
        assert_eq!(r, Some(Box::new(OopLang::new(InheritanceType::Single, 1928)) as Box<dyn Language>));
        r = list.pop();
        assert_eq!(r, None);
    }
}