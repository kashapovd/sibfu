DROP FUNCTION IF EXISTS dbo.avgMark;      
DROP FUNCTION IF EXISTS dbo.syllabus;  
go
create function avgMark(@disciplineID int) returns float
begin
	declare @result float = 0;
	declare @n float = (select count(*) from Изучение where КодДисциплины = @disciplineID and Оценка >= 2)
	set @result = (select sum(Оценка) from Изучение where КодДисциплины = @disciplineID and Оценка >= 2) / @n
	return @result
end
go
create function dbo.syllabus(@groupName nchar(4), @semesteNumber int) returns table as return (
	select d.Название, d.Объем, d.Отчетность from Дисциплины as d
	join Группы as g
		on d.КодСпециальности = (select g.КодСпециальности where g.Название = @groupName)
	where d.Семестр = @semesteNumber
)
go
select dbo.avgMark(4) as N'Математика', dbo.avgMark(6) as N'История', dbo.avgMark(2) as N'Философия'
go
select * from dbo.syllabus(N'ИC21', 1) 