#[derive(Debug)]
pub enum InheritanceType {
    Single,
    Multiple,
    Interface
}

#[derive(Debug)]
pub enum Language {
    Procedure{abstract_data_types: bool, dev_year: i32},
    Oop{inheritance_type: InheritanceType, dev_year: i32}
}