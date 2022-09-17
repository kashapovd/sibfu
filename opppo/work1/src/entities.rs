enum InheritanceType {
    Single,
    Multiple,
    Interface
}

enum Language {
    Procedure{abstract_data_types: bool, dev_year: u32},
    Oop{inheritance_type: InheritanceType, dev_year: u32}
}