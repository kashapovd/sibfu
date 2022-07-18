function msg = decode_msg(emsg, code)
    alph = ['0':'9' 'A':'F'];
    msg = '';
    word = '';
    for c = emsg
        word(end + 1) = c;
        m = strcmp(code, word)
        if any(m)
            msg = [msg alph(m)];
            word = '';
        end
    end
end
