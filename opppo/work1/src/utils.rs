use crate::token::{Token, TokenType};

pub fn vec_token_to_vec_token_type(tokens: &Vec<Token>) -> Vec<TokenType> {
    let mut token_types: Vec<TokenType> = Vec::new();
    for t in tokens {
        token_types.push(t.get_type());
    }
    token_types
}