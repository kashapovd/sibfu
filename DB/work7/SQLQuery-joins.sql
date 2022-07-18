﻿use [Торговая компания]

begin transaction
		-- Показать какой поставщик поставил каждый товар на склад.
		select g.Наименование as 'Товар', p.Наименование as 'Поставщик' from Товар as g
			join Склад as s
				on g.ID = s.КодТoвара
			join Поставщик as p
				on p.ID = s.КодПоставщика;
	go
		-- Вывести список товаров, которыми торгует фирма, и их поставщиков вне зависимости от наличия поставок
		select g.Наименование as 'Товар', p.Наименование as 'Поставщик', s.Количество from Товар as g
			left join Склад as s
				on g.ID = s.КодТoвара
			left join Поставщик as p
				on p.ID = s.КодПоставщика;
	go
		-- Вывести информацию о покупаемых со склада товарах и их покупателях, включая товары, отсутствующие в списке реализованных товаров
		select g.Наименование as N'Товар', ISNULL((select c.Имя+' '+c.Фамилия+' '+c.Отчество), N'не определено') as N'Покупатель', 
			ISNULL(TRY_CONVERT(nvarchar, d.Количество), N'нет продаж') as N'Количество' from Сделка as d
			right join Клиент as c
				on d.КодКлиента = c.ID
			right join Товар as g
				on (select КодТoвара from Склад where ID = d.КодНаСкладе) = g.ID;
	go
		-- Вывести список поставщиков, которые хотя бы раз осуществляли поставку на склад (полусоединение)
		select distinct p.Наименование from Склад as s
			join Поставщик as p
			on p.ID = s.КодПоставщика;
	go
		-- Выведите список сотрудников с указанием их прямых начальников (самосоединение). Для главного начальника в столбец «Начальник» вывести «не определен».
		select e.Фамилия+' '+e.Имя+' '+e.Отчество as Сотрудник, ISNULL((select h.Фамилия+' '+h.Имя+' '+h.Отчество), N'не определено') as Начальник from Сотрудник as e
			left join Сотрудник as h
			on e.КодРуководителя = h.ID;
			
commit transaction