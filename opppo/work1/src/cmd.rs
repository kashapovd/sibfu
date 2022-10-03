use crate::{entities::InheritanceType, token::{TokenType, Token}};

#[derive(Debug)]
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
pub struct Command {
    pub ctype: CmdType
}

impl Command {
    pub fn new(tokens: &Vec<Token>) -> Result<Self, String> {
        let ctype = Self::match_command_type_by_token(tokens);
        match ctype {
            Ok(t) => Ok(Self { ctype: t }),
            Err(err) => Err(err)
        }
    }
    fn match_command_type_by_token(tokens: &Vec<Token>) -> Result<CmdType, String> {
        let first_token = tokens.get(0).unwrap();
        match first_token.ttype {
            TokenType::Print => {
                match CPrint::compare_implementation(tokens.as_ref()) {
                    Ok(_is_correct_cmd) => Ok(CmdType::Print),
                    Err(err) => Err(err)
                }
            }
            TokenType::Sort => {
                match CSortDevyear::compare_implementation(tokens.as_ref()) {
                    Ok(_is_correct_cmd) => Ok(CmdType::SortDevyear),
                    Err(err) => Err(err)
                }
            }
            TokenType::Flush => {
                match CFlush::compare_implementation(tokens.as_ref()) {
                    Ok(_is_correct_cmd) => Ok(CmdType::Flush),
                    Err(err) => Err(err)
                }
            }
            TokenType::Add => {
                let mut error_msg: String;
                let mut compare_result = CAddp::compare_implementation(tokens.as_ref());
                
                if compare_result.is_ok() {
                    return Ok(CmdType::AddP(tokens.get(2).unwrap().parse_content_as_logic().unwrap(), tokens.get(3).unwrap().parse_content_as_int().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CAddo::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::AddO(tokens.get(2).unwrap().parse_content_inh_type().unwrap(), tokens.get(3).unwrap().parse_content_as_int().unwrap())); 
                }
                else {
                    error_msg = compare_result.err().unwrap();
                }
                Err(error_msg)
            }
            TokenType::Del => {
                let mut error_msg: String;
                let mut compare_result = CDelP::compare_implementation(tokens.as_ref());
                
                if compare_result.is_ok() {
                    return Ok(CmdType::DelP); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelO::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelO); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelIfDevyear::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelIfDevyear(tokens.get(4).unwrap().parse_content_as_int().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelIfPDevyear::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelIfPDevyear(tokens.get(6).unwrap().parse_content_as_int().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelIfODevyear::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelIfODevyear(tokens.get(6).unwrap().parse_content_as_int().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelIfOInhtype::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelIfOInhtype(tokens.get(6).unwrap().parse_content_inh_type().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                compare_result = CDelIfPAdt::compare_implementation(tokens.as_ref());
                if compare_result.is_ok() {
                    return Ok(CmdType::DelIfPAdt(tokens.get(6).unwrap().parse_content_as_logic().unwrap())); 
                } else {
                    error_msg = compare_result.err().unwrap();
                }

                Err(error_msg)
            }
            _ => {
                Err(format!("Unknown command {:?}", first_token.ttype))
            }
            
        }
    }
}

trait CommandImpl {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String>;
    fn command_comparator(tokens: &Vec<Token>, implementation: &Vec<TokenType>) -> Result<bool, String> {
        if tokens.len() == implementation.len() {
            for i in 0..tokens.len() {
                if tokens.get(i).unwrap().ttype != *implementation.get(i).unwrap() {
                    return Err(format!("Unknown parameter at {}", tokens.get(i).unwrap().start_pos));
                }
            }
        } else {
            return Err(format!("Not valid parameters for {:?}", tokens.get(0).unwrap().ttype));
        }
        Ok(true)
    }
    
}

struct CAddp {}
struct CAddo {}
struct CDelP {}
struct CDelO {}
struct CDelIfDevyear {}
struct CDelIfPDevyear {}
struct CDelIfODevyear {}
struct CDelIfPAdt {}
struct CDelIfOInhtype {}
struct CSortDevyear {}
struct CPrint {}
struct CFlush {}

impl CommandImpl for CPrint {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Print];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CFlush {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Flush];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CSortDevyear {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Sort, TokenType::DevyearInnerKeyword];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CAddp {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Add, TokenType::Procedure, TokenType::Logic, TokenType::Num];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CAddo {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Add, TokenType::Oop, TokenType::InhType, TokenType::Num];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelP {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::Procedure];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelO {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::Oop];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelIfDevyear {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::If, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelIfODevyear {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::If, TokenType::Oop, TokenType::Dot, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}
impl CommandImpl for CDelIfOInhtype {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::If, TokenType::Oop, TokenType::Dot, TokenType::InhtypeInnerKeyword, TokenType::Assign, TokenType::InhType];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelIfPDevyear {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::If, TokenType::Procedure, TokenType::Dot, TokenType::DevyearInnerKeyword, TokenType::Assign, TokenType::Num];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}

impl CommandImpl for CDelIfPAdt {
    fn compare_implementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::Del, TokenType::If, TokenType::Procedure, TokenType::Dot, TokenType::AdtInnerKeyword, TokenType::Assign, TokenType::Logic];
        Self::command_comparator(tokens, implementation.as_ref())
    }
}
