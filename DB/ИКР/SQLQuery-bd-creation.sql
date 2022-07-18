use �������������
go
begin transaction

	create table ����� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		��������				nvarchar(255)			NOT NULL
	);

	create table �������� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		�����					nvarchar(255)			NOT NULL,
		��������������			int						NOT NULL,
		�����					int						NOT NULL
	);	

	create table �������� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		���						nvarchar(255)			NOT NULL,
		�����������				bigint					NOT NULL,
		foreign key (�����������) references �����(ID)
	);

	create table �������� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		����������				int						NOT NULL,
		����������������		time					NOT NULL,
		�������������			time					NOT NULL,
		����������������		bigint					NOT NULL,
		�������������			bigint					NOT NULL,
		����					money					NOT NULL,
		�������					int						NOT NULL,
		foreign key (����������������) references �����(ID),
		foreign key (�������������) references �����(ID)
	);

	create table ������� (
		ID						bigint	identity(200,1)	NOT NULL primary key,
		�������������			bigint					NOT NULL,
		�������������			bigint					NOT NULL,
		�������������			bigint					NOT NULL,
		������������			date					NOT NULL,
		foreign key (�������������) references ��������(ID),
		foreign key (�������������) references ��������(ID),
		foreign key (�������������) references ��������(ID)
	);

	create table ����� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		�����������				bigint					NOT NULL,
		�����					nvarchar(255)			NOT NULL
		foreign key (�����������) references �����(ID)
	);

	create table ������� (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		���						nvarchar(255)			NOT NULL,
		����					nvarchar(255)			NOT NULL,
	);

	create table ������ (
		ID						bigint	identity(1,1)	NOT NULL primary key,
		����������				bigint					NOT NULL,
		������������			bigint					NOT NULL,
		�����					int						NOT NULL,
		�����������				date					NOT NULL,
		������������			bigint					NOT NULL,
		foreign key (����������) references �����(ID),
		foreign key (������������) references �������(ID),
		foreign key (������������) references �������(ID)
	);

commit transaction

begin transaction
	--��������� ������
	insert ����� values
	(N'�����������'),
	(N'�����'),
	(N'�����'),
	(N'����������'),
	(N'������������'),
	(N'������'),
	(N'��������'),
	(N'�����������'),
	(N'������������'),
	(N'����������')

	--������� ��������
	insert ������� values
	(N'���� �������', N'-'),
	(N'�������� �����', N'-'),
	(N'������� �������', N'-'),
	(N'������� �����', N'-'),
	(N'������� ������', N'-'),
	(N'��������� ���', N'-'),
	(N'�������� �������', N'-'),
	(N'������ �����', N'-'),
	(N'������� ��������', N'-'),
	(N'������� �����', N'-'),
	(N'������ �������', N'-'),
	(N'������ �����', N'-'),
	(N'Ը����� ����', N'-'),
	(N'������ �������', N'-'),
	(N'������ ��������', N'-'),
	(N'����������� ������', N'-'),
	(N'������� ������', N'-')

	--������� ��������
	insert �������� values
	(N'������', 8, (select (abs(checksum(newid())) % 1000))),
	(N'������', 5, (select (abs(checksum(newid())) % 1000))),
	(N'������', 7, (select (abs(checksum(newid())) % 1000))),
	(N'���', 6, (select (abs(checksum(newid())) % 1000))),
	(N'���', 5, (select (abs(checksum(newid())) % 1000))),
	(N'���', 7, (select (abs(checksum(newid())) % 1000))),
	(N'���', 10, (select (abs(checksum(newid())) % 1000))),
	(N'���', 4, (select (abs(checksum(newid())) % 1000)))

	--������� ���������
	insert �������� values
	(N'������� ���������', 2),
	(N'������� �����', 3),
	(N'������� �������', 1),
	(N'������� ������', 4),
	(N'����� ����', 5),
	(N'����� �������', 8),
	(N'����� �����', 10),
	(N'�������� ���������', 6),
	(N'����� �����', 7),
	(N'������� ������',9)

	--������� �����
	insert ����� values
	(1, N'��. ������������ ���, ��� 149'),
	(2, N' ��. ������� ����, ��� 170'),
	(3, N' ��. ��������� ���, ��� 63'),
	(4, N'��. ���������������� ������, ��� 93'),
	(5, N'��. ���������, ��� 105'),
	(6, N'��. �����-2 ���, ��� 177'),
	(7, N'��. ������� 3-�, ��� 143'),
	(8, N'��. �������, ��� 1'),
	(9, N'��. ������, ��� 47'),
	(10, N'��. ��������, ��� 4')

	--������� ��������
	declare @i int = 0

	while @i < 20
	begin
		declare @defPrice int = 1000
		declare @defMinPlace int = 2
		declare @timeDeparture time = '06:00:00'
		declare @timeArrival time = (select DATEADD(hh, (select (abs(checksum(newid())) % 10)), DATEADD(mi, (select (abs(checksum(newid())) % 60)), @timeDeparture)))
		declare @weekDay int = (select (abs(checksum(newid())) % 7) +1)
		declare @cityDeparture bigint = (select top 1 ID from ����� order by newid())
		declare @cityArrival bigint = (select top 1 ID from ����� order by newid())
		while @cityDeparture = @cityArrival
		begin
			set @cityArrival = (select top 1 ID from ����� order by newid())
		end
		
		insert �������� values
		(@weekDay, @timeDeparture, @timeArrival, @cityDeparture, @cityArrival, @defPrice+(select (abs(checksum(newid())) % 500)), @defMinPlace+(select (abs(checksum(newid())) % 3)))
		set @i = @i + 1
	end
	set @i = 1
	
	--������� �������
	while @i <= (select count(*) from ��������)
	begin
		insert into �������
			select 
				@i,
				(select top 1 ID from �������� order by newid()),
				(select top 1 ID from �������� where ����������� = (select ���������������� from �������� where ID = @i) order by newid()),
				DATEADD(dd, (select (abs(checksum(newid())) % 30)),DATEADD(mm, (select (abs(checksum(newid())) % 4)), '2021-05-28'))
			set @i = @i + 1
	end
	set @i = 0;
	--������� ������
	while  @i < 20
	begin
		declare @ticketoffice bigint = (select top 1 ID from ����� order by newid())
		declare @trip bigint = (select top 1 ID from ������� order by newid())
		
		declare @minPlace int = (select ������� from �������� where ID = (select ������������� from ������� where ID = @trip))
		declare @places int = (select �������������� from �������� where ID = (select ������������� from ������� where ID = @trip))
		
		declare @dateofsale date = DATEADD(dd, -10, (select ������������ from ������� where ID = @trip))

		declare @place int = 1
		while (select count(*) from ������ where ����������� = @dateofsale) != @minPlace
		begin
			print('1')
			declare @client bigint = (select top 1 ID from ������� order by newid())
			while (select count(*) from ������ where ������������ = @client) != 0
				set @client = (select top 1 ID from ������� order by newid())

			insert ������ values
				(@ticketoffice, @trip, @place, @dateofsale, @client)
			set @place = @place + 1
		end
		print(@i)
		set @i = @i + 1;
	end
commit transaction