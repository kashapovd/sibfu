use crate::{
    entities::Language,
    token::{Token, TokenType},
};

/// Transorm vector of token to vector of token types  
/// # Arguments
/// * `tokens` - Input vector of token to transform
/// # Returns
///   Vector of token types
pub fn vec_token_to_vec_token_type(tokens: &Vec<Token>) -> Vec<TokenType> {
    let mut token_types: Vec<TokenType> = Vec::new();
    for t in tokens {
        token_types.push(t.get_type());
    }
    token_types
}

/// Implements method `pop_front` for vector which doesn't support it  
/// # Arguments
/// * `vec` - Input vector to pop from front
/// # Returns
///   The value that was popped
pub fn pop_front_vec(mut vec: &mut Vec<Box<dyn Language>>) -> Option<Box<dyn Language>> {
    match vec.get(0) {
        Some(_) => Some(vec.remove(0)),
        None => None,
    }
}
