use crate::cmd::{Command, CmdType};
use crate::list::Slist;
use crate::entities::Language;
use crate::parser::Parser;
use crate::lexer::Lexer;

pub(crate) struct Interpenter {
    input: String,
    lang_list: Slist<Language>
}

impl Interpenter {
    pub fn new(input: String) -> Self {
        Self { input, lang_list: Slist::new() }
    }

    pub fn execute(&mut self) {
        for cmd_line in self.input.lines() {
            print!("> {}: ", cmd_line);
            let mut lex = Lexer::new(cmd_line.to_owned());
            let tokens = lex.tokenizator();
            let mut p = Parser::new(tokens);
            let c = p.parse();
            println!("{:?}", c);
            match c {
                Ok(cmd) => {
                    match cmd.ctype {
                        CmdType::AddO(inhtype, devyear) => {
                            self.lang_list.push(Language::Oop {inheritance_type: inhtype, dev_year: devyear})
                        }
                        CmdType::AddP(abstract_data_types_support, devyear) => {
                            self.lang_list.push(Language::Procedure {abstract_data_types: abstract_data_types_support, dev_year:devyear})
                        }
                        CmdType::Print => {
                            println!("{:?}", self.lang_list.peek().unwrap())
                        }
                        _ => {}
                    }
                }
                Err(_) => {}
            }
        }
    }
}