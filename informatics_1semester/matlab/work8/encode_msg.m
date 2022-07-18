function emsg = encode_msg(msg, code)
    alph = ['0':'9' 'A':'F'];
    emsg = '';
    for c = msg
        emsg = [emsg code{c == alph}];
    end
end
