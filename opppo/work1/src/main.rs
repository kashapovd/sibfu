use std::{fs, env};

use parser::Parser;

use crate::{lexer::Lexer, interpreter::Interpenter};

mod lexer;
mod token;
mod interpreter;
mod list;
mod entities;
mod parser;
mod cmd;

fn main() {
    if env::args().nth(1).is_none() {
        panic!("Please, specify source file")
    }
    let f = env::args().nth(1).unwrap();
    let source = fs::read_to_string(f).unwrap();

    let mut i = Interpenter::new(source);
    i.execute();
}