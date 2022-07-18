rand('state', 38)
len = 8;
outf = fopen('results.txt', 'w');
fprintf(outf, 'ok %d\n', len); 
maxn = 2^(len - 1) - 1;
for n = randi([-maxn maxn], 1, 100)
    nstr = print_num_code(n, len);
    nback = read_num_code(nstr);
    fprintf(outf, '%d %s\n', n, nstr);
    if nback ~= n
        error("Выходное число не равно исходному");
    end
end
fclose(outf);
