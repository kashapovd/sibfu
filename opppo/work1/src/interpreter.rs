use crate::cmd::CmdType;
use crate::list::Slist;
use crate::entities::{Language, OopLang, ProcedureLang};
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
                        CmdType::AddP(abstract_data_types_support, devyear) => {
                            self.lang_list.push(Box::new(ProcedureLang::new(abstract_data_types_support, devyear)) as Box<dyn Language>)
                        }
                        CmdType::Print => {
                            println!("{:#?}", self.lang_list)
                        }
                        CmdType::Flush => {
                            //drop(&self.lang_list);
                        }
                        _ => {}
                    }
                }
                Err(_) => {}
            }
        }
    }
}