var searchIndex = JSON.parse('{\
"work1":{"doc":"","t":[0,0,0,0,0,5,0,0,0,13,13,4,3,13,13,13,13,13,13,13,13,13,13,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,4,13,8,4,13,13,3,13,3,13,12,11,11,11,11,11,11,11,11,11,11,11,12,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,10,11,11,10,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,3,11,11,11,11,12,11,12,11,11,11,11,3,11,11,12,11,11,11,11,12,11,11,11,11,11,12,3,3,3,6,3,3,11,11,11,11,11,11,11,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,12,12,11,11,11,11,12,12,12,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,3,11,11,11,11,12,11,11,11,11,11,11,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,3,4,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,11,11,11,11,11,12,11,11,11,5,5],"n":["cmd","entities","interpreter","lexer","list","main","parser","token","utils","AddO","AddP","CmdType","Command","DelIfDevyear","DelIfODevyear","DelIfOInhtype","DelIfPAdt","DelIfPDevyear","DelO","DelP","Flush","Print","SortDevyear","borrow","borrow","borrow_mut","borrow_mut","clone","clone_into","ctype","fmt","fmt","from","from","get_type","into","into","match_command_type_by_token","new","to_owned","try_from","try_from","try_into","try_into","type_id","type_id","0","0","0","0","0","0","0","1","1","InheritanceType","Interface","Language","LanguageType","Multiple","Oop","OopLang","Procedure","ProcedureLang","Single","abstract_data_types","borrow","borrow","borrow","borrow","borrow_mut","borrow_mut","borrow_mut","borrow_mut","clone","clone_into","cmp","dev_year","dev_year","eq","eq","eq","eq","eq","fmt","fmt","fmt","fmt","fmt","fmt","fmt","fmt","from","from","from","from","get_devyear","get_devyear","get_devyear","get_type","get_type","get_type","inh_type","into","into","into","into","ne","ne","ne","new","new","partial_cmp","partial_cmp","partial_cmp","partial_cmp","to_owned","to_string","to_string","try_from","try_from","try_from","try_from","try_into","try_into","try_into","try_into","type_id","type_id","type_id","type_id","0","0","Interpenter","borrow","borrow_mut","execute","from","input","into","lang_list","new","try_from","try_into","type_id","Lexer","borrow","borrow_mut","content","fmt","from","into","new","pos","read_word_or_num","tokenizator","try_from","try_into","type_id","0","IntoIter","Iter","IterMut","Link","Node","Slist","borrow","borrow","borrow","borrow","borrow","borrow_mut","borrow_mut","borrow_mut","borrow_mut","borrow_mut","clean","delete","drop","elem","fmt","fmt","fmt","fmt","from","from","from","from","from","head","into","into","into","into","into","into_iter","into_iter","into_iter","iter","iter_mut","len","len","len","new","next","next","next","next","next","next","peek","pop","push","sort","tail","to_string","to_string","try_from","try_from","try_from","try_from","try_from","try_into","try_into","try_into","try_into","try_into","type_id","type_id","type_id","type_id","type_id","Parser","borrow","borrow_mut","fmt","from","input","into","new","parse","try_from","try_into","type_id","Add","AdtInnerKeyword","Assign","Del","DevyearInnerKeyword","Dot","Flush","If","InhType","InhtypeInnerKeyword","Invalid","Logic","Num","Oop","Print","Procedure","Sort","Token","TokenType","borrow","borrow","borrow_mut","borrow_mut","clone","clone_into","content","eq","eq","fmt","fmt","from","from","get_type","into","into","ne","new","parse_content_as_int","parse_content_as_logic","parse_content_inh_type","start_pos","to_owned","try_from","try_from","try_into","try_into","ttype","type_by_str","type_id","type_id","pop_front_vec","vec_token_to_vec_token_type"],"q":["work1","","","","","","","","","work1::cmd","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","work1::cmd::CmdType","","","","","","","","","work1::entities","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","work1::entities::LanguageType","","work1::interpreter","","","","","","","","","","","","work1::lexer","","","","","","","","","","","","","","work1::list","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","work1::parser","","","","","","","","","","","","work1::token","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","work1::utils",""],"d":["","","","","","program entry point. Opens files and creates <code>Interpenter</code> …","","","","","","","Represents command object in program","","","","","","","","","","","","","","","","","","","","Returns the argument unchanged.","Returns the argument unchanged.","Returns a type of command","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Matches command type from a given tokens subset","Contructs new <code>Command</code> object from a given tokens by …","","","","","","","","","","","","","","","","","","","Represents Language object in program as trait","","","","Represents Object Oriented Language object in program","","Represents Procedure Language object in program","","","","","","","","","","","","","","","","","","","","","","","","","","","","","Returns the argument unchanged.","Returns the argument unchanged.","Returns the argument unchanged.","Returns the argument unchanged.","","","","","","","","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","","","","Contructs new <code>OopLang</code> object from a given string","Contructs new <code>ProcedureLang</code> object from a given string","","","","","","","","","","","","","","","","","","","","","","Represents interpenter object in the program","","","Executes a given input","Returns the argument unchanged.","Input commands as string","Calls <code>U::from(self)</code>.","List to be processed with commands","Contructs new <code>Interpenter</code> object from a given string","","","","Represents lexer object in the program","","","Contains vector of input chars","","Returns the argument unchanged.","Calls <code>U::from(self)</code>.","Contructs new <code>Lexer</code> object from a given string","Contains current position that points to char","Tries to read a given char subset as word or number","Process input string and creates tokens from","","","","","","Represents iterator for linked list","Represents iterator for linked list","","Represents the member of linked list ","Represents circular syngly-linked list in the program","","","","","","","","","","","Performs list cleanup by correct termination of objects","Performs unsafe delete of membere at given index ","","Contains the value of <code>Language</code> trait  ","","","","","Returns the argument unchanged.","Returns the argument unchanged.","Returns the argument unchanged.","Returns the argument unchanged.","Returns the argument unchanged.","Points to a head of the list","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","","","","Implements unsafe iterator wrapper for <code>Slist</code>","Implements unsafe iterator wrapper for <code>Slist</code>","Returns a size of the list","Contorl maximum of iterations because of list circularity","Contains current size of the list ","Constructs new object of <code>Slist</code>","","","","","","Points to the next member","Returns first value of list  ","Performs unsafe delete a first member of the list","Performs unsafe push a new value to the list","Performs sorting of list. Uses vector as transition state …","Points to a tail of the list","","","","","","","","","","","","","","","","","","Represents parser object in the program","","","","Returns the argument unchanged.","Vector of tokens to parse","Calls <code>U::from(self)</code>.","Contructs new parser object from a given vector of tokens","Tries to parse tokens","","","","","","","","","","","","","","","","","","","","","Represents token object in program","The set of all possible tokens ","","","","","","","A content of token","","","","","Returns the argument unchanged.","Returns the argument unchanged.","Returns a token type","Calls <code>U::from(self)</code>.","Calls <code>U::from(self)</code>.","","Contructs new token oject","Try to parse a token content as int value","Try to parse a token content as boolean value","Try to parse a token content as <code>InheritanceType</code> enum ","Token position in the input string","","","","","","Contains token type","Reconizes token type from a given string","","","Implements method <code>pop_front</code> for vector which doesn’t …","Transorm vector of token to vector of token types"],"i":[0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,1,2,1,2,1,2,2,1,2,2,2,1,1,2,1,2,1,2,3,4,5,6,7,8,9,3,4,0,10,0,0,10,11,0,11,0,10,12,10,11,13,12,10,11,13,12,10,10,14,13,12,14,10,11,13,12,14,14,10,10,11,11,13,12,10,11,13,12,14,13,12,14,13,12,13,10,11,13,12,11,13,12,13,12,14,10,13,12,10,10,11,10,11,13,12,10,11,13,12,10,11,13,12,15,16,0,17,17,17,17,17,17,17,17,17,17,17,0,18,18,18,18,18,18,18,18,18,18,18,18,18,19,0,0,0,0,0,0,19,20,21,22,23,19,20,21,22,23,22,22,22,23,22,22,23,23,19,20,21,22,23,22,19,20,21,22,23,19,20,21,22,22,22,20,22,22,19,20,21,20,21,23,22,22,22,22,22,22,23,19,20,21,22,23,19,20,21,22,23,19,20,21,22,23,0,24,24,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,0,0,25,26,25,26,25,25,26,25,26,25,26,25,26,26,25,26,26,26,26,26,26,26,25,25,26,25,26,26,26,25,26,0,0],"f":[null,null,null,null,null,[[],["result",6]],null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["cmdtype",4]],["cmdtype",4]],[[["",0],["",0]]],null,[[["cmdtype",4],["formatter",3]],["result",6]],[[["command",3],["formatter",3]],["result",6]],[[]],[[]],[[["command",3]],["cmdtype",4]],[[]],[[]],[[["vec",3]],["result",4,[["cmdtype",4],["string",3]]]],[[["vec",3]],["result",4,[["command",3],["string",3]]]],[[["",0]]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["inheritancetype",4]],["inheritancetype",4]],[[["",0],["",0]]],[[["language",8],["language",8]],["ordering",4]],null,null,[[["language",8],["language",8]],["bool",0]],[[["inheritancetype",4],["inheritancetype",4]],["bool",0]],[[["languagetype",4],["languagetype",4]],["bool",0]],[[["ooplang",3],["ooplang",3]],["bool",0]],[[["procedurelang",3],["procedurelang",3]],["bool",0]],[[["language",8],["formatter",3]],["result",6]],[[["language",8],["formatter",3]],["result",6]],[[["inheritancetype",4],["formatter",3]],["result",6]],[[["inheritancetype",4],["formatter",3]],["result",6]],[[["languagetype",4],["formatter",3]],["result",6]],[[["languagetype",4],["formatter",3]],["result",6]],[[["ooplang",3],["formatter",3]],["result",6]],[[["procedurelang",3],["formatter",3]],["result",6]],[[]],[[]],[[]],[[]],[[["",0]],["i32",0]],[[["ooplang",3]],["i32",0]],[[["procedurelang",3]],["i32",0]],[[["",0]],["languagetype",4]],[[["ooplang",3]],["languagetype",4]],[[["procedurelang",3]],["languagetype",4]],null,[[]],[[]],[[]],[[]],[[["languagetype",4],["languagetype",4]],["bool",0]],[[["ooplang",3],["ooplang",3]],["bool",0]],[[["procedurelang",3],["procedurelang",3]],["bool",0]],[[["inheritancetype",4],["i32",0]],["ooplang",3]],[[["bool",0],["i32",0]],["procedurelang",3]],[[["language",8],["language",8]],["option",4,[["ordering",4]]]],[[["inheritancetype",4],["inheritancetype",4]],["option",4,[["ordering",4]]]],[[["ooplang",3],["ooplang",3]],["option",4,[["ordering",4]]]],[[["procedurelang",3],["procedurelang",3]],["option",4,[["ordering",4]]]],[[["",0]]],[[["",0]],["string",3]],[[["",0]],["string",3]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],null,null,null,[[["",0]],["",0]],[[["",0]],["",0]],[[["interpenter",3]],["result",4,[["string",3],["string",3]]]],[[]],null,[[]],null,[[["string",3]],["interpenter",3]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],null,[[["",0]],["",0]],[[["",0]],["",0]],null,[[["lexer",3],["formatter",3]],["result",6]],[[]],[[]],[[["string",3]],["lexer",3]],null,[[["lexer",3]]],[[["lexer",3]],["vec",3,[["token",3]]]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],null,null,null,null,null,null,null,[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["slist",3]]],[[["slist",3],["usize",0]]],[[["slist",3]]],null,[[["slist",3],["formatter",3]],["result",6]],[[["slist",3],["formatter",3]],["result",6]],[[["node",3],["formatter",3]],["result",6]],[[["node",3],["formatter",3]],["result",6]],[[]],[[]],[[]],[[]],[[]],null,[[]],[[]],[[]],[[]],[[]],[[]],[[]],[[]],[[["slist",3]],["iter",3]],[[["slist",3]],["itermut",3]],[[["slist",3]],["usize",0]],null,null,[[],["slist",3]],[[["intoiter",3]],["option",4]],[[["iter",3]],["option",4]],[[["itermut",3]],["option",4]],null,null,null,[[["slist",3]],["option",4,[["box",3]]]],[[["slist",3]],["option",4,[["box",3,[["language",8]]]]]],[[["slist",3],["box",3,[["language",8]]]]],[[["slist",3]]],null,[[["",0]],["string",3]],[[["",0]],["string",3]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],null,[[["",0]],["",0]],[[["",0]],["",0]],[[["parser",3],["formatter",3]],["result",6]],[[]],null,[[]],[[["vec",3,[["token",3]]]],["parser",3]],[[["parser",3]],["result",4,[["command",3],["string",3]]]],[[],["result",4]],[[],["result",4]],[[["",0]],["typeid",3]],null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["",0]],["",0]],[[["tokentype",4]],["tokentype",4]],[[["",0],["",0]]],null,[[["tokentype",4],["tokentype",4]],["bool",0]],[[["token",3],["token",3]],["bool",0]],[[["tokentype",4],["formatter",3]],["result",6]],[[["token",3],["formatter",3]],["result",6]],[[]],[[]],[[["token",3]],["tokentype",4]],[[]],[[]],[[["token",3],["token",3]],["bool",0]],[[["string",3],["usize",0]],["token",3]],[[["token",3]],["option",4,[["i32",0]]]],[[["token",3]],["option",4,[["bool",0]]]],[[["token",3]],["option",4,[["inheritancetype",4]]]],null,[[["",0]]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],null,[[["string",3]],["tokentype",4]],[[["",0]],["typeid",3]],[[["",0]],["typeid",3]],[[["vec",3]],["option",4,[["box",3,[["language",8]]]]]],[[["vec",3]],["vec",3,[["tokentype",4]]]]],"p":[[4,"CmdType"],[3,"Command"],[13,"AddP"],[13,"AddO"],[13,"DelIfDevyear"],[13,"DelIfPDevyear"],[13,"DelIfODevyear"],[13,"DelIfPAdt"],[13,"DelIfOInhtype"],[4,"InheritanceType"],[4,"LanguageType"],[3,"ProcedureLang"],[3,"OopLang"],[8,"Language"],[13,"Procedure"],[13,"Oop"],[3,"Interpenter"],[3,"Lexer"],[3,"IntoIter"],[3,"Iter"],[3,"IterMut"],[3,"Slist"],[3,"Node"],[3,"Parser"],[4,"TokenType"],[3,"Token"]]}\
}');
if (typeof window !== 'undefined' && window.initSearch) {window.initSearch(searchIndex)};
if (typeof exports !== 'undefined') {exports.searchIndex = searchIndex};