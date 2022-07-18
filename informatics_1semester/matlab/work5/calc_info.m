## Author:  <yaroslav@arch>
## Created: 2019-11-27

function [b,n] = calc_info(msg, alph, alph_p)
  len_alph = length(alph);
  len_alph_p = length(alph_p);
  len_msg = length(msg);
  if len_alph ~= len_alph_p;
    error("alph и alph_p имеют разную длину: %d != %d", length(alph), length(alph_p))
  endif
  
  b=0;
  for i=1:len_msg
    m = msg(i)==alph(1:len_alph);
    if any(m)
      b -= log2(alph_p(m));
    else
      len_msg--;
      warning("Символ '%s' на %d позиции из msg не найден в алфавите", msg(i), i);
    endif
  endfor
  
  n = len_msg*log2(length(alph));
endfunction
