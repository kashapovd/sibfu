use Деканат
drop view if exists dbo.highmarkers

-- Показать в представлении студентов, сдававших сессии на «Отлично». Вывести
-- Ф.И.О., номер группы и семестр. Группировать по семестрам и группам. 
go
create view highmarkers as
	select distinct t.Фамилия, t.Имя, t.Отчество, t.КодГруппы, t.Семестр
	from (
		select s.Фамилия, s.Имя, S.Отчество, s.КодГруппы, d.Семестр, (select avg(iz.Оценка) from Изучение as iz where iz.Оценка > 1 and iz.НомерЗачетнойКнижкиСтудента = s.НомерЗачетнойКнижки) avgMarkE, (select avg(iz.Оценка) from Изучение as iz where iz.Оценка <= 1  and iz.НомерЗачетнойКнижкиСтудента = s.НомерЗачетнойКнижки) avgMarkZ
		from Изучение as e
			join Дисциплины as d 
				on e.КодДисциплины = d.ID
			join Студенты as s 
				on e.НомерЗачетнойКнижкиСтудента = s.НомерЗачетнойКнижки
		  group by s.Фамилия, s.Имя, s.Отчество, s.КодГруппы, d.Семестр, e.Оценка, s.НомерЗачетнойКнижки) as t
	where t.avgMarkE = 5 and t.avgMarkZ = 1
	group by t.Фамилия, t.Имя, t.Отчество, t.КодГруппы, t.Семестр
go
select * from highmarkers;