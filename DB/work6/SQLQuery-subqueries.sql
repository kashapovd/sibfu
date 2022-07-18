use [Торговая компания];

-- prepare
begin transaction
	if (select count(*) from [Склад] where [Количество] = (select max([Количество]) from [Склад])) = 1
	update [Склад] 
		set [Количество] = (select max([Количество]) from [Склад])
		where ID = (select top 1 ID from [Склад] order by newid()) and [Количество] != (select max([Количество]) from [Склад]);
commit transaction

begin transaction
		-- Вывести наименования товаров, количество которых на складе максимально (на
		-- складе должно быть как минимум два товара, количество которых одинаково и
		-- равно максимальному).
		select [Наименование] 
			from [Товар] 
			where ID in (select [КодТoвара] from [Склад] where [Количество] = (select max([Количество]) from [Склад]));
	go 
		-- Вывести в порядке, обратном алфавитному, наименования товаров, количество которых на складе находится в заданном диапазоне.
		declare @bound_1 as int = 5;
		declare @bound_2 as int = 90;
		select [Наименование]
			from [Товар]
			where ID in (select ID from [Склад] where [Количество] between @bound_1 and @bound_2)
			order by [Наименование] desc;
	go
		-- Вывести поставщиков, которые хотя бы раз осуществили поставку, в алфавитном порядке.
		select [Наименование]
			from [Поставщик]
			where ID in (select distinct ID from [Склад] where [Количество] != 0)
			order by [Наименование];
	go 
		-- 30 дней с даты последней покупки действует дополнительная скидка на все товары. Вывести список покупателей, имеющих возможность воспользоваться указанной скидкой.
		declare @purchase_date as date = '2021-01-17';
		select [Фамилия],[Имя],[Отчество] 
			from [Клиент]
			where ID in (select КодКлиента from [Сделка] where datediff(dd, @purchase_date, Дата) between 0 and 30);
	go 
		-- Вывести список товаров, названия которых начинающиеся с букв «Ш» и «Р», стоимость которых не более 20% от максимальной
		select [Наименование] 
			from [Товар]
			where ID in (select ID from [Склад] where [Цена] <= 0.20 * (select max([Цена]) from [Склад]))
			and [Наименование] like N'[ШР]%';
	go
		-- Вывести поставщиков, которые не поставляют товары, названия которых начинаются с букв «О» и «М».
		select Наименование 
			from Поставщик 
			where ID not in (select КодПоставщика from Склад where КодТoвара in (select ID from Товар where Наименование like N'[ОМ]%'));

		-- Показать список клиентов с указанием их пола («мужчина» или «женщина»).
		select [Имя],[Фамилия],[Отчество],
			case 
				when [Пол] = 1 then N'мужчина'
				when [Пол] = 0 then N'женщина'
			end as [Пол]
			from [Клиент]
commit transaction