DROP FUNCTION IF EXISTS dbo.avgMark;      
DROP FUNCTION IF EXISTS dbo.syllabus;  
go
create function avgMark(@disciplineID int) returns float
begin
	declare @result float = 0;
	declare @n float = (select count(*) from �������� where ������������� = @disciplineID and ������ >= 2)
	set @result = (select sum(������) from �������� where ������������� = @disciplineID and ������ >= 2) / @n
	return @result
end
go
create function dbo.syllabus(@groupName nchar(4), @semesteNumber int) returns table as return (
	select d.��������, d.�����, d.���������� from ���������� as d
	join ������ as g
		on d.���������������� = (select g.���������������� where g.�������� = @groupName)
	where d.������� = @semesteNumber
)
go
select dbo.avgMark(4) as N'����������', dbo.avgMark(6) as N'�������', dbo.avgMark(2) as N'���������'
go
select * from dbo.syllabus(N'�C21', 1) 