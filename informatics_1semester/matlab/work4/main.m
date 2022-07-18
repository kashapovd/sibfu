## Author:  <yaroslav@arch>
## Created: 2019-10-30

%%Задание 1
v=38;
rand('state', v);
%%Задание 4
r = rand(1, 10);
s = sum(r);
ralph = r ./ s;
save -ascii ralph.txt ralph;
%%Задание 5
load -ascii coin.txt;
load -ascii crime.txt;
load -ascii unfair.txt;
load -ascii ventsel.txt;
s1 = [alph_entropy(coin), alph_redundancy(coin)];
s2 = [alph_entropy(crime), alph_redundancy(crime)];
s3 = [alph_entropy(unfair), alph_redundancy(unfair)];
s4 = [alph_entropy(ventsel), alph_redundancy(ventsel)];
s5 = [alph_entropy(ralph), alph_redundancy(ralph)];
m = [s1; s2; s3; s4; s5];
save -ascii results.txt m;