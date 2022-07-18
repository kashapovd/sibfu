create database [Торговая компания];
go
USE [Торговая компания];

begin transaction
	create table [Товар] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	Наименование	nvarchar(255)			NOT NULL,
	Описание		nvarchar(255)			NOT NULL
	);

	create table [Поставщик] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	Наименование	nvarchar(255)			NOT NULL,
	Адрес			nvarchar(255)			NOT NULL
	);

	create table [Склад] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	КодТoвара		bigint					NOT NULL,
	КодПоставщика	bigint					NOT NULL,
	ДатаПоставки	DATE					NOT NULL,
	Количество		INT						NOT NULL,
	Цена			MONEY					NOT NULL,
		foreign key (КодТoвара) references Товар(ID),
		foreign key (КодПоставщика) references Поставщик(ID)
	);

	create table [Клиент] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	Фамилия			nvarchar(20)			NOT NULL,
	Имя				nvarchar(20)			NOT NULL,
	Отчество		nvarchar(20)			NOT NULL,
	Адрес			nvarchar(255)			NOT NULL,
	Пол				INT						NOT NULL
	);

	create table [Сотрудник] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	КодРуководителя	bigint					NULL,
	Фамилия			nvarchar(20)			NOT NULL,
	Имя				nvarchar(20)			NOT NULL,
	Отчество		nvarchar(20)			NOT NULL,
	Адрес			nvarchar(255)			NOT NULL
		foreign key (КодРуководителя) references Сотрудник(ID)
	);

	create table [Сделка] (
	ID				bigint	identity(1,1)	NOT NULL primary key,
	КодНаСкладе		bigint					NOT NULL,
	КодСотрудника	bigint					NOT NULL,
	КодКлиента		bigint					NOT NULL,	
	Количество		INT						NOT NULL,
	Дата			DATE					NOT NULL
		foreign key (КодНаСкладе) references Склад(ID),
		foreign key (КодСотрудника) references Сотрудник(ID),
		foreign key (КодКлиента) references Клиент(ID)
	);
commit transaction

begin transaction
	-- генерируем таблицу товаров
	begin transaction
		insert [Товар] values 
		(N'Лопата',		N'Для уборка снега'),
		(N'Бензопила',	N'Бензопила с широкой шиной'),
		(N'Рубанок',	N'Рубанок электрический'),
		(N'Мотыга',		N'Как в майнкрафте (алмазная)'),
		(N'Шланг',		N'Шланг высокого давления'),
		(N'Отвёртка',	N'Шлицевая'),
		(N'Отвёртка',	N'Крестовая'),
		(N'Ножницы',	N'Ножницы садовые'),
		(N'Лобзик',		N'Лобзик электрический'),
		(N'Сверло',		N'Сверло диметром 1 см.');
	commit transaction

	-- генерируем таблицу поставщиков
	begin transaction
		insert [Поставщик] values
		(N'ООО "Стройбаза"', N' г. Явас, ул. Комсомольский пер, дом 79'),
		(N'ООО "Россельстрой"', N' г. Колышлей, ул. Малая Морская, дом 32'),
		(N'ИП "Волощук Сидор Богданович"', N'г. Кирова, ул. Сталина, дом 47'),
		(N'ИП "Пономарёв Ануфри Викторович"', N'г. Гаврилов-ям, ул. Университетская пл, дом 112'),
		(N'OOO "ТехноАльянс"', N'г. Лазаревское, ул. Причальный проезд, дом 975'),
		(N'ООО "PerfectHand"', N'г. Барабинск, ул. Варваринская, дом 43');
	commit transaction

	-- генерируем таблицу клиентов
	begin transaction
		insert [Клиент] values
		(N'Москаленко', N'Марина', N'Ермаковна', N'г. Грайворон, ул. Михайловский пер, дом 149, квартира 994', N'0'),
		(N'Зорин', N'Остап', N'Леонидович', N'г. Александро-Невский, ул. Лазенки 3-я, дом 143, квартира 41', N'1'),
		(N'Москаленко', N'Дементий', N'Богданович', N'г. Антропово, ул. Печерская, дом 105, квартира 817', N'1'),
		(N'Быстров', N'Леон', N'Викторович', N'г. Кушнаренково, ул. Нововладыкинский проезд, дом 93, квартира 562', N'1'),
		(N'Павленко', N'Гавриил', N'Игоревич', N'г. Домбаровский, ул. Нестерова пер, дом 63, квартира 110', N'1'),
		(N'Мамедова', N'Алиса', N'Андреевна', N'г. Заозерье, ул. Ширяево Поле, дом 170, квартира 9', N'0'),
		(N'Кароль', N'Мария', N'Виталиевна', N'г. Нива, ул. Пково-2 тер, дом 177, квартира 48', N'0');
	commit transaction

	-- генерируем таблицу сотрудников
	begin transaction
		insert [Сотрудник] values
		(NULL, N'Попова', N'Екатерина', N'Борисовна', N'г. Лазаревское, ул. Здоровцева, дом 131, квартира 62');
		insert [Сотрудник] values
		((select ID from [Сотрудник] where [КодРуководителя] is null), N'Казаков', N'Селиверст', N'Давидович', N'г. Олекминск, ул. Тверская-Ямская 2-Я, дом 25, квартира 42'),
		((select ID from [Сотрудник] where [КодРуководителя] is null), N'Михайлов', N'Гремислав', N'Борисович', N'г. Становое, ул. Люсиновский 1-й пер, дом 1, квартира 298');
		insert [Сотрудник] values
		((select ID from [Сотрудник] where [КодРуководителя]=(select ID from [Сотрудник] where [КодРуководителя] is null) and [Фамилия]=N'Казаков'), N'Королев', N'Владлен', N'Леонидович', N'г. Старощербиновская, ул. Герасима Курина, дом 63, квартира 578'),
		((select ID from [Сотрудник] where [КодРуководителя]=(select ID from [Сотрудник] where [КодРуководителя] is null) and [Фамилия]=N'Казаков'), N'Яковлева', N'Варвара', N'Викторовна', N'г. Черный Яр, ул. Опочинина, дом 59, квартира 235'),
		((select ID from [Сотрудник] where [КодРуководителя]=(select ID from [Сотрудник] where [КодРуководителя] is null) and [Фамилия]=N'Михайлов'), N'Тимошенко', N'Флорентин', N'Александрович', N'г. Путятино, ул. Скьптора Мухиной, дом 45, квартира 77'),
		((select ID from [Сотрудник] where [КодРуководителя]=(select ID from [Сотрудник] where [КодРуководителя] is null) and [Фамилия]=N'Михайлов'), N'Попов', N'Антонин', N'Юрьевич', N'г. Кировград, ул. Михайловский Верхн. 2-й проезд, дом 96, квартира 177');
	commit transaction

	-- генерируем таблицу склада
	begin transaction
		insert [Склад] values
		-- одинаковые товары поставлены разными поставщиками
		((select ID from [Товар] where [Наименование]=N'Отвёртка' and [Описание]=N'Крестовая'),
		 (select ID from [Поставщик] where [Наименование]=N'OOO "ТехноАльянс"'), '2021-01-10', 200, 110),
		((select ID from [Товар] where [Наименование]=N'Отвёртка' and [Описание]=N'Крестовая'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Стройбаза"'), '2021-02-01', 300, 115),

		((select ID from [Товар] where [Наименование]=N'Отвёртка' and [Описание]=N'Шлицевая'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Россельстрой"'), '2021-01-12', 43, 140),
		((select ID from [Товар] where [Наименование]=N'Отвёртка' and [Описание]=N'Шлицевая'),
		 (select ID from [Поставщик] where [Наименование]=N'OOO "ТехноАльянс"'), '2021-01-15', 0, 138.5),
		((select ID from [Товар] where [Наименование]=N'Отвёртка' and [Описание]=N'Шлицевая'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Стройбаза"'), '2021-02-01', 110, 150),

		((select ID from [Товар] where [Наименование]=N'Лопата'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Стройбаза"'), '2021-01-21', 0, 799),
		((select ID from [Товар] where [Наименование]=N'Лопата'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Россельстрой"'), '2021-01-28', 83, 750),

		((select ID from [Товар] where [Наименование]=N'Бензопила'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Стройбаза"'), '2021-01-21', 10, 5000),
		((select ID from [Товар] where [Наименование]=N'Бензопила'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Россельстрой"'), '2021-01-28', 0, 6500),
		((select ID from [Товар] where [Наименование]=N'Сверло'),
		 (select ID from [Поставщик] where [Наименование]=N'ИП "Пономарёв Ануфри Викторович"'), '2021-02-01', 131, 100),
		((select ID from [Товар] where [Наименование]=N'Сверло'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "Россельстрой"'), '2021-02-01', 10, 101),

		-- одинаковые товары по разным ценам поставлены в разные даты
		((select ID from [Товар] where [Наименование]=N'Мотыга'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "PerfectHand"'), '2021-02-01', 30, 550),
		((select ID from [Товар] where [Наименование]=N'Мотыга'),
		 (select ID from [Поставщик] where [Наименование]=N'ООО "PerfectHand"'), '2021-01-20', 50, 500),
		((select ID from [Товар] where [Наименование]=N'Лобзик'),
		 (select ID from [Поставщик] where [Наименование]=N'OOO "ТехноАльянс"'), '2021-02-01', 0, 1400),
		((select ID from [Товар] where [Наименование]=N'Лобзик'),
		 (select ID from [Поставщик] where [Наименование]=N'OOO "ТехноАльянс"'), '2021-01-02', 40, 1500),

		((select ID from [Товар] where [Наименование]=N'Шланг'),
		 (select ID from [Поставщик] where [Наименование]=N'OOO "ТехноАльянс"'), '2021-01-15', 100, 300);
	commit transaction

	-- генерируем таблицу сделок
	begin transaction
		declare @i as float
		set @i = 1
		while (@i <= (select count(*) from [Клиент]))
		begin
			insert [Сделка] values
			((select top 1 ID from [Склад] order by newid()),
			 (select top 1 ID from [Сотрудник] order by newid()), 
			 (select ID from [Клиент] where ID=ceiling(@i)), (select floor(rand()*(100))),
			 (select dateadd(day, floor(rand()*(365)), '2021-01-01')));
			set @i = @i + 0.5;
		 end 
	commit transaction
commit transaction
