use �������
drop view if exists dbo.highmarkers

-- �������� � ������������� ���������, ��������� ������ �� ��������. �������
-- �.�.�., ����� ������ � �������. ������������ �� ��������� � �������. 
go
create view highmarkers as
	select distinct t.�������, t.���, t.��������, t.���������, t.�������
	from (
		select s.�������, s.���, S.��������, s.���������, d.�������, (select avg(iz.������) from �������� as iz where iz.������ > 1 and iz.��������������������������� = s.�������������������) avgMarkE, (select avg(iz.������) from �������� as iz where iz.������ <= 1  and iz.��������������������������� = s.�������������������) avgMarkZ
		from �������� as e
			join ���������� as d 
				on e.������������� = d.ID
			join �������� as s 
				on e.��������������������������� = s.�������������������
		  group by s.�������, s.���, s.��������, s.���������, d.�������, e.������, s.�������������������) as t
	where t.avgMarkE = 5 and t.avgMarkZ = 1
	group by t.�������, t.���, t.��������, t.���������, t.�������
go
select * from highmarkers;