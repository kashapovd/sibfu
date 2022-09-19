use crate::entities::InheritanceType;
use crate::token::{Token, TokenType};

#[derive(Debug)]
pub enum Command {
    ADDP(bool, i32),
    ADDO(InheritanceType, i32),
    DEL_P,
    DEL_O,
    DEL_IF_DEVAYER(i32),
    DEL_IF_P_DEVYEAR(i32),
    DEL_IF_O_DEVYEAR(i32),
    DEL_IF_P_ADT(bool),
    DEL_IF_O_INHTYPE(InheritanceType),
    SORT_DEVYEAR,
    PRINT,
    FLUSH,
}

#[derive(Debug)]
pub struct Parser {
    input: Vec<Token>,
    pos: u32
}

impl Parser {
    pub fn new(input: Vec<Token>) -> Self {
        Self {
            input,
            pos: 0
        }
    }
    fn parse_print(&mut self) -> Result<Command, String> {
        self.input.remove(0);
        if self.input.len() != 0 {
            Err(format!("Command PRINT doesn't have parameters. Unknown keyword at {}", self.input.get(0).unwrap().startPos))
        } else {
            Ok(Command::PRINT)
        }
    }
    fn parse_flush(&mut self) -> Result<Command, String> {
        self.input.remove(0);
        if !self.input.is_empty() {
            Err(format!("Command FLUSH doesn't have parameters. Unknown keyword at {}", self.input.get(0).unwrap().startPos))
        } else {
            Ok(Command::FLUSH)
        }
    }
    fn parse_sort(&mut self) -> Result<Command, String> {
        self.input.remove(0);
        if self.input.is_empty() {
            Err(format!("Please, specify field for sorting"))
        } else {
            let token_field = self.input.get(0).unwrap();
            match token_field.ttype {
                TokenType::DEVYEAR_INNER_KEYWORD => {
                    Ok(Command::SORT_DEVYEAR)
                }
                _ => {
                    Err(format!("Sort by unknown field at {}", token_field.startPos))
                }
            }
        }
    }
    pub fn parse(&mut self) -> Result<Command, String> {
        if !self.input.is_empty() {
            let token = self.input.get(0);
            match token.unwrap().ttype {
            TokenType::PRINT => {
                self.parse_print()
            },
            // TokenType::ADD => {
            //     parse_add()
            // },
            // TokenType::DEL => {
            //     parseDEL()
            // }
            TokenType::SORT => {
                self.parse_sort()
            },
            TokenType::FLUSH => {
                self.parse_flush()
            },
            _ => Err(format!("Unknown keyword at {}", token.unwrap().startPos))
        }
        } else {
            Err(format!("Source file cannot be empty"))
        }
        
        
    }
    
}