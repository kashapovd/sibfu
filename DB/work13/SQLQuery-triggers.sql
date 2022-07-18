use Деканат
drop trigger if exists disciplineDelete
drop trigger if exists headmanСhange
drop trigger if exists examInsert
go
create trigger disciplineDelete
	on Дисциплины
	instead of delete as
	begin
		declare @discID bigint = (select ID from deleted)
		if exists (select * from Изучение where КодДисциплины = @discID) begin
				raiserror ('[error]: discipline in use', 16, 1);
				return;
		end
		delete from Дисциплины
			where ID = @discID
	end
go
create trigger headmanСhange
	on Группы
	after update as
	begin
		declare @newHeadmanID bigint = (select Староста from inserted)

		if (select КодГруппы from Студенты where НомерЗачетнойКнижки = @newHeadmanID) = (select ID from inserted)
			return;
		raiserror ('[error]: student from another group is not allowed', 16, 1);
		rollback transaction;
	end
go
--Не позволить добавить информацию о сданном экзамене (или зачете), если
--дисциплина не соответствует специальности студента.
create trigger examInsert
	on Изучение
	after insert as
	begin
		declare @specIDbyDiscipline bigint = (
			select КодСпециальности 
				from Дисциплины where ID = (
					select КодДисциплины 
						from inserted
				)
			)
		
		declare @specIDbyStudent bigint = (
		select КодСпециальности 
			from Группы where ID = (
				select КодГруппы 
					from Студенты where НомерЗачетнойКнижки = (
						select НомерЗачетнойКнижкиСтудента 
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

insert Дисциплины values
	(N'Философывааываия', 1, 1, 80, N'зачёт');

delete from Дисциплины WHERE ID = 1;
delete from Дисциплины WHERE Название = N'Философывааываия';
go 
update Группы set Староста = 3500 WHERE ID = 1;
go
insert Изучение values
	(3500, 1, '2018-12-02', 1);

select * 
	from Изучение where НомерЗачетнойКнижкиСтудента = 3500 and КодДисциплины =1
go