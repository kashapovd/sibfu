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
        while self.pos < self.content.len() {
            let c = self.content.get(self.pos);
            if c.is_some() {
                let c = c.unwrap();
                match c {
                    '=' | '.' => {
                        tokens.push(Token::new(&c.to_string(), self.pos));
                    }
                    _ if c.is_alphanumeric() => {
                        let (word_or_num, keyword_pos) = self.read_word_or_num();
                        tokens.push(Token::new(&word_or_num, keyword_pos));
                    }
                    _ => {}
                }
            }
            self.pos += 1;
        }
        tokens
    }
    fn read_word_or_num(&mut self) -> (String, usize) {
        let mut buff: String = String::new();
        let keyword_pos = self.pos;
        loop {
            let c = self.content.get(self.pos);
            if c.is_some() && c.unwrap().is_alphanumeric() {
                buff.push(*c.unwrap());
                self.pos += 1;
            }
            else {
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
        assert_eq!(tokens.get(0), Some(Token::new(&"ADD".to_string(), 0)).as_ref());
        assert_ne!(tokens.get(0), Some(Token::new(&"DOT".to_string(), 0)).as_ref());
    }
}