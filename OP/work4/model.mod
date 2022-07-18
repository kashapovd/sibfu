# Множество номеров дней 1, 2, ...
set days;
# Множество номеров дней с нуля: 0, 1, ...
set zdays := {0} union days;
# Материалы
set supplies;
# Оборудование
set equipment;
# Все ресурсы
set resources := supplies union equipment;

# Начальные запасы
param sup0{resources};
# Начальное число больных
param ill0;
# Эффективность предотвращения
param pr_cost{resources};
# Эффективность лечения
param tr_cost{resources};
# Коэффициент заразности (сколько здоровых подвергает контакту один больной)
param k_cont;
# Изменение коэффициента заразности за день
param dk_cont;

# Число больных в дни 0, 1, ...
var ill{zdays} >= 0 integer;
# Число выздоровевших
var rec{zdays} >= 0 integer;
# Число контактных (подвергшихся контакту с инфекцией, потенциальных больных)
var exps{zdays} >= 0 integer;
# Число предотвращённых заболеваний
var pr{zdays} >= 0 integer;
# Запасы материалов
var sup{zdays, supplies} >= 0 integer;
# Доступность оборудования
var equ{zdays, equipment} >= 0 integer;

minimize final_ill: ill[max{d in days} d];

s.t. con_sup0{s in supplies}: sup[0, s] = sup0[s];
s.t. con_sup{d in days, s in supplies}: sup[d, s] = sup[d - 1, s] - pr[d] * pr_cost[s] - rec[d] * tr_cost[s];
# Динамика доступности оборудования
s.t. con_equ0{e in equipment}: equ[0, e] = sup0[e];
s.t. con_equ{d in days, e in equipment}: equ[d, e] = equ[0, e] - pr[d] * pr_cost[e] - rec[d] * tr_cost[e];
# Динамика числа контактных
s.t. cons_exps0: exps[0] = 0;
s.t. con_exps{d in days}: exps[d] = ill[d-1] * (k_cont + (d - 1) * dk_cont);
# Динамика числа больных
s.t. con_ill0: ill[0] = ill0;
s.t. con_ill{d in days}: ill[d] = ill[d-1] + exps[d-1] - pr[d] - rec[d];
# Число предотвращённых не больше количества контактных за вчерашний день
s.t. con_pr0: pr[0] = 0;
s.t. con_pr{d in days}: pr[d] <= exps[d-1];
# Число выздоровевших не больше количества больных за вчерашний день
s.t. con_rec0: rec[0] = 0;
s.t. con_rec{d in days}: rec[d] <= ill[d-1];

data;
set days := 1, 2, 3;
set supplies := 'MASK', 'PILL', 'SOAP';
set equipment := 'BED';
param sup0 := 'BED' 13896, 'MASK' 175103, 'PILL' 244845, 'SOAP' 292955;
param ill0 := 14379;
param k_cont := 10;
param dk_cont := -1;
param     :    pr_cost     tr_cost :=
    'BED'      1	   1
    'MASK'     0.5	   4
    'PILL'     0	   2
    'SOAP'     1.5	   6;
end;
