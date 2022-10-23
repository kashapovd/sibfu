use std::fmt::Debug;
use std::ptr;
use std::fmt;
use crate::utils;
use crate::entities::Language;

type Link = *mut Node;

/// Represents circular syngly-linked list in the program
#[derive(Debug)]
pub struct Slist {
    /// Points to a head of the list
    head: Link,
    /// Points to a tail of the list
    tail: Link,
    /// Contains current size of the list 
    len: usize
}

/// Represents the member of linked list 
#[derive(Debug)]
struct Node {
    /// Contains the value of `Language` trait  
    elem: Box<dyn Language>,
    /// Points to the next member
    next: Link,
}

impl Slist {
    /// Constructs new object of `Slist`
    /// # Returns
    /// New object of `Slist`
    pub fn new() -> Self {
        Slist {
            head: ptr::null_mut(),
            tail: ptr::null_mut(),
            len: 0
        }
    }
    /// Performs unsafe push a new value to the list
    /// # Arguments
    /// * `elem` - `Language` value to be pushed
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
    /// Performs unsafe delete a first member of the list
    /// # Returns
    /// `Option` that contains removed `Language` value
    /// If nothing to remove, just returns `None`
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

    /// Returns first value of list  
    pub fn peek(&self) -> Option<& Box<dyn Language>> {
        unsafe {
            self.head.as_ref().map(|node| &node.elem)
        }
    }

    /// Performs list cleanup by correct termination of objects
    pub fn clean(&mut self) {
        while let Some(_) = self.pop() { }
    }

    /// Performs unsafe delete of membere at given index 
    pub fn delete(&mut self, index: usize) {
        // use vector to safe needed elements
        let mut elements: Vec<Box<dyn Language>> = Vec::new();
        for i in 0..index+1 {
            if i == index {
                // remove desired element
                self.pop();
                break;
            }
            elements.push(self.pop().unwrap());
            
        }
        while let Some(e) = utils::pop_front_vec(&mut elements) {
            self.push(e);
        }
    }

    /// Performs sorting of list. Uses vector as transition state and uses its
    /// sort algo instead of implementation algo for our `Slist`
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

    /// Returns a size of the list
    /// # Returns
    /// Size of the list as `usize` value
    pub fn len(&self) -> usize {
        self.len
    }

    /// Implements unsafe iterator wrapper for `Slist`
    /// # Returns
    /// Imutable Iterator of `Slist`
    pub fn iter(&self) -> Iter<'_> {
        unsafe {
            Iter { next: self.head.as_ref(), len: self.len}
        }
    }

    /// Implements unsafe iterator wrapper for `Slist`
    /// # Returns
    /// Mutable Iterator of `Slist`
    pub fn iter_mut(&mut self) -> IterMut<'_> {
        unsafe {
            IterMut { next: self.head.as_mut() }
        }
    }
}

/// Implements destructor of `Slist`
impl Drop for Slist {
    fn drop(&mut self) {
        self.clean();
    }
}

/// Implements Display trait for `Node`
impl<'a> std::fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        writeln!(f, "{}", self.elem)
    }
}

/// Implements Display trait for `Slist`
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

pub struct IntoIter(Slist);

/// Represents iterator for linked list
pub struct Iter<'a> {
    // Points to next slist value 
    next: Option<&'a Node>,
    /// Contorl maximum of iterations because of list circularity
    len: usize
}

/// Represents iterator for linked list
pub struct IterMut<'a> {
    next: Option<&'a mut Node>,
}

impl Iterator for IntoIter {
    type Item = Box<dyn Language>;
    fn next(&mut self) -> Option<Self::Item> {
        self.0.pop()
    }
}

/// Implements `Iterator` trait for `Iter` object
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
    #[test]
    fn flushing() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Single, 2000)) as Box<dyn Language>);
        
        list.clean();
        assert_eq!(list.peek(), None);
    }
    #[test]
    fn deleting() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Single, 2000)) as Box<dyn Language>);
        
        list.delete(0);
        let mut e = list.pop();
        assert!(e.is_some());
        e = list.pop();
        assert!(e.is_some());
        e = list.pop();
        assert!(e.is_some());
        e = list.pop();
        assert!(e.is_none());
    }
    #[test]
    fn iter() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>);
        
        let mut iter = list.iter();
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>).as_ref());
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>).as_ref());
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>).as_ref());
        assert_eq!(iter.next(), None);
    }
    fn iter_mut() {
        let mut list:Slist = Slist::new();
        list.push(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>);
        list.push(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>);
        
        let mut iter = list.iter_mut();
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Single, 1931)) as Box<dyn Language>).as_mut());
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Multiple, 1967)) as Box<dyn Language>).as_mut());
        assert_eq!( iter.next(), 
                    Some(Box::new(OopLang::new(InheritanceType::Interface, 1930)) as Box<dyn Language>).as_mut());
        assert_eq!(iter.next(), None);
    } 
}