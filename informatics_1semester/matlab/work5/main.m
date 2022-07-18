%%Задание 3
V = 38;
rand('state', V);
%%Задание 4
alph = ['0':'9' 'A':'F'];
r = rand(1, 16);
ralph = r./sum(r);
save -ascii ralph.txt ralph;
%%Задание 5
en = alph_entropy(ralph);
red = alph_redundancy(ralph);
%%Задание 6
msg = gen_msg(ralph, 100);
dlmwrite("msg.txt", msg, ' ');
%%Задание 7
[b, n] = calc_info(msg, alph, ralph);
%%Задание 8
avg = b / (n / log2(length(alph)));
%%Задание 9
results = [b, n, avg, en, red];
save -ascii results.txt results;
