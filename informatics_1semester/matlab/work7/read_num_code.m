function n = read_num_code(s)
  if s(1)=='0'
    n = bin2dec(s);
  else
    n = -(2^length(s) - 1 - bin2dec(s));
  endif
end
