use Автотранспорт;
go
--drop trigger if exists driverChange
create trigger driverChange
	on Поездки
	after update as
	begin
		declare @newDriverID bigint = (select НомерВодителя from inserted)

		if (select НомерГорода from Водители where ID = @newDriverID) = (select ГородОтправления from Маршруты where ID = (select НомерМаршрута from inserted))
			return;

		raiserror ('[error]: driver from another city is not allowed', 16, 1);
		rollback transaction;
	end
go
--drop trigger if exists ticketInsert
create trigger ticketInsert
	on Билеты
	after insert as
	begin
		declare @trip bigint = (select НомерПоездки from inserted)
		declare @date date =(select ДатаПродажи from inserted)
		declare @place int = (select Место from inserted)

		declare @freePlaces int = ((select b.КоличествоМест from Билеты as t 
				join Поездки as tr
					on tr.ID = t.НомерПоездки
				join Автобусы as b
					on b.ID = tr.НомерАвтобуса
				where tr.ID = @trip and t.ДатаПродажи = @date
				group by tr.ID, b.КоличествоМест) - (select count(ID) from Билеты where НомерПоездки = @trip and ДатаПродажи = @date)
			)
		if @freePlaces > 0 or not exists (select ID from Билеты where НомерПоездки = @trip and Место = @place and ДатаПродажи = @date)
			select @freePlaces
			(select ID from Билеты where НомерПоездки = @trip and Место = @place and ДатаПродажи = @date)
			return

			raiserror('[error]: bus is full or place is taken', 16, 1);
			rollback transaction
	end
go
--1.Получить данные (время, цену на билет) о рейсах в город Железногорск из города Норильск.
	select tr.ID, r.ВремяОтправления, r.ВремяПрибытия, r.Цена
	from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		where ГородОтправления = (select ID from Город where Название = N'Норильск')
			and ГородПрибытия = (select ID from Город where Название = N'Железногорск')
		group by tr.ID, r.ВремяОтправления, r.ВремяПрибытия, r.Цена

--2.Получить суммарный доход какой-либо кассы.
	select SUM(Цена) as N'Суммарный доход кассы №8' from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		where t.НомерКассы = 8

--3.Получить суммарные доходы касс в городе Красноярске.
	select SUM(Цена) as N'Суммарный доход кассы в Красноярске' from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		join Кассы as tof
			on tof.ID = t.НомерКассы
		join Город as c
			on c.ID = tof.НомерГорода
		where c.Название = N'Красноярск'

--4.Получить число рейсов, совершѐнных данным водителем за три месяца.
	declare @startDate date = '2021-06-01'
	select count(distinct tr.ID) from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		where tr.НомерВодителя = 9 and datediff(mm, @startDate, t.ДатаПродажи) between 0 and 3

--5.Назначить водителя на рейс.
	declare @trip bigint = 200
	declare @newDriver bigint = 5
	select * from Поездки where ID = @trip
		update Поездки set НомерВодителя = @newDriver where ID = @trip
	select * from Поездки where ID = @trip
	
--6.Оформить билет для клиента в город Железногорск из Норильска, с учѐтом занятых мест в автобусе.
	declare @trip bigint = (select top 1 t.ID from Поездки as t
		join Маршруты as r
			on r.ID = t.НомерМаршрута
		where ГородОтправления = (select ID from Город where Название = N'Норильск')
			and ГородПрибытия = (select ID from Город where Название = N'Железногорск')
		order by newid())
	declare @client bigint = (select top 1 ID from Клиенты order by newid())
	declare @ticketoff bigint = (select top 1 ID from Кассы order by newid())

	insert Билеты values
	(@ticketoff, @trip, 5, '2021-05-30', @client)


--7.Получить число рейсов, совершѐнных автобусами «Икарус» и «ПАЗ»
	select count (distinct tr.ID) as N'число рейсов, совершѐнных автобусами «Икарус» и «ПАЗ»'  from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Автобусы as b
			on b.ID = tr.НомерАвтобуса
		where b.Марка = N'ПАЗ' or b.Марка = N'Икарус'

--8.Проверить все свободные места на рейс.
	declare @ticket bigint = (select top 1 ID from Билеты order by newid())
	declare @trip bigint = (select distinct НомерПоездки from Билеты where ID = @ticket)
	declare @date date =(select ДатаПродажи from Билеты where ID = @ticket)
	declare @place int = (select Место from Билеты where ID = @ticket)
	declare @freePlaces int = ((select b.КоличествоМест from Билеты as t 
				join Поездки as tr
					on tr.ID = t.НомерПоездки
				join Автобусы as b
					on b.ID = tr.НомерАвтобуса
				where tr.ID = @trip and t.ДатаПродажи = @date
				group by tr.ID, b.КоличествоМест) - (select count(ID) from Билеты where НомерПоездки = @trip and ДатаПродажи = @date)
			)
	select @trip as tripID, @freePlaces as freePlaces
	
--9.Показать число билетов, проданных кассами.
	select tof.ID as N'Номер кассы', count(*) as N'Число проданных билетов' from Билеты as t
		join Кассы as tof
			on t.НомерКассы = tof.ID
	group by tof.ID 

--10.Показать среднюю цену билетов
	declare @avgPrice float = 
	(select AVG(r.Цена) from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута)

--11.Показать рейсы, цена на которые выше средней цены на билеты.
	select tr.ID, (select Название from Город where ID = r.ГородОтправления) as N'ГородОтправления', (select Название from Город where ID = r.ГородПрибытия) as N'ГородПрибытия', r.ВремяОтправления, r.Цена from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		where r.Цена > @avgPrice
		group by tr.ID, r.ГородОтправления, r.ГородПрибытия, r.ВремяОтправления, r.Цена

--12.Отменить клиенту билет, после того как он его вернул.
	declare @ticket bigint = (select top 1 ID from Билеты order by newid())
	delete from Билеты where ID = @ticket

--13.Показать информацию о рейсах из города Норильск (включая цену на билет, время рейса)
	select (select Название from Город where ID = r.ГородОтправления) as N'ГородОтправления', (select Название from Город where ID = r.ГородПрибытия) as N'ГородПрибытия', r.ВремяОтправления, r.ВремяПрибытия, r.Цена from Билеты as t
	join Поездки as tr
		on tr.ID = t.НомерПоездки
	join Маршруты as r
		on r.ID = tr.НомерМаршрута
	join Город as c
		on c.ID = r.ГородОтправления
	where c.Название = N'Норильск'
	group by tr.ID, r.ГородОтправления, r.ГородПрибытия, r.ВремяОтправления, r.ВремяПрибытия, r.Цена

--14.Посчитать количество билетов, проданных по рейсам Томск – Новосибирск 2021-2022.
	select count(t.ID)
	from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		where ГородОтправления = (select ID from Город where Название = N'Норильск')
			and ГородПрибытия = (select ID from Город where Название = N'Железногорск')
			and datediff(mm, N'2021-01-01', t.ДатаПродажи) <= 24

--15.Назначить автобус на рейс.
	declare @bus bigint = (select top 1 ID from Автобусы order by newid())
	declare @trip bigint = (select top 1 НомерПоездки from Билеты order by newid())
	declare @ticketCount bigint = (select count(*) from Билеты where НомерПоездки = @trip)
	declare @places bigint = (select КоличествоМест from Автобусы where ID = @bus)
	select @ticketCount, @places
	if (@ticketCount <= @places) 
		
		update Поездки set НомерАвтобуса = @bus where ID = @trip
	else
		raiserror('[error]: not enough space in a bus', 16,1)


--16.Получить список рейсов, на которые может быть назначен данный водитель и
--данный автобус с числом мест, равным 10.
	declare @driver bigint = (select top 1 ID from Водители order by newid())
	declare @bus bigint = (select top 1 ID from Автобусы order by newid())

	select t.НомерКассы, t.НомерКлиента, t.НомерПоездки, t.Место, t.ДатаПродажи from Билеты as t
		join Поездки as tr
			on tr.ID = t.НомерПоездки
		join Маршруты as r
			on r.ID = tr.НомерМаршрута
		join Автобусы as b
			on b.ID = tr.НомерАвтобуса
	where (select НомерГорода from Водители where ID = @driver) = r.ГородОтправления
		and ((b.КоличествоМест - (select count(*) from Билеты where ID = t.ID)) >= 0 )

--17.После ремонта в автобусе добавили 3 места, добавить эти места и в БД.
	begin transaction
		declare @brokenBus bigint = (select top 1 ID from Автобусы order by newid())
		declare @beforeFix int = (select КоличествоМест from Автобусы where ID = @brokenBus)
		update Автобусы set КоличествоМест = @beforeFix + 3 where ID = @brokenBus
		declare @afterFix int = (select КоличествоМест from Автобусы where ID = @brokenBus)
		select @brokenBus as N'ID', (select Марка from Автобусы where ID = @brokenBus) as N'Марка автобуса', @beforeFix as N'Число мест до починки', @afterFix as N'Число мест после починки'
	rollback transaction