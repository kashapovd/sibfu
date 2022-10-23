use core::fmt::Debug;
use std::{cmp::{Ordering, Eq}, fmt};

#[derive(Debug)]
#[derive(Copy, Clone)]
#[derive(PartialEq, PartialOrd)]
pub enum InheritanceType {
    Single,
    Multiple,
    Interface
}

impl std::fmt::Display for InheritanceType {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            InheritanceType::Single => write!(f, "single"),
            InheritanceType::Multiple => write!(f, "multiple"),
            InheritanceType::Interface => write!(f, "interface"),
        }
    }
}

#[derive(Debug)]
#[derive(PartialEq)]
pub enum LanguageType {
    Procedure(ProcedureLang),
    Oop(OopLang)
}

impl std::fmt::Display for LanguageType {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            LanguageType::Procedure(_) => write!(f, "procedure"),
            LanguageType::Oop(_) => write!(f, "object-oriented"),
        }
    }
}

#[derive(Debug)]
#[derive(PartialEq, PartialOrd)]
pub struct OopLang {
    pub inh_type: InheritanceType,
    pub dev_year: i32
}

#[derive(Debug)]
#[derive(PartialEq, PartialOrd)]
pub struct ProcedureLang {
    pub abstract_data_types: bool,
    pub dev_year: i32
}

impl ProcedureLang {
    pub fn new(abstract_data_types: bool, dev_year: i32) -> Self {
        ProcedureLang { abstract_data_types, dev_year }
    }
}

impl OopLang {
    pub fn new(inh_type: InheritanceType, dev_year: i32) -> Self {
        OopLang { inh_type, dev_year }
    }
}

pub trait Language {
    fn get_devyear(&self) -> i32;
    fn get_type(&self) -> LanguageType;
}

impl Language for OopLang {
    fn get_devyear(&self) -> i32 {
        self.dev_year
    }
    fn get_type(&self) -> LanguageType {
        LanguageType::Oop(OopLang { inh_type: self.inh_type, dev_year: self.dev_year })
    }
}

impl Language for ProcedureLang {
    fn get_devyear(&self) -> i32 {
        self.dev_year
    }
    fn get_type(&self) -> LanguageType {
        LanguageType::Procedure(ProcedureLang { abstract_data_types: self.abstract_data_types, dev_year: self.dev_year })
    }
}

impl fmt::Display for dyn Language {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self.get_type() {
            LanguageType::Procedure(p) => writeln!(f, "lang:\n\ttype: {},\n\tSupport abstract types: {},\n\tYear of development: {}",  self.get_type(), p.abstract_data_types, p.dev_year),
            LanguageType::Oop(o) => writeln!(f, "lang:\n\ttype: {},\n\tSupport abstract types: {},\n\tYear of development: {}",  self.get_type(), o.get_type(), o.dev_year),
        }
    }
}

impl Debug for dyn Language {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "lang: {:?}", self.get_type())
    }
}

impl Ord for dyn Language {
    fn cmp(&self, other: &Self) -> Ordering {
        self.get_devyear().cmp(&other.get_devyear())
    }
}

impl Eq for dyn Language {}

impl PartialOrd for dyn Language {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for dyn Language {
    fn eq(&self, other: &Self) -> bool {
        self.get_devyear() == other.get_devyear()
    }
}

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn lang_comp() {
        let e1 = Box::new(OopLang::new(InheritanceType::Multiple, 1938)) as Box<dyn Language>;
        let e2 = Box::new(OopLang::new(InheritanceType::Single, 1928)) as Box<dyn Language>;
        assert_eq!(e1 > e2, true);
    }
}