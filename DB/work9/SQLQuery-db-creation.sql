--create database [�������];
--go;
use [�������];

-- ������ �������
begin transaction
	create table [�������������] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		����					nvarchar(255)			NOT NULL,
		������������			nvarchar(255)			NOT NULL,
		�������������			bit						NOT NULL,
		�������					nvarchar(20)			NOT NULL,
		�������������������������	int					NOT NULL,
		��������				nvarchar(255)			NOT NULL
	);

	create table [��������] (
		�������������������		bigint	identity(3500,1)	NOT NULL primary key, 
		�������					nvarchar(20)			NOT NULL,
		���						nvarchar(20)			NOT NULL,
		��������				nvarchar(20)			NOT NULL,
		���������				bigint					NULL,
		��������������			int						NOT NULL
	);

	create table [�������������] (
		��������������			bigint	identity(200,1)	NOT NULL primary key,
		�������					nvarchar(20)			NOT NULL,
		���						nvarchar(20)			NOT NULL,
		��������				nvarchar(20)			NOT NULL,
		�������������			nvarchar(255)			NOT NULL,
		������������			nvarchar(255)			NOT NULL,
		�������					nvarchar(255)			NOT NULL
	);

	create table [������] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		��������				nvarchar(255)			NOT NULL,
		����������������		bigint					NOT NULL,
		��������				bigint					NOT NULL,
		�������					bigint					NOT NULL
		foreign key (��������) references ��������(�������������������),
		foreign key (�������) references �������������(��������������),
		foreign key (����������������) references �������������(ID)
	);
	alter table	�������� add foreign key (���������) references ������(ID);

	create table [����������] (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		��������				nvarchar(255)			NOT NULL,
		����������������		bigint					NOT NULL,
		�������					int						NOT NULL,
		�����					int						NOT NULL,
		����������				nvarchar(255)			NOT NULL
		foreign key (����������������) references �������������(ID)
	);

	create table [��������] (
		���������������������������	bigint		NOT NULL,
		�������������			bigint			NOT NULL,
		���������				date			NOT NULL,
		������					int				NOT NULL
		foreign key (���������������������������) references ��������(�������������������),
		foreign key (�������������) references ����������(ID)
	);

	create table [������������] (
		�������������			bigint			NOT NULL,
		��������������			bigint			NOT NULL
		foreign key (��������������) references �������������(��������������),
		foreign key (�������������) references ����������(ID)
	);
commit transaction

begin transaction
	-- ������ ��������������
	begin transaction
		insert [�������������] values
		('01', N'���', 0, N'�����������', 4, N'����������� � �������������� �������'),
		('02', N'����', 0, N'�����������', 5, N'�������������� ������� � ����������'),
		('03', N'��', 1, N'������������', 2, N'����������� ���������');
	commit transaction

	-- ������ ����������
	begin transaction
		declare @i as int
		set @i = ((select top 1 ID from �������������) - 1)
		while (@i < (select count(*) from [�������������]))
		begin
			set @i = @i + 1;
			if @i = (select ID from ������������� where ������� = N'������������')
				continue;
			insert ���������� values
			(N'���������', @i, 1, 80, N'�����'),
			(N'���������', @i, 1, 144, N'�������'),
			(N'����������', @i, 1, 100, N'�����'),
			(N'����������', @i, 2, 186, N'�������'),
			(N'�������', @i, 2, 30, N'�����'),
			(N'�������', @i, 2, 112, N'�������');
		end
		set @i = (select top 1 ID from �������������)
		while (@i <= (select count(*) from [�������������]))
		begin
			insert ���������� values
			(N'����������������', @i, 1, 20, N'�������'),
			(N'���������', @i, 2, 78, N'�������'),
			(N'�����������', @i, 1, 80, N'�����'),
			(N'�����������', @i, 2, 80, N'�����');
			set @i = @i + 1;
		end 
	commit transaction
	go
	-- ������ ���������
	begin transaction
		insert �������� values
		(N'�������', N'���������', N'����������', NULL, 2018),
		(N'�����������', N'�����', N'���������', NULL, 2018),
		(N'��������', N'����', N'���������', NULL, 2018),
		(N'�������', N'������', N'����������', NULL, 2018),
		(N'����������', N'������', N'�������', NULL, 2018),
		(N'������', N'�������', N'���������', NULL, 2018),
		(N'�����', N'�����', N'�����', NULL, 2018),
		(N'�������', N'����������', N'��������������', NULL, 2019),
		(N'�������', N'�������', N'���������', NULL, 2019),
		(N'����������', N'������', N'�������', NULL, 2019),
		(N'���������', N'�������', N'���������', NULL, 2019),
		(N'��������', N'���������', N'����������', NULL, 2019),
		(N'������', N'��������', N'����������', NULL, 2019),
		(N'���������', N'�������', N'�����������', NULL, 2019),
		(N'������', N'��������', N'������������', NULL, 2020),
		(N'����������', N'�������', N'���������', NULL, 2020),
		(N'��������', N'���������', N'��������', NULL, 2020),
		(N'�������', N'������', N'���������', NULL, 2020),
		(N'��������', N'�����', N'����������', NULL, 2020),
		(N'���������', N'����', N'�����������', NULL, 2020),
		(N'��������', N'����', N'��������', NULL, 2020),
		(N'�����������', N'����������', N'���������', NULL, 2021),
		(N'�������', N'��������', N'���������', NULL, 2021),
		(N'�����', N'�������', N'������������', NULL, 2021),
		(N'��������', N'������', N'������������', NULL, 2021),
		(N'���������', N'���������', N'�������', NULL, 2021),
		(N'����������', N'�������', N'����������', NULL, 2021),
		(N'���������', N'���', N'�����������', NULL, 2021);
	commit transaction
	go
	-- ������ ��������������
	begin transaction
		insert ������������� values
		(N'���������', N'������� ', N'����������', N'������ ����', N'������', N'��'),
		(N'���������', N'�������', N'�������������', N'�������� ����', N'���������', N'���'),
		(N'��������', N'�������', N'����������', N'�������� ����', N'������', N'��'),
		(N'����������', N'�������', N'�������', N'�������� ����', N'������', N'��'),
		(N'���������', N'�������', N'����������', N'������ ����', N'���������', N'���'),
		(N'�������', N'������', N'�������', N'������ ����', N'������', N'��');
	commit transaction
	go
	-- ������ ������
	begin transaction
		insert ������ values
		(N'��18', (select ID from ������������� where ����=N'01'), 
			(select top 1 ������������������� from �������� where �������������� = 2018 order by newid()), 
			(select top 1 �������������� from ������������� order by newid())),
		(N'��19', (select ID from ������������� where ����=N'03'), 
			(select top 1 ������������������� from �������� where �������������� = 2019 order by newid()), 
			(select top 1 �������������� from ������������� order by newid())),
		(N'��20', (select ID from ������������� where ����=N'01'), 
			(select top 1 ������������������� from �������� where �������������� = 2020 order by newid()), 
			(select top 1 �������������� from ������������� order by newid())),
		(N'��21', (select ID from ������������� where ����=N'01'), 
			(select top 1 ������������������� from �������� where �������������� = 2021 order by newid()), 
			(select top 1 �������������� from ������������� order by newid()));
	commit transaction
	go
	-- ��������� ���� � ������� "��������"
	begin transaction
		update ��������
		set ��������� = (select ID from ������ where SUBSTRING(CONVERT(varchar, ��������������), 3, 4) = SUBSTRING(��������, 3, 4))
	commit transaction
	go
	-- 
	begin transaction
		declare @firstTeacherID int = (select top 1 �������������� from ������������� order by ��������������)
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'���������' and p.�������������� = @firstTeacherID
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'����������' and p.�������������� = @firstTeacherID+1
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'�����������' and p.�������������� = @firstTeacherID+2
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'�������' and p.�������������� = @firstTeacherID+3
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'����������������' and p.�������������� = @firstTeacherID+4
		insert into ������������(��������������, �������������)
		select p.��������������, d.ID from ������������� as p, ���������� as d where d.�������� = N'���������' and p.�������������� = @firstTeacherID+5
	commit transaction

	begin transaction
		insert into �������� 
		select s.�������������������,
				d.ID,
				DATEADD(DAY, (90+ABS(CHECKSUM(NEWID())) %30), CONVERT(varchar, s.��������������) + '-' + IIF(d.�������=1, '09', '02') + '-01'),
				IIF(d.���������� = N'�����', (ABS(CHECKSUM(NEWID())) % 2), (2 + ABS(CHECKSUM(NEWID())) % 4))
		from �������� as s, ���������� as d
		where d.���������������� = (select ���������������� from ������ where ID = s.���������)
		order by newid()
	commit transaction
commit transaction