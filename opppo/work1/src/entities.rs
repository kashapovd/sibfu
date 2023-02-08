use core::fmt::Debug;
use std::{
    cmp::{Eq, Ordering},
    fmt,
};

#[derive(Debug, Copy, Clone, PartialEq, PartialOrd)]
pub enum InheritanceType {
    Single,
    Multiple,
    Interface,
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

#[derive(Debug, PartialEq)]
pub enum LanguageType {
    Procedure(ProcedureLang),
    Oop(OopLang),
    Functional(FuncLang),
}

impl std::fmt::Display for LanguageType {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            LanguageType::Procedure(_) => write!(f, "procedure"),
            LanguageType::Oop(_) => write!(f, "object-oriented"),
            LanguageType::Functional(_) => write!(f, "functional"),
        }
    }
}

/// Represents Object Oriented Language object in program
#[derive(Debug, PartialEq, PartialOrd)]
pub struct OopLang {
    pub inh_type: InheritanceType,
    pub dev_year: i32,
}

/// Represents Procedure Language object in program
#[derive(Debug, PartialEq, PartialOrd)]
pub struct ProcedureLang {
    pub abstract_data_types: bool,
    pub dev_year: i32,
}

/// Represents Functional Language object in program
#[derive(Debug, PartialEq, PartialOrd)]
pub struct FuncLang {
    pub purity_support: bool,
    pub dev_year: i32,
}

impl ProcedureLang {
    /// Contructs new `ProcedureLang` object from a given string
    /// # Arguments
    /// * `abstract_data_types` - Contains logic value about supporting abstract data types
    /// * `dev_year` - Contains numeric value about year of language developments
    /// # Returns
    /// New `ProcedureLang` object
    pub fn new(abstract_data_types: bool, dev_year: i32) -> Self {
        ProcedureLang {
            abstract_data_types,
            dev_year,
        }
    }
}

impl OopLang {
    /// Contructs new `OopLang` object from a given string
    /// # Arguments
    /// * `purity_support` - Contains logic value about supporting abstract data types
    /// * `dev_year` - Contains numeric value about year of language developments
    /// # Returns
    /// New `OopLang` object
    pub fn new(inh_type: InheritanceType, dev_year: i32) -> Self {
        OopLang { inh_type, dev_year }
    }
}

impl FuncLang {
    /// Contructs new `FuncLang` object from a given string
    /// # Arguments
    /// * `inh_type` - Contains type of language inheritance
    /// * `dev_year` - Contains numeric value about year of language developments
    /// # Returns
    /// New `OopLang` object
    pub fn new(purity_support: bool, dev_year: i32) -> Self {
        FuncLang {
            purity_support,
            dev_year,
        }
    }
}

/// Represents Language object in program as trait
pub trait Language {
    // Returns the year of language development
    fn get_devyear(&self) -> i32;
    // Returns a type of language
    fn get_type(&self) -> LanguageType;
}

/// Impelements Language trait for Object Oriented Language object
impl Language for OopLang {
    fn get_devyear(&self) -> i32 {
        self.dev_year
    }
    fn get_type(&self) -> LanguageType {
        LanguageType::Oop(OopLang {
            inh_type: self.inh_type,
            dev_year: self.dev_year,
        })
    }
}

/// Impelements Language trait for Procedure Language object
impl Language for ProcedureLang {
    fn get_devyear(&self) -> i32 {
        self.dev_year
    }
    fn get_type(&self) -> LanguageType {
        LanguageType::Procedure(ProcedureLang {
            abstract_data_types: self.abstract_data_types,
            dev_year: self.dev_year,
        })
    }
}

impl Language for FuncLang {
    fn get_devyear(&self) -> i32 {
        self.dev_year
    }
    fn get_type(&self) -> LanguageType {
        LanguageType::Functional(FuncLang {
            purity_support: self.purity_support,
            dev_year: self.dev_year,
        })
    }
}

/// Expands Language trait with Display trait
impl fmt::Display for dyn Language {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self.get_type() {
            LanguageType::Procedure(p) => writeln!(
                f,
                "lang:\n\tType: {},\n\tSupport abstract types: {},\n\tYear of development: {}",
                self.get_type(),
                p.abstract_data_types,
                p.dev_year
            ),
            LanguageType::Oop(o) => writeln!(
                f,
                "lang:\n\tType: {},\n\tType of inheritance: {},\n\tYear of development: {}",
                self.get_type(),
                o.inh_type,
                o.dev_year
            ),
            LanguageType::Functional(func) => writeln!(
                f,
                "lang:\n\tType: {},\n\tSupport purity: {},\n\tYear of development: {}",
                self.get_type(),
                func.purity_support,
                func.dev_year
            ),
        }
    }
}

/// Expands Language trait with Debug trait
impl Debug for dyn Language {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "lang: {:?}", self.get_type())
    }
}

/// Expands Language trait with Ord trait for sorting and comparing
impl Ord for dyn Language {
    fn cmp(&self, other: &Self) -> Ordering {
        self.get_devyear().cmp(&other.get_devyear())
    }
}

/// Expands Language trait just as dependency of Ord
impl Eq for dyn Language {}

/// Expands Language trait with PartialOrd trait for sorting and comparing
impl PartialOrd for dyn Language {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

/// Expands Language trait with PartialEq trait for sorting and comparing
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
