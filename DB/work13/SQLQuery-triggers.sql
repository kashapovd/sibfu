use �������
drop trigger if exists disciplineDelete
drop trigger if exists headman�hange
drop trigger if exists examInsert
go
create trigger disciplineDelete
	on ����������
	instead of delete as
	begin
		declare @discID bigint = (select ID from deleted)
		if exists (select * from �������� where ������������� = @discID) begin
				raiserror ('[error]: discipline in use', 16, 1);
				return;
		end
		delete from ����������
			where ID = @discID
	end
go
create trigger headman�hange
	on ������
	after update as
	begin
		declare @newHeadmanID bigint = (select �������� from inserted)

		if (select ��������� from �������� where ������������������� = @newHeadmanID) = (select ID from inserted)
			return;
		raiserror ('[error]: student from another group is not allowed', 16, 1);
		rollback transaction;
	end
go
--�� ��������� �������� ���������� � ������� �������� (��� ������), ����
--���������� �� ������������� ������������� ��������.
create trigger examInsert
	on ��������
	after insert as
	begin
		declare @specIDbyDiscipline bigint = (
			select ���������������� 
				from ���������� where ID = (
					select ������������� 
						from inserted
				)
			)
		
		declare @specIDbyStudent bigint = (
		select ���������������� 
			from ������ where ID = (
				select ��������� 
					from �������� where ������������������� = (
						select ��������������������������� 
							from inserted
					)
				)
			)

		if @specIDbyStudent = @specIDbyDiscipline
			return;
		
		raiserror ('[error]: student is not learning that discipline', 16, 1);
		rollback transaction
	end

go

insert ���������� values
	(N'����������������', 1, 1, 80, N'�����');

delete from ���������� WHERE ID = 1;
delete from ���������� WHERE �������� = N'����������������';
go 
update ������ set �������� = 3500 WHERE ID = 1;
go
insert �������� values
	(3500, 1, '2018-12-02', 1);

select * 
	from �������� where ��������������������������� = 3500 and ������������� =1
go