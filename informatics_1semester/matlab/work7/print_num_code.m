function s = print_num_code(n, len)
  if num2str(n)(1) == '-'
    n = 2^len - 1 + n;
    s = dec2bin(n, len);
  else
    s = dec2bin(n, len);
  endif
end