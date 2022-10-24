use std::{fs, env};
use crate::interpreter::Interpenter;

mod lexer;
mod token;
mod interpreter;
mod list;
mod entities;
mod parser;
mod cmd;
mod utils;

/// program entry point. Opens files and creates `Interpenter` object
fn main() {
    if env::args().nth(1).is_none() {
        panic!("Please, specify source file");
    }
    let file = env::args().nth(1).unwrap();
    let file_metadata = fs::metadata(&file);
    assert!(file_metadata.unwrap().is_file());
    let source = fs::read_to_string(file).unwrap();
    if source.is_empty() {
        panic!("Source file cannot be empty")
    }

    let mut i = Interpenter::new(source);
    i.execute();
}