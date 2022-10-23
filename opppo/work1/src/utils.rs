use crate::{token::{Token, TokenType}, entities::Language};

pub fn vec_token_to_vec_token_type(tokens: &Vec<Token>) -> Vec<TokenType> {
    let mut token_types: Vec<TokenType> = Vec::new();
    for t in tokens {
        token_types.push(t.get_type());
    }
    token_types
}

pub fn pop_front_vec(mut vec: &mut Vec<Box<dyn Language>>) -> Option<Box<dyn Language>> {
    match vec.get(0) {
        Some(_) => {
            Some(vec.remove(0))
        },
        None => None,
    }
}