function s = flip_stats(nflip, nexp)
  k = 0;
  s(1:nflip+1) = 0;
  while k~=nexp
    i = sum_heads(coin_flip(nflip));
    s(i+1) += 1;
    k += 1;
  endwhile
endfunction
