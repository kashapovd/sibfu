use crate::token::{Token, TokenType};

pub fn vecTokenToVecTokenType(tokens: &Vec<Token>) -> Vec<TokenType> {
    let mut tokenTypes: Vec<TokenType> = Vec::new();
    for t in tokens {
        tokenTypes.push(t.get_type());
    }
    tokenTypes
}