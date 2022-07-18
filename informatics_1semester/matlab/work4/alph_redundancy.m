## Author:  <yaroslav@arch>
## Created: 2019-10-30

function red = alph_redundancy(P)
  en = alph_entropy(P);
  red = 1 - (en/log2(length(P)));
endfunction
