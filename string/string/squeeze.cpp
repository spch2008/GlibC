
// ��s�е��ַ�c�޳�
void squeeze(char *s, char c)
{
	char *p = s;
	char *q = s;

	while(*p != '\0')
		if(*p != c)
			*q++ = *p++;
		else
			p++;

	*q = '\0';
}

//˼·����Ҫ������ָ�룻��Σ����ġ�\0'�ǵò���