use crate::cmd::CmdType;
use crate::entities::{FuncLang, Language, LanguageType, OopLang, ProcedureLang};
use crate::lexer::Lexer;
use crate::list::Slist;
use crate::parser::Parser;
use chrono::{self, Datelike};

/// Represents interpenter object in the program
pub(crate) struct Interpenter {
    /// Input commands as string
    input: String,
    /// List to be processed with commands
    lang_list: Slist,
}

impl Interpenter {
    /// Contructs new `Interpenter` object from a given string
    /// # Arguments
    /// * `input` - Contains input string to interpet
    /// # Returns
    /// New `Interpenter` object
    pub fn new(input: String) -> Self {
        Self {
            input,
            lang_list: Slist::new(),
        }
    }

    /// Executes a given input
    /// # Returns
    /// `Result` with succes or err message
    pub fn execute(&mut self) {
        for cmd_line in self.input.lines() {
            print!("##> \"{}\" => ", cmd_line);
            let mut lex = Lexer::new(cmd_line.to_owned());
            let tokens = lex.tokenizator();
            let mut p = Parser::new(tokens);
            let c = p.parse();
            println!("{:?}", c);
            match c {
                Ok(cmd) => {
                    match cmd.get_type() {
                        CmdType::AddO(inhtype, devyear) => {
                            self.lang_list.push(Box::new(OopLang::new(inhtype, devyear)) as Box<dyn Language>);
                        }
                        CmdType::AddP(abstract_data_types_support, devyear) => self.lang_list.push(
                            Box::new(ProcedureLang::new(abstract_data_types_support, devyear))
                                as Box<dyn Language>,
                        ),
                        CmdType::AddF(purity_support, devyear) => self
                            .lang_list
                            .push(Box::new(FuncLang::new(purity_support, devyear))
                                as Box<dyn Language>),
                        CmdType::Print => {
                            println!("{}", self.lang_list)
                        }
                        CmdType::Flush => {
                            self.lang_list.clean();
                        }
                        CmdType::SortDevyear => {
                            self.lang_list.sort();
                        }
                        CmdType::Diff => {
                            if !self.lang_list.is_empty() {
                                let current_year = chrono::Utc::now().year();
                                println!("Current year: {current_year}");
                                for e in self.lang_list.iter() {
                                    print!("{}", e);
                                    println!("+-->\tYear diff: {}", current_year - e.get_devyear());
                                }
                            }
                        }
                        CmdType::DelO => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Oop(_) => true,
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Functional(_) => false,
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelP => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(_) => true,
                                    LanguageType::Oop(_) => false,
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelF => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Oop(_) => false,
                                    LanguageType::Functional(_) => true,
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfDevyear(year) => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(p) => p.get_devyear() == year,
                                    LanguageType::Oop(o) => o.get_devyear() == year,
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfPDevyear(year) => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(p) => p.get_devyear() == year,
                                    LanguageType::Oop(_) => false,
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfODevyear(year) => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Oop(o) => o.get_devyear() == year,
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfOInhtype(inh_type) => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Oop(o) => {
                                        o.get_type()
                                            == LanguageType::Oop(OopLang {
                                                inh_type,
                                                dev_year: o.get_devyear(),
                                            })
                                    }
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfPAdt(adt) => {
                            while let Some(index) =
                                self.lang_list.iter().position(|x| match x.get_type() {
                                    LanguageType::Procedure(p) => {
                                        p.get_type()
                                            == LanguageType::Procedure(ProcedureLang {
                                                abstract_data_types: adt,
                                                dev_year: p.get_devyear(),
                                            })
                                    }
                                    LanguageType::Oop(_) => false,
                                    LanguageType::Functional(_) => todo!(),
                                })
                            {
                                self.lang_list.delete(index);
                            }
                        }
                        _ => {}
                    }
                }
                Err(_) => {}
            }
        }
    }
}
