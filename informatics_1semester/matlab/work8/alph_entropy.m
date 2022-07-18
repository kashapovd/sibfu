function en = alph_entropy(P)
  P = P(P != 0);
  en = sum(-P .* log2(P));
endfunction