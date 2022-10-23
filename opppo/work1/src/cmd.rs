use crate::{entities::InheritanceType, token::{TokenType, Token, self}, interpreter::Interpenter, utils::vecTokenToVecTokenType};

#[derive(Debug)]
#[derive(Copy, Clone)]
pub enum CmdType {
    AddP(bool, i32),
    AddO(InheritanceType, i32),
    DelP,
    DelO,
    DelIfDevyear(i32),
    DelIfPDevyear(i32),
    DelIfODevyear(i32),
    DelIfPAdt(bool),
    DelIfOInhtype(InheritanceType),
    SortDevyear,
    Print,
    Flush
}

#[derive(Debug)]
#[derive(Clone)]
pub struct Command {
    ctype: CmdType
}

impl Command {
    pub fn new(tokens: &Vec<Token>) -> Result<Self, String> {
        let ctype = Self::match_command_type_by_token(tokens);
        match ctype {
            Ok(t) => Ok(Self { ctype: t }),
            Err(err) => Err(err)
        }
    }
    pub fn get_type(&self) -> CmdType {
        self.ctype
    }
    fn match_command_type_by_token(tokens: &Vec<Token>) -> Result<CmdType, String> {
        let tokenTypes = vecTokenToVecTokenType(tokens);
        match tokenTypes.as_slice() {
            [TokenType::Print] => { 
                Ok(CmdType::Print) 
            }
            [TokenType::Flush] => { 
                Ok(CmdType::Flush) 
            }
            [TokenType::Sort, TokenType::DevyearInnerKeyword] => { 
                Ok(CmdType::SortDevyear) 
            }
            [TokenType::Add, TokenType::Procedure, TokenType::Logic, TokenType::Num] => { 
                Ok(CmdType::AddP(tokens.get(2).unwrap().parse_content_as_logic().unwrap(), 
                                 tokens.get(3).unwrap().parse_content_as_int().unwrap())) 
            }
            [TokenType::Add, TokenType::Oop, TokenType::InhType, TokenType::Num] => { 
                Ok(CmdType::AddO(tokens.get(2).unwrap().parse_content_inh_type().unwrap(), 
                                 tokens.get(3).unwrap().parse_content_as_int().unwrap())) 
            }
            [TokenType::Del, TokenType::Procedure] => { 
                Ok(CmdType::DelP) 
            }
            [TokenType::Del, TokenType::Oop] => { 
                Ok(CmdType::DelO) 
            }
            [TokenType::Del, TokenType::If, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num] => { 
                Ok(CmdType::DelIfDevyear(tokens.get(4).unwrap().parse_content_as_int().unwrap())) 
            }
            [TokenType::Del, TokenType::If, TokenType::Oop, TokenType::Dot, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num] => { 
                Ok(CmdType::DelIfODevyear(tokens.get(6).unwrap().parse_content_as_int().unwrap())) 
            }
            [TokenType::Del, TokenType::If, TokenType::Oop, TokenType::Dot, TokenType::InhtypeInnerKeyword, TokenType::Assign, TokenType::InhType] => { 
                Ok(CmdType::DelIfOInhtype(tokens.get(6).unwrap().parse_content_inh_type().unwrap())) 
            }
            [TokenType::Del, TokenType::If, TokenType::Procedure, TokenType::Dot, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num] => { 
                Ok(CmdType::DelIfPDevyear(tokens.get(6).unwrap().parse_content_as_int().unwrap())) 
            }
            [TokenType::Del, TokenType::If, TokenType::Procedure, TokenType::Dot, TokenType::AdtInnerKeyword, TokenType::Assign, TokenType::Logic] => { 
                Ok(CmdType::DelIfPAdt(tokens.get(6).unwrap().parse_content_as_logic().unwrap())) 
            }
            _ => {
                Err(format!("Unknown command \"{:?}\"", tokens))
            }
            
        }
    }
}