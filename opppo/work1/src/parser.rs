use crate::cmd::Command;
use crate::token::Token;

#[derive(Debug)]
pub struct Parser {
    input: Vec<Token>
}

impl Parser {
    pub fn new(input: Vec<Token>) -> Self {
        Self { input }
    }
    pub fn parse(&mut self) -> Result<Command, String> {
        if !self.input.is_empty() {
            let token = self.input.get(0);
            match token {
                Some(_token) => {
                    let cmd = Command::new(&self.input);
                    match cmd {
                        Ok(cmd) => Ok(cmd),
                        Err(err) => Err(err)
                    }
                } 
                _ => {
                    Err(format!("Unexpected error while unpacking a token stream in parser"))
                }     
            }  
        } else {
            Err(format!("Source file cannot be empty"))
        }
    }    
}

#[cfg(test)]
mod test {
    use super::*;
}