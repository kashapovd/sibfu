use crate::cmd::CmdType;
use crate::list::Slist;
use crate::entities::{Language, OopLang, ProcedureLang, LanguageType};
use crate::parser::Parser;
use crate::lexer::Lexer;

pub(crate) struct Interpenter {
    input: String,
    lang_list: Slist
}

impl Interpenter {
    pub fn new(input: String) -> Self {
        Self { input, lang_list: Slist::new() }
    }

    pub fn execute(&mut self) -> Result<String, String> {
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
                        CmdType::AddP(abstract_data_types_support, devyear) => {
                            self.lang_list.push(Box::new(ProcedureLang::new(abstract_data_types_support, devyear)) as Box<dyn Language>)
                        }
                        CmdType::Print => {
                            println!("{}", self.lang_list)
                        }
                        CmdType::Flush => {
                            self.lang_list.clean();
                        }
                        CmdType::SortDevyear => {
                            if self.lang_list.len() == 0 {
                                return Err(format!("list is empty"));
                            } 
                            self.lang_list.sort();
                        }
                        CmdType::DelO => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Oop(_) => true,
                                    LanguageType::Procedure(_) => false,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelP => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(_) => true,
                                    LanguageType::Oop(_) => false,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfDevyear(year) => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(p) => p.get_devyear() == year,
                                    LanguageType::Oop(o) => o.get_devyear() == year,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfPDevyear(year) => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(p) => p.get_devyear() == year,
                                    LanguageType::Oop(_) => false,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfODevyear(year) => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Oop(o) => o.get_devyear() == year,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfOInhtype(inh_type) => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(_) => false,
                                    LanguageType::Oop(o) => o.get_type() == LanguageType::Oop(OopLang{inh_type, dev_year: o.get_devyear()}),
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        CmdType::DelIfPAdt(adt) => {
                            while let Some(index) = self.lang_list.iter().position(
                                |x|
                                match x.get_type() {
                                    LanguageType::Procedure(p) => p.get_type() == LanguageType::Procedure(ProcedureLang{abstract_data_types: adt, dev_year: p.get_devyear()}),
                                    LanguageType::Oop(_) => false,
                                }
                            ) {
                                self.lang_list.delete(index);
                            }
                        }
                        _ => {}
                    }
                }
                Err(err_msg) => {
                    return Err(err_msg);
                }
            }
        }
        Ok("".to_string())
    }
}