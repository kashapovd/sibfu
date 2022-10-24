use crate::entities::InheritanceType;

/// The set of all possible tokens 
#[derive(PartialEq)]
#[derive(Debug)]
#[derive(Copy, Clone)]
pub enum TokenType {
    Sort,
    Flush,
    Add,
    Print,
    Del,
    Assign,
    Dot,
    Num,
    Logic,
    If,
    Procedure,
    Oop,
    DevyearInnerKeyword,
    AdtInnerKeyword,
    InhtypeInnerKeyword,
    InhType,
    Invalid
}

/// Represents token object in program
#[derive(PartialEq)]
#[derive(Debug)]
pub struct Token {
    /// Contains token type
    pub ttype: TokenType,
    /// Token position in the input string
    pub start_pos: usize,
    /// A content of token
    pub content: String
}

impl Token {
    /// Contructs new token oject
    /// # Arguments
    /// * `token_symbol` - Contains Token content as string
    /// * `start_pos` - Token position in the input string
    /// # Returns
    /// New `Token` object
    pub fn new(token_symbol: &String, start_pos: usize) -> Self {
        Self {
            ttype: Self::type_by_str(token_symbol.to_owned()),
            start_pos,
            content: token_symbol.to_owned()
        }
    }
    /// Try to parse a token content as int value
    /// # Returns
    /// `Option` of `i32` value
    pub fn parse_content_as_int(&self) -> Option<i32> {
        match self.content.parse::<i32>() {
            Ok(int32) => Some(int32),
            Err(_) => None
        }
    }
    /// Try to parse a token content as boolean value
    /// # Returns
    /// `Option` of `bool` value
    pub fn parse_content_as_logic(&self) -> Option<bool> {
        match self.content.to_lowercase().as_str() {
            "t" => Some(true),
            "f" => Some(false),
            _ => None
        }
    }
    /// Try to parse a token content as `InheritanceType` enum 
    /// # Returns
    /// `Option` of `InheritanceType` value
    pub fn parse_content_inh_type(&self) -> Option<InheritanceType> {
        match self.content.to_ascii_lowercase().as_str() {
            "single" => Some(InheritanceType::Single),
            "multiple" => Some(InheritanceType::Multiple),
            "interface" => Some(InheritanceType::Interface),
            _ => None
        }
    }
    /// Returns a token type
    /// # Returns
    /// `TokenType` enum value
    pub fn get_type(&self) -> TokenType {
        self.ttype
    }
    /// Reconizes token type from a given string
    /// # Returns
    /// `TokenType` enum value
    fn type_by_str(token: String) -> TokenType {
        match token.to_ascii_lowercase().as_str() {
            "=" => TokenType::Assign,
            "." => TokenType::Dot,
            "add" => TokenType::Add,
            "sort" => TokenType::Sort,
            "flush" => TokenType::Flush,
            "del" => TokenType::Del,
            "print" => TokenType::Print,
            "if" => TokenType::If,
            "t" => TokenType::Logic,
            "f" => TokenType::Logic,
            "procedure" => TokenType::Procedure,
            "oop" => TokenType::Oop,
            "devyear" => TokenType::DevyearInnerKeyword,
            "adt" => TokenType::AdtInnerKeyword,
            "inhtype" => TokenType::InhtypeInnerKeyword,
            "single" => TokenType::InhType,
            "multiple" => TokenType::InhType,
            "interface" => TokenType::InhType,
            _ if token.parse::<i32>().is_ok() => TokenType::Num,
            _ => TokenType::Invalid
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn token_creation() {
        let t = Token::new(&"ADD".to_string(), 0);
        assert_eq!(t.ttype, TokenType::Add);
        assert_eq!(t.start_pos, 0);
    }
    #[test]
    fn type_parsing_dot() {
        let c = '.';
        let t = Token::new(&c.to_string(), 0);
        assert_eq!(t.ttype, TokenType::Dot);
    }
    #[test]
    fn type_parsing_num() {
        let c = String::from("1998");
        let t = Token::new(&c, 0);
        assert_eq!(t.ttype, TokenType::Num);
        assert_eq!(t.content, "1998".to_string());
        assert_eq!(Some(1998), t.parse_content_as_int());
    }
    #[test]
    fn type_parsing_float_invalid() {
        let c = String::from("0.8");
        let t = Token::new(&c, 0);
        assert_eq!(t.ttype, TokenType::Invalid);
    }
    #[test]
    fn type_parsing_invalid() {
        let c = String::from("#$%^&*");
        let t = Token::new(&c, 0);
        assert_eq!(t.ttype, TokenType::Invalid);
    }
}