use crate::cmd::Command;
use crate::token::Token;

/// Represents parser object in the program
#[derive(Debug)]
pub struct Parser {
    /// Vector of tokens to parse
    input: Vec<Token>
}


impl Parser {
    /// Contructs new parser object from a given vector of tokens
    /// # Arguments
    /// * `input` - Contains vector of `Token`
    /// # Returns
    /// New `Parser` object
    pub fn new(input: Vec<Token>) -> Self {
        Self { input }
    }
    /// Tries to parse tokens
    /// # Returns
    /// `Result` object with valid value or error string
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