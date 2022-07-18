use Автотранспорт
go
begin transaction

	create table Город (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Название				nvarchar(255)			NOT NULL
	);

	create table Автобусы (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Марка					nvarchar(255)			NOT NULL,
		КоличествоМест			int						NOT NULL,
		Номер					int						NOT NULL
	);	

	create table Водители (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Имя						nvarchar(255)			NOT NULL,
		НомерГорода				bigint					NOT NULL,
		foreign key (НомерГорода) references Город(ID)
	);

	create table Маршруты (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		ДеньНедели				int						NOT NULL,
		ВремяОтправления		time					NOT NULL,
		ВремяПрибытия			time					NOT NULL,
		ГородОтправления		bigint					NOT NULL,
		ГородПрибытия			bigint					NOT NULL,
		Цена					money					NOT NULL,
		МинМест					int						NOT NULL,
		foreign key (ГородОтправления) references Город(ID),
		foreign key (ГородПрибытия) references Город(ID)
	);

	create table Поездки (
		ID						bigint	identity(200,1)	NOT NULL primary key,
		НомерМаршрута			bigint					NOT NULL,
		НомерАвтобуса			bigint					NOT NULL,
		НомерВодителя			bigint					NOT NULL,
		ДатаПрибытия			date					NOT NULL,
		foreign key (НомерМаршрута) references Маршруты(ID),
		foreign key (НомерАвтобуса) references Автобусы(ID),
		foreign key (НомерВодителя) references Водители(ID)
	);

	create table Кассы (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		НомерГорода				bigint					NOT NULL,
		Адрес					nvarchar(255)			NOT NULL
		foreign key (НомерГорода) references Город(ID)
	);

	create table Клиенты (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Имя						nvarchar(255)			NOT NULL,
		Инфо					nvarchar(255)			NOT NULL,
	);

	create table Билеты (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		НомерКассы				bigint					NOT NULL,
		НомерПоездки			bigint					NOT NULL,
		Место					int						NOT NULL,
		ДатаПродажи				date					NOT NULL,
		НомерКлиента			bigint					NOT NULL,
		foreign key (НомерКассы) references Кассы(ID),
		foreign key (НомерПоездки) references Поездки(ID),
		foreign key (НомерКлиента) references Клиенты(ID)
	);

commit transaction

begin transaction
	--вставляем города
	insert Город values
	(N'Новосибирск'),
	(N'Томск'),
	(N'Канск'),
	(N'Красноярск'),
	(N'Железногорск'),
	(N'Ачинск'),
	(N'Норильск'),
	(N'Зеленогорск'),
	(N'Сосновоборск'),
	(N'Дивногорск')

	--генерим клиентов
	insert Клиенты values
	(N'Юдин Ибрагил', N'-'),
	(N'Артемьев Артур', N'-'),
	(N'Матвеев Варлаам', N'-'),
	(N'Ермаков Рубен', N'-'),
	(N'Соколов Сергей', N'-'),
	(N'Терентьев Ким', N'-'),
	(N'Алексеев Виталий', N'-'),
	(N'Петров Гаянэ', N'-'),
	(N'Логинов Илларион', N'-'),
	(N'Куликов Донат', N'-'),
	(N'Мхиеев Любомир', N'-'),
	(N'Волков Павел', N'-'),
	(N'Фёдоров Юлий', N'-'),
	(N'Жданов Велорий', N'-'),
	(N'Маслов Валентин', N'-'),
	(N'Александров Герман', N'-'),
	(N'Веселов Власий', N'-')

	--генерим автобусы
	insert Автобусы values
	(N'Икарус', 8, (select (abs(checksum(newid())) % 1000))),
	(N'Икарус', 5, (select (abs(checksum(newid())) % 1000))),
	(N'Икарус', 7, (select (abs(checksum(newid())) % 1000))),
	(N'ПАЗ', 6, (select (abs(checksum(newid())) % 1000))),
	(N'ПАЗ', 5, (select (abs(checksum(newid())) % 1000))),
	(N'ГАЗ', 7, (select (abs(checksum(newid())) % 1000))),
	(N'ГАЗ', 10, (select (abs(checksum(newid())) % 1000))),
	(N'ГАЗ', 4, (select (abs(checksum(newid())) % 1000)))

	--генерим водителей
	insert Водители values
	(N'Смирнов Лаврентий', 2),
	(N'Филатов Юстин', 3),
	(N'Суханов Алексей', 1),
	(N'Кононов Людвиг', 4),
	(N'Исаев Адам', 5),
	(N'Быков Николай', 8),
	(N'Силин Вадим', 10),
	(N'Горбунов Вольдемар', 6),
	(N'Рябов Донат', 7),
	(N'Кузьмин Корней',9)

	--генерим кассы
	insert Кассы values
	(1, N'ул. Михайловский пер, дом 149'),
	(2, N' ул. Ширяево Поле, дом 170'),
	(3, N' ул. Нестерова пер, дом 63'),
	(4, N'ул. Нововладыкинский проезд, дом 93'),
	(5, N'ул. Печерская, дом 105'),
	(6, N'ул. Пково-2 тер, дом 177'),
	(7, N'ул. Лазенки 3-я, дом 143'),
	(8, N'ул. Стройки, дом 1'),
	(9, N'ул. Шмидта, дом 47'),
	(10, N'ул. Высотная, дом 4')

	--генерим маршруты
	declare @i int = 0

	while @i < 20
	begin
		declare @defPrice int = 1000
		declare @defMinPlace int = 2
		declare @timeDeparture time = '06:00:00'
		declare @timeArrival time = (select DATEADD(hh, (select (abs(checksum(newid())) % 10)), DATEADD(mi, (select (abs(checksum(newid())) % 60)), @timeDeparture)))
		declare @weekDay int = (select (abs(checksum(newid())) % 7) +1)
		declare @cityDeparture bigint = (select top 1 ID from Город order by newid())
		declare @cityArrival bigint = (select top 1 ID from Город order by newid())
		while @cityDeparture = @cityArrival
		begin
			set @cityArrival = (select top 1 ID from Город order by newid())
		end
		
		insert Маршруты values
		(@weekDay, @timeDeparture, @timeArrival, @cityDeparture, @cityArrival, @defPrice+(select (abs(checksum(newid())) % 500)), @defMinPlace+(select (abs(checksum(newid())) % 3)))
		set @i = @i + 1
	end
	set @i = 1
	
	--генерим поездки
	while @i <= (select count(*) from Маршруты)
	begin
		insert into Поездки
			select 
				@i,
				(select top 1 ID from Автобусы order by newid()),
				(select top 1 ID from Водители where НомерГорода = (select ГородОтправления from Маршруты where ID = @i) order by newid()),
				DATEADD(dd, (select (abs(checksum(newid())) % 30)),DATEADD(mm, (select (abs(checksum(newid())) % 4)), '2021-05-28'))
			set @i = @i + 1
	end
	set @i = 0;
	--генерим билеты
	while  @i < 20
	begin
		declare @ticketoffice bigint = (select top 1 ID from Кассы order by newid())
		declare @trip bigint = (select top 1 ID from Поездки order by newid())
		
		declare @minPlace int = (select МинМест from Маршруты where ID = (select НомерМаршрута from Поездки where ID = @trip))
		declare @places int = (select КоличествоМест from Автобусы where ID = (select НомерАвтобуса from Поездки where ID = @trip))
		
		declare @dateofsale date = DATEADD(dd, -10, (select ДатаПрибытия from Поездки where ID = @trip))

		declare @place int = 1
		while (select count(*) from Билеты where ДатаПродажи = @dateofsale) != @minPlace
		begin
			print('1')
			declare @client bigint = (select top 1 ID from Клиенты order by newid())
			while (select count(*) from Билеты where НомерКлиента = @client) != 0
				set @client = (select top 1 ID from Клиенты order by newid())

			insert Билеты values
				(@ticketoffice, @trip, @place, @dateofsale, @client)
			set @place = @place + 1
		end
		print(@i)
		set @i = @i + 1;
	end
commit transaction