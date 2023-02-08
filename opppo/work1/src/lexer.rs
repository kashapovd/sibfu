use crate::token::Token;

/// Represents lexer object in the program
#[derive(Debug)]
pub struct Lexer {
    /// Contains vector of input chars
    content: Vec<char>,
    /// Contains current position that points to char
    pos: usize,
}

impl Lexer {
    /// Contructs new `Lexer` object from a given string
    /// # Arguments
    /// * `content` - Contains input string to lex
    /// # Returns
    /// New `Lexer` object
    pub fn new(content: String) -> Self {
        Self {
            content: content.chars().collect(),
            pos: 0,
        }
    }
    /// Process input string and creates tokens from
    /// # Returns
    /// Vector of `Token` objects
    pub fn tokenizator(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = Vec::new();
        while self.pos < self.content.len() {
            let c = self.content.get(self.pos);
            if c.is_some() {
                let c = c.unwrap();
                match c {
                    ' ' => {}
                    _ if c.is_ascii_control() => {}
                    _ if c.is_alphanumeric() => {
                        let (word_or_num, keyword_pos) = self.read_word_or_num();
                        tokens.push(Token::new(&word_or_num, keyword_pos));
                    }
                    _ => {
                        tokens.push(Token::new(&c.to_string(), self.pos));
                    }
                }
            }
            self.pos += 1;
        }
        tokens
    }
    /// Tries to read a given char subset as word or number\
    /// # Returns
    /// Tuple of result `String` and its start position in the input
    fn read_word_or_num(&mut self) -> (String, usize) {
        let mut buff: String = String::new();
        let keyword_pos = self.pos;
        buff.push(*self.content.get(self.pos).unwrap());
        loop {
            self.pos += 1;
            let c = self.content.get(self.pos);
            if c.is_some() && c.unwrap().is_alphanumeric() {
                buff.push(*c.unwrap());
            } else {
                self.pos -= 1;
                break;
            }
        }
        (buff, keyword_pos)
    }
}

#[cfg(test)]
mod test {
    use crate::token::Token;

    use super::Lexer;
    #[test]
    fn creation() {
        let l = Lexer::new("ADD".to_string());
        let s: String = l.content.into_iter().collect();
        assert_eq!(s, "ADD")
    }
    #[test]
    fn tokenization() {
        let mut l = Lexer::new("ADD".to_string());
        let tokens = l.tokenizator();
        assert_eq!(tokens.len(), 1);
        assert_eq!(
            tokens.get(0),
            Some(Token::new(&"ADD".to_string(), 0)).as_ref()
        );
        assert_ne!(
            tokens.get(0),
            Some(Token::new(&"DOT".to_string(), 0)).as_ref()
        );
    }
    #[test]
    fn tokenization_with_control_symbols() {
        let mut l = Lexer::new("\n\t\t\tADD\t\t\t".to_string());
        let tokens = l.tokenizator();
        assert_eq!(tokens.len(), 1);
        assert_eq!(
            tokens.get(0),
            Some(Token::new(&"ADD".to_string(), 4)).as_ref()
        );
        assert_ne!(
            tokens.get(0),
            Some(Token::new(&"\nADD".to_string(), 4)).as_ref()
        );
    }
}
