## Author:  <yaroslav@arch>
## Created: 2019-10-30

function en = alph_entropy(P)
  P = P(P != 0);
  en = sum(-P .* log2(P));
endfunction
