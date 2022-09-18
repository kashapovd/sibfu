use crate::token::Token;

#[derive(Debug)]
pub struct Lexer {
    content: Vec<char>,
    pos: usize
}

impl Lexer {
    pub fn new(content: String) -> Self {
        Self {
            content: content.chars().collect(),
            pos: 0
        }
    }
    pub fn tokenizator(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = Vec::new();
        while self.content.len() > self.pos {
            match self.current_char() {
                '=' | '.' => {
                    tokens.push(Token::new(Token::typeByStr(self.current_char().to_string()), self.pos));
                    self.pos += 1;
                }
                _ if self.current_char().is_alphabetic() => {
                    let mut buff: String = String::new();
                    let keyword_pos = self.pos;
                    while self.current_char().is_alphabetic() {
                        buff.push(self.current_char());
                        self.pos += 1;
                    }
                    tokens.push(Token::new(Token::typeByStr(buff), keyword_pos));
                }
                _ if self.current_char().is_numeric() => {
                    let mut buff: String = String::new();
                    let keyword_pos = self.pos;
                    while self.current_char().is_numeric() {
                        buff.push(self.current_char());
                        self.pos += 1;
                    };
                    tokens.push(Token::new(Token::typeByStr(buff), keyword_pos));
                }
                _ => {
                    self.pos += 1;
                }
            }
        }
        println!("{:?}", tokens);
        tokens
    }
    fn current_char(&self) -> char {
        *self.content.get(self.pos).unwrap()
    }
}

#[cfg(test)]
mod test {
    use crate::token::{TokenType, Token};

    use super::Lexer;
    #[test]
    fn lexer_creation() {
        let l = Lexer::new("ADD".to_string());
        let s: String = l.content.into_iter().collect();
        assert_eq!(s, "ADD")
    }
    #[test]
    fn lexer_tokenization() {
        let mut l = Lexer::new("ADD\n".to_string());
        let tokens = l.tokenizator();
        assert_eq!(tokens.len(), 1);
        assert_eq!(tokens.get(0), Some(Token::new(TokenType::ADD, 0)).as_ref());
        assert_ne!(tokens.get(0), Some(Token::new(TokenType::DOT, 0)).as_ref());
    }
}