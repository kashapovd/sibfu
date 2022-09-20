use crate::{entities::InheritanceType, token::{TokenType, Token}};

#[derive(Debug)]
pub enum CmdType {
    ADDP(bool, i32),
    ADDO(InheritanceType, i32),
    DEL_P,
    DEL_O,
    DEL_IF_DEVAYER(i32),
    DEL_IF_P_DEVYEAR(i32),
    DEL_IF_O_DEVYEAR(i32),
    DEL_IF_P_ADT(bool),
    DEL_IF_O_INHTYPE(InheritanceType),
    SORT_DEVYEAR,
    PRINT,
    FLUSH,
    INVALID
}

#[derive(Debug)]
pub struct Command {
    pub ctype: CmdType
}

impl Command {
    pub fn new(tokens: &Vec<Token>) -> Result<Self, String> {
        let ctype = Self::matchCommandTypeByToken(tokens);
        match ctype {
            Ok(t) => Ok(Self { ctype: t }),
            Err(err) => Err(err)
        }
    }
    fn matchCommandTypeByToken(tokens: &Vec<Token>) -> Result<CmdType, String> {
        let first_token = tokens.get(0).unwrap();
        match first_token.ttype {
            TokenType::PRINT => {
                match C_PRINT::compImplementation(tokens.as_ref()) {
                    Ok(is_correct_cmd) => Ok(CmdType::PRINT),
                    Err(err) => Err(err)
                }
            }
            _ => {
                todo!()
            }
            
        }
    }
}

trait CommandImpl {
    fn compImplementation(tokens: &Vec<Token>) -> Result<bool, String>;
}

struct C_ADDP {
    pub ctype: CmdType,
    implementation: Vec<TokenType>
}

struct C_ADDO {
    pub ctype: CmdType
}

struct C_DEL_P {
    pub ctype: CmdType
}

struct C_DEL_O {
    pub ctype: CmdType
}
struct C_DEL_IF_DEVAYER {
    pub ctype: CmdType
}

struct C_DEL_IF_P_DEVYEAR {
    pub ctype: CmdType
}
struct C_DEL_IF_O_DEVYEAR {
    pub ctype: CmdType
}

struct C_DEL_IF_P_ADT {
    pub ctype: CmdType
}
struct C_DEL_IF_O_INHTYPE {
    pub ctype: CmdType
}

struct C_SORT_DEVYEAR {
    pub ctype: CmdType
}

struct C_PRINT {
    pub ctype: CmdType
}

struct C_SORT {
    pub ctype: CmdType
}

struct C_FLUSH {
    pub ctype: CmdType
}

impl CommandImpl for C_PRINT {
    fn compImplementation(tokens: &Vec<Token>) -> Result<bool, String> {
        let implementation = vec![TokenType::PRINT];

        if tokens.len() == implementation.len() {
            for i in 0..tokens.len() {
                if tokens.get(0).unwrap().ttype != *implementation.get(0).unwrap() {
                    return Err(format!("Unknown parameter at {}", tokens.get(0).unwrap().startPos));
                }
            }
        } else {
            return Err(format!("Command PRINT doesn't have parameters"));
        }
        Ok(true)
    }
}
