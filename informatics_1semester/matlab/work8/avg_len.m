function l = avg_len(C, P)
    l = 0;
    for i=1:length(C)
        l += length(C{i}) * P(i);
    endfor
endfunction
