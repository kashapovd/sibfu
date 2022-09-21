use crate::cmd::{Command};
use crate::token::{Token, TokenType};

#[derive(Debug)]
pub struct Parser {
    input: Vec<Token>
}

impl Parser {
    pub fn new(input: Vec<Token>) -> Self {
        Self { input }
    }
    fn parse_print(&mut self) -> Result<Command, String> {
        let cmd = Command::new(&self.input);
        match cmd {
            Ok(cmd) => Ok(cmd),
            Err(err) => Err(format!("Unable to parse PRINT command. {err}"))
        }
    }
    fn parse_flush(&mut self) -> Result<Command, String> {
        let cmd = Command::new(&self.input);
        match cmd {
            Ok(cmd) => Ok(cmd),
            Err(err) => Err(format!("Unable to parse FLUSH command. {err}"))
        }
    }
    fn parse_sort(&mut self) -> Result<Command, String> {
        let cmd = Command::new(&self.input);
        match cmd {
            Ok(cmd) => Ok(cmd),
            Err(err) => Err(format!("Unable to parse SORT command. {err}"))
        }

    }
    fn parse_add(&mut self) -> Result<Command, String> {
        let cmd = Command::new(&self.input);
        match cmd {
            Ok(cmd) => Ok(cmd),
            Err(err) => Err(format!("Unable to parse ADD command. {err}"))
        }
    }
    fn parse_del(&mut self) -> Result<Command, String> {
        let cmd = Command::new(&self.input);
        match cmd {
            Ok(cmd) => Ok(cmd),
            Err(err) => Err(format!("Unable to parse DEL command. {err}"))
        }
    }
    pub fn parse(&mut self) -> Result<Command, String> {
        if !self.input.is_empty() {
            let token = self.input.get(0);
            match token.unwrap().ttype {
            TokenType::Print => {
                self.parse_print()
            },
            TokenType::Add => {
                self.parse_add()
            },
            TokenType::Del => {
                self.parse_del()
            }
            TokenType::Sort => {
                self.parse_sort()
            },
            TokenType::Flush => {
                self.parse_flush()
            },
            _ => Err(format!("Unknown keyword at {}", token.unwrap().start_pos))
        }
        } else {
            Err(format!("Source file cannot be empty"))
        }
    }
    
}