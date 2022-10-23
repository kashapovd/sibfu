use core::fmt::Debug;
use std::cmp::{Ordering, Eq};

#[derive(Debug)]
#[derive(Copy, Clone)]
#[derive(PartialEq, PartialOrd)]
pub enum InheritanceType {
    Single,
    Multiple,
    Interface
}

#[derive(Debug)]
pub enum LanguageType {
    Procedure(ProcedureLang),
    Oop(OopLang)
}

#[derive(Debug)]
#[derive(PartialEq, PartialOrd)]
pub struct OopLang {
    inh_type: InheritanceType,
    dev_year: i32
}

#[derive(Debug)]
#[derive(PartialEq, PartialOrd)]
pub struct ProcedureLang {
    abstract_data_types: bool,
    dev_year: i32
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