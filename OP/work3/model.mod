set ch := 1..3;

param t{ch};
param c{ch};
param r{ch}; 
param B;
param T;
param Rmin;

var x{ch} >= 0;

maximize traffic: 
    sum{i in ch} x[i];

s.t. max_t{i in ch}:
    x[i] <= t[i];
s.t. max_c:
    sum{i in ch} c[i]*x[i] <= B;
s.t. min_t:
    sum{i in ch} x[i] >= T;
s.t. rmin:
    sum{i in ch} r[i]*x[i] >= Rmin*sum{i in ch} x[i];

solve;
printf "R= %.4f\n", (sum{i in ch} x[i]*r[i])/(sum{i in ch} x[i]);

data;

param B :=      24034;
param T :=      3126;
param Rmin :=   0.65;
param t :=      1 2692, 2 2260, 3 1995;
param c :=      1 7.81, 2 1.40, 3 9.45;
param r :=      1 0.24, 2 0.69, 3 0.84;

end;
