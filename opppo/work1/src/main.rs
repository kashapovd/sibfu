use crate::interpreter::Interpenter;
use std::{env, fs};

mod cmd;
mod entities;
mod interpreter;
mod lexer;
mod list;
mod parser;
mod token;
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
    source.trim();

    let mut i = Interpenter::new(source);
    i.execute();
}
