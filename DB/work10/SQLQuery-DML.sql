use [Деканат];

begin transaction
	
	--создайте группу по специальности, на которую не набирали студентов (ИСИТ)
	insert Группы values
	(N'ИC21', (select ID from Специальности where Шифр=N'02'), 
			(select top 1 НомерЗачетнойКнижки from Студенты where ГодПоступления = 2021 order by newid()), 
			(select top 1 ТабельныйНомер from Преподаватели order by newid()));

	-- Одну из групп, которых две по одной специальности, перевести в созданную группу
	declare @oldGroupID bigint = (select ID from Группы where Название = N'ТИ21') 
	declare @newGroupID bigint = (select ID from Группы where Название = N'ИC21')

	update Студенты 
	set КодГруппы = @newGroupID
	where КодГруппы = @oldGroupID

	-- Назначьте старосту и куратора тех же людей, которые были в теперь уже пустой группе.
	update Группы 
	set Староста = (select Староста from Группы where ID = @oldGroupID), Куратор = (select Куратор from Группы where ID = @oldGroupID)
	where ID = @newGroupID
 
	-- Удалите пустую группу из таблицы.
	delete from Группы
	where ID = @oldGroupID
		
commit transaction