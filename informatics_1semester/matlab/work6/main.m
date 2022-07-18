errors = [];
rand('state', 38);
outf = fopen('results.txt', 'w');
for n = -1000 + 2000 * rand(1, 100)
  nstr = print_num_bin(n, 4);
  nback = read_num_bin(nstr);
  err = abs(n - nback);
  errors(end + 1) = err;
  fprintf(outf, '%.6f %s %.6f %.6f\n', n, nstr, nback, err);
endfor
fclose(outf);
stats = [min(errors) mean(errors) max(errors)];
save -ascii stats.txt stats