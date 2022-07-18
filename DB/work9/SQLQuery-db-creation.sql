--create database [Деканат];
--go;
use [Деканат];

-- создаём таблицы
begin transaction
	create table [Специальности] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Шифр					nvarchar(255)			NOT NULL,
		Наименование			nvarchar(255)			NOT NULL,
		ФормаОбучения			bit						NOT NULL,
		Уровень					nvarchar(20)			NOT NULL,
		ПродолжительностьОбучения	int					NOT NULL,
		Описание				nvarchar(255)			NOT NULL
	);

	create table [Студенты] (
		НомерЗачетнойКнижки		bigint	identity(3500,1)	NOT NULL primary key, 
		Фамилия					nvarchar(20)			NOT NULL,
		Имя						nvarchar(20)			NOT NULL,
		Отчество				nvarchar(20)			NOT NULL,
		КодГруппы				bigint					NULL,
		ГодПоступления			int						NOT NULL
	);

	create table [Преподаватели] (
		ТабельныйНомер			bigint	identity(200,1)	NOT NULL primary key,
		Фамилия					nvarchar(20)			NOT NULL,
		Имя						nvarchar(20)			NOT NULL,
		Отчество				nvarchar(20)			NOT NULL,
		УчёнаяСтепень			nvarchar(255)			NOT NULL,
		УчёноеЗвание			nvarchar(255)			NOT NULL,
		Кафедра					nvarchar(255)			NOT NULL
	);

	create table [Группы] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Название				nvarchar(255)			NOT NULL,
		КодСпециальности		bigint					NOT NULL,
		Староста				bigint					NOT NULL,
		Куратор					bigint					NOT NULL
		foreign key (Староста) references Студенты(НомерЗачетнойКнижки),
		foreign key (Куратор) references Преподаватели(ТабельныйНомер),
		foreign key (КодСпециальности) references Специальности(ID)
	);
	alter table	Студенты add foreign key (КодГруппы) references Группы(ID);

	create table [Дисциплины] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		Название				nvarchar(255)			NOT NULL,
		КодСпециальности		bigint					NOT NULL,
		Семестр					int						NOT NULL,
		Объем					int						NOT NULL,
		Отчетность				nvarchar(255)			NOT NULL
		foreign key (КодСпециальности) references Специальности(ID)
	);

	create table [Изучение] (
		НомерЗачетнойКнижкиСтудента	bigint		NOT NULL,
		КодДисциплины			bigint			NOT NULL,
		ДатаСдачи				date			NOT NULL,
		Оценка					int				NOT NULL
		foreign key (НомерЗачетнойКнижкиСтудента) references Студенты(НомерЗачетнойКнижки),
		foreign key (КодДисциплины) references Дисциплины(ID)
	);

	create table [Преподавание] (
		КодДисциплины			bigint			NOT NULL,
		ТабельныйНомер			bigint			NOT NULL
		foreign key (ТабельныйНомер) references Преподаватели(ТабельныйНомер),
		foreign key (КодДисциплины) references Дисциплины(ID)
	);
commit transaction

begin transaction
	-- создаём специальнности
	begin transaction
		insert [Специальности] values
		('01', N'ИВТ', 0, N'бакалавриат', 4, N'Информатика и вычислительная техника'),
		('02', N'ИСИТ', 0, N'специалитет', 5, N'Информационные системы и технологии'),
		('03', N'ПИ', 1, N'магистратура', 2, N'Программная инженерия');
	commit transaction

	-- создаём дисциплины
	begin transaction
		declare @i as int
		set @i = ((select top 1 ID from Специальности) - 1)
		while (@i < (select count(*) from [Специальности]))
		begin
			set @i = @i + 1;
			if @i = (select ID from Специальности where Уровень = N'магистратура')
				continue;
			insert Дисциплины values
			(N'Философия', @i, 1, 80, N'зачёт'),
			(N'Философия', @i, 1, 144, N'экзамен'),
			(N'Математика', @i, 1, 100, N'зачёт'),
			(N'Математика', @i, 2, 186, N'экзамен'),
			(N'История', @i, 2, 30, N'зачёт'),
			(N'История', @i, 2, 112, N'экзамен');
		end
		set @i = (select top 1 ID from Специальности)
		while (@i <= (select count(*) from [Специальности]))
		begin
			insert Дисциплины values
			(N'Программирование', @i, 1, 20, N'экзамен'),
			(N'Алгоритмы', @i, 2, 78, N'экзамен'),
			(N'Физкультура', @i, 1, 80, N'зачёт'),
			(N'Физкультура', @i, 2, 80, N'зачёт');
			set @i = @i + 1;
		end 
	commit transaction
	go
	-- создаём студентов
	begin transaction
		insert Студенты values
		(N'Кольцов', N'Святослав', N'Эльдарович', NULL, 2018),
		(N'Лаврентьева', N'Агата', N'Артемовна', NULL, 2018),
		(N'Федотова', N'Рада', N'Матвеевна', NULL, 2018),
		(N'Петрова', N'Тамара', N'Валерьевна', NULL, 2018),
		(N'Шаповалова', N'Анжела', N'Львовна', NULL, 2018),
		(N'Фролов', N'Онуфрий', N'Антонович', NULL, 2018),
		(N'Орлов', N'Юлиан', N'Ильич', NULL, 2018),
		(N'Волощук', N'Флорентина', N'Константиновна', NULL, 2019),
		(N'Князева', N'Пелагея', N'Романовна', NULL, 2019),
		(N'Кудрявцева', N'Дарина', N'Юрьевна', NULL, 2019),
		(N'Соловьева', N'Наталья', N'Закировна', NULL, 2019),
		(N'Звездный', N'Лаврентий', N'Леонидович', NULL, 2019),
		(N'Егоров', N'Вениамин', N'Кириллович', NULL, 2019),
		(N'Каменских', N'Спартак', N'Анатольевич', NULL, 2019),
		(N'Лютова', N'Аграфена', N'Валентиновна', NULL, 2020),
		(N'Чайковская', N'Надежда', N'Сергеевна', NULL, 2020),
		(N'Щербаков', N'Христофор', N'Игоревич', NULL, 2020),
		(N'Васютин', N'Бернар', N'Закирович', NULL, 2020),
		(N'Романова', N'Марфа', N'Леонидовна', NULL, 2020),
		(N'Герасимов', N'Арно', N'Анатольевич', NULL, 2020),
		(N'Ржевский', N'Наум', N'Егорович', NULL, 2020),
		(N'Калашникова', N'Клементина', N'Сергеевна', NULL, 2021),
		(N'Маврина', N'Вероника', N'Тарасовна', NULL, 2021),
		(N'Быков', N'Будимир', N'Валентинович', NULL, 2021),
		(N'Ржевский', N'Ануфри', N'Валентинович', NULL, 2021),
		(N'Садовская', N'Генриетта', N'Юрьевна', NULL, 2021),
		(N'Городецкий', N'Никандр', N'Алексеевич', NULL, 2021),
		(N'Берестова', N'Ева', N'Ярославовна', NULL, 2021);
	commit transaction
	go
	-- создаём преподавателей
	begin transaction
		insert Преподаватели values
		(N'Баландина', N'Евдокия ', N'Степановна', N'доктор наук', N'доцент', N'ВТ'),
		(N'Платонова', N'Агнесса', N'Владиславовна', N'кандидат наук', N'профессор', N'ИБП'),
		(N'Крымская', N'Саломея', N'Максимовна', N'кандидат наук', N'доцент', N'КТ'),
		(N'Богатырева', N'Эвелина', N'Юрьевна', N'кандидат наук', N'доцент', N'ВО'),
		(N'Филлипова', N'Евгеиня', N'Богдановна', N'доктор наук', N'профессор', N'ИБП'),
		(N'Галкина', N'Рената', N'Львовна', N'доктор наук', N'доцент', N'КУ');
	commit transaction
	go
	-- создаём группы
	begin transaction
		insert Группы values
		(N'ТИ18', (select ID from Специальности where Шифр=N'01'), 
			(select top 1 НомерЗачетнойКнижки from Студенты where ГодПоступления = 2018 order by newid()), 
			(select top 1 ТабельныйНомер from Преподаватели order by newid())),
		(N'ММ19', (select ID from Специальности where Шифр=N'03'), 
			(select top 1 НомерЗачетнойКнижки from Студенты where ГодПоступления = 2019 order by newid()), 
			(select top 1 ТабельныйНомер from Преподаватели order by newid())),
		(N'ТИ20', (select ID from Специальности where Шифр=N'01'), 
			(select top 1 НомерЗачетнойКнижки from Студенты where ГодПоступления = 2020 order by newid()), 
			(select top 1 ТабельныйНомер from Преподаватели order by newid())),
		(N'ТИ21', (select ID from Специальности where Шифр=N'01'), 
			(select top 1 НомерЗачетнойКнижки from Студенты where ГодПоступления = 2021 order by newid()), 
			(select top 1 ТабельныйНомер from Преподаватели order by newid()));
	commit transaction
	go
	-- обновляем инфу в таблице "Студенты"
	begin transaction
		update Студенты
		set КодГруппы = (select ID from Группы where SUBSTRING(CONVERT(varchar, ГодПоступления), 3, 4) = SUBSTRING(Название, 3, 4))
	commit transaction
	go
	-- 
	begin transaction
		declare @firstTeacherID int = (select top 1 ТабельныйНомер from Преподаватели order by ТабельныйНомер)
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'Философия' and p.ТабельныйНомер = @firstTeacherID
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'Математика' and p.ТабельныйНомер = @firstTeacherID+1
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'Физкультура' and p.ТабельныйНомер = @firstTeacherID+2
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'История' and p.ТабельныйНомер = @firstTeacherID+3
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'Программирование' and p.ТабельныйНомер = @firstTeacherID+4
		insert into Преподавание(ТабельныйНомер, КодДисциплины)
		select p.ТабельныйНомер, d.ID from Преподаватели as p, Дисциплины as d where d.Название = N'Алгоритмы' and p.ТабельныйНомер = @firstTeacherID+5
	commit transaction

	begin transaction
		insert into Изучение 
		select s.НомерЗачетнойКнижки,
				d.ID,
				DATEADD(DAY, (90+ABS(CHECKSUM(NEWID())) %30), CONVERT(varchar, s.ГодПоступления) + '-' + IIF(d.Семестр=1, '09', '02') + '-01'),
				IIF(d.Отчетность = N'зачёт', (ABS(CHECKSUM(NEWID())) % 2), (2 + ABS(CHECKSUM(NEWID())) % 4))
		from Студенты as s, Дисциплины as d
		where d.КодСпециальности = (select КодСпециальности from Группы where ID = s.КодГруппы)
		order by newid()
	commit transaction
commit transaction