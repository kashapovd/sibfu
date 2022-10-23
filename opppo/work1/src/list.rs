use std::fmt::Debug;
use std::ptr;
use std::fmt;
use crate::entities::Language;

type Link = *mut Node;

#[derive(Debug)]
pub struct Slist {
    head: Link,
    tail: Link,
    len: usize
}

impl<'a> std::fmt::Display for Slist {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        if self.head.is_null() {
            write!(f, "[list is empty]")
        } else {
            for e in self.iter() {
                write!(f, "{}", e);
            }
            Ok(())
        }    
    }
}

#[derive(Debug)]

struct Node {
    elem: Box<dyn Language>,
    next: Link,
}

impl<'a> std::fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        unsafe {
            writeln!(f, "{}", self.elem)
        }
    }
}

impl Slist {
    pub fn new() -> Self {
        Slist {
            head: ptr::null_mut(),
            tail: ptr::null_mut(),
            len: 0
        }
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
        self.len += 1;
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
                self.len -= 1;
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

    pub fn delete(&mut self, index: usize) {
        let mut elements: Vec<Box<dyn Language>> = Vec::new();
        for i in 0..index+1 {
            if i == index {
                self.pop();
                break;
            }
            elements.push(self.pop().unwrap());
            
        }
        while let Some(e) = elements.pop() {
            self.push(e);
        }

            
    }

    // use sort algo of vec instead of implementing algo for our list
    pub fn sort(&mut self) {
        let mut elements: Vec<Box<dyn Language>> = Vec::new();
        while let Some(e) = self.pop() {
            elements.push(e);
        }
        elements.sort_by(|a, b| b.cmp(a));
        
        while let Some(e) = elements.pop() {
            self.push(e);
        }
    }

    //iter
    pub fn into_iter(self) -> IntoIter {
        IntoIter(self)
    }

    pub fn iter(&self) -> Iter<'_> {
        unsafe {
            Iter { next: self.head.as_ref(), len: self.len}
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

pub struct IntoIter(Slist);

pub struct Iter<'a> {
    next: Option<&'a Node>,
    len: usize
}

pub struct IterMut<'a> {
    next: Option<&'a mut Node>,
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
            if self.len > 0 {
                self.next.map(|node| {
                    self.len -= 1;
                    self.next = node.next.as_ref();
                    &node.elem
                })
            } else {
                None
            }
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

        let a = [1, 2, 3];

        assert_eq!(a.iter().position(|&x| x == 2), Some(1));

        assert_eq!(a.iter().position(|&x| x == 5), None);

    }
    #[test]
    fn sorting() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Single, 2000)) as Box<dyn Language>);
        list.sort();
        
        let mut e = list.pop();
        assert_eq!(e, Some(Box::new(OopLang::new(InheritanceType::Single, 1930)) as Box<dyn Language>));
        e = list.pop();
        assert_eq!(e, Some(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>));
        e = list.pop();
        assert_eq!(e, Some(Box::new(OopLang::new(InheritanceType::Single, 1967)) as Box<dyn Language>));
        e = list.pop();
        assert_eq!(e, Some(Box::new(OopLang::new(InheritanceType::Single, 2000)) as Box<dyn Language>));
    }
}