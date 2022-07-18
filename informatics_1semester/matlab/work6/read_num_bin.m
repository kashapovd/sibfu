function n = read_num_bin(s)
    neg = false;
    if s(1) == '-'
      s = s(2:end);
      neg = true;
    endif
    
    dot_pos = find(s=='.');
    s_int = s(1:dot_pos-1);
    s_frac = s(dot_pos+1:end);
    n = to_dec(s_int) + to_dec(s_frac) / 2^length(s_frac);
    
    if neg
      n = -n;
    endif 
endfunction

function dec = to_dec(s)
  dec = 0;
  for c = s
    dec = dec * 2 + str2num(c);
  endfor
endfunction
