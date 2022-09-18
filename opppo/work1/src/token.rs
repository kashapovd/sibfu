#[derive(PartialEq)]
#[derive(Debug)]
pub enum TokenType {
    SORT,
    FLUSH,
    ADD,
    PRINT,
    DEL,
    ASSIGN,
    DOT,
    NUM(i32),
    TRUE,
    FALSE,
    IF,
    PRODCEDURE,
    OOP,
    DEVYEAR_INNER_KEYWORD,
    ADT_INNER_KEYWORD,
    INHTYPE_INNER_KEYWORD,
    INHTYPE_SINGLE,
    INHTYPE_MULTIPLE,
    INHTYPE_INTERFACE,
    EOF,
    INVALID
}

#[derive(PartialEq)]
#[derive(Debug)]
pub struct Token {
    ttype: TokenType,
    startPos: usize
}

impl Token {
    pub fn new(ttype: TokenType, startPos: usize ) -> Self {
        Self {
            ttype,
            startPos
        }
    }
    pub fn typeByStr(token: String) -> TokenType {
        match token.to_ascii_lowercase().as_str() {
            "=" => TokenType::ASSIGN,
            "." => TokenType::DOT,
            "add" => TokenType::ADD,
            "sort" => TokenType::SORT,
            "flush" => TokenType::FLUSH,
            "del" => TokenType::DEL,
            "print" => TokenType::PRINT,
            "if" => TokenType::IF,
            "t" => TokenType::TRUE,
            "f" => TokenType::FALSE,
            "procedure" => TokenType::PRODCEDURE,
            "oop" => TokenType::OOP,
            "devyear" => TokenType::DEVYEAR_INNER_KEYWORD,
            "adt" => TokenType::ADT_INNER_KEYWORD,
            "inhtype" => TokenType::INHTYPE_INNER_KEYWORD,
            "single" => TokenType::INHTYPE_SINGLE,
            "multiple" => TokenType::INHTYPE_MULTIPLE,
            "intefrace" => TokenType::INHTYPE_INTERFACE,
            _ if token.parse::<i32>().is_ok() => {TokenType::NUM(token.parse::<i32>().unwrap())},
            _ => TokenType::INVALID
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn token_creation() {
        let t = Token::new(TokenType::ADD, 2);
        assert_eq!(t.ttype, TokenType::ADD);
        assert_eq!(t.startPos, 2);
    }
    #[test]
    fn type_parsing_dot() {
        let c = '.';
        let t = Token::new(Token::typeByStr(c.to_string()), 0);
        assert_eq!(t.ttype, TokenType::DOT);
    }
    #[test]
    fn type_parsing_num() {
        let c = String::from("1998");
        let t = Token::new(Token::typeByStr(c), 0);
        assert_eq!(t.ttype, TokenType::NUM(1998));
    }
    #[test]
    fn type_parsing_float() {
        let c = String::from("0.8");
        let t = Token::new(Token::typeByStr(c), 0);
        assert_eq!(t.ttype, TokenType::INVALID);
    }
    #[test]
    fn type_parsing_invalid() {
        let c = String::from("#$%^&*");
        let t = Token::new(Token::typeByStr(c), 0);
        assert_eq!(t.ttype, TokenType::INVALID);
    }
}