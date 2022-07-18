use [�������];

begin transaction
	
	--�������� ������ �� �������������, �� ������� �� �������� ��������� (����)
	insert ������ values
	(N'�C21', (select ID from ������������� where ����=N'02'), 
			(select top 1 ������������������� from �������� where �������������� = 2021 order by newid()), 
			(select top 1 �������������� from ������������� order by newid()));

	-- ���� �� �����, ������� ��� �� ����� �������������, ��������� � ��������� ������
	declare @oldGroupID bigint = (select ID from ������ where �������� = N'��21') 
	declare @newGroupID bigint = (select ID from ������ where �������� = N'�C21')

	update �������� 
	set ��������� = @newGroupID
	where ��������� = @oldGroupID

	-- ��������� �������� � �������� ��� �� �����, ������� ���� � ������ ��� ������ ������.
	update ������ 
	set �������� = (select �������� from ������ where ID = @oldGroupID), ������� = (select ������� from ������ where ID = @oldGroupID)
	where ID = @newGroupID
 
	-- ������� ������ ������ �� �������.
	delete from ������
	where ID = @oldGroupID
		
commit transaction