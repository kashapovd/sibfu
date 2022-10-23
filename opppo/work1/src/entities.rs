use core::fmt::Debug;

#[derive(Debug)]
#[derive(Copy, Clone)]
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
pub struct OopLang {
    inh_type: InheritanceType,
    dev_year: i32
}

#[derive(Debug)]
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

pub(crate) trait Language {
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
        write!(f, "{:?}", self.get_type())
    }
}