V=38
%Задание 1
rand('state', V);
vec = rand(1, 5);
%%
%Задание 2
v = [1:100];
r = randi([0,1], 1, 100);
s = v+r;
s(mod(s, 2) == 1) = 0
%%
%Задание 3
R = rand(1, 99.*V) .* 3;
f = @(t) sum(R < t);
t = 0:0.1:3;
figure;
plot(arrayfun(f, t), t);
print("3.png");
%%
%Задание 4
figure;
plot(rand([12+V, 4]), rand([12+V, 4]));
print("4.png");
%%
%Задание 5
figure;
plot3(rand([12+V, 4]), rand([12+V, 4]), rand([12+V, 4]));
print("5.png");
%%
%Задание 6
t = 0:0.1:2*(3+V)*pi;
r = linspace(0, 1, numel(t));
figure;
plot(r.*sin(t), r.*cos(t));
print("6.png");
%%
%Задание 7
X = -4:0.1:4;
Y = -4:0.1:4;
[x, y] = meshgrid(X, Y);
z =  cos(0.5 * V .* x) .* x .^ 3 + y .^ 2;
figure;
mesh(z);
print("7_1.png");
xlabel('x');
ylabel('y');
zlabel('z');
figure;
surf(z);
print("7_2.png");
xlabel('x');
ylabel('y');
zlabel('z');
%%
%Задание 11
nflip = 9 * V;
nexp = 1001 + V;
s = flip_stats(nflip, nexp);
v = s ./ nexp;
figure;
bar(v);
print("11.png");
