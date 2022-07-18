function s = print_num_bin(n, prec)
  s_frac = '';
  s_int = '';
  s_zero = '';
  
  % Переводим целую и дробную часть числа
  n = round(n * 2^prec) / 2^prec;
  s_int = to_bin(fix(abs(n)));
  s_frac = to_bin(mod(abs(n), 1) * 2^prec);

  % Объединяем результаты
  s_zero(1:prec-length(s_frac)) = '0';
  s = [s_int '.' s_zero s_frac];
  
  % Если начальное число отрицательное - "меняем" знак
  if n < 0
    s = ['-' s];
  endif
endfunction

function bin = to_bin(dec)
  bin = '';
  do
    bin = [num2str(mod(dec, 2)) bin];
    dec = fix(dec / 2);
  until dec == 0
endfunction
