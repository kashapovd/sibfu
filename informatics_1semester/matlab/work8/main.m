rand('state', 38);
r = rand(1, 16);
alph = ['0':'9' 'A':'F'];
hex = r/sum(r);
save -ascii hex.txt hex;

code = {'1110' '0110' '001' '101010' '000' '11111' '1101' '101011' '11110' '11000' '11001' '010' '0111' '100' '1011' '10100'};
dlmwrite('code.txt', char(code), '');

for i = 1:100
    msg = gen_msg(hex, 100);
    emsg = encode_msg(msg, code);
    dmsg = decode_msg(emsg, code);
    if !isequal(msg, dmsg)
        error("Декодированное сообщение(%s) отличается от исходного(%s)" , dmsg, msg);
    endif
endfor

l_min = alph_entropy(hex);
l_avg = avg_len(code, hex);
k = l_min/l_avg;

results = [
  l_avg;
  l_min;
  min_bits(length(hex)); 
  k
];
save -ascii results.txt results;