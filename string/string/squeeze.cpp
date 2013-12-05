
// 将s中的字符c剔除
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

//思路很重要，两个指针；其次，最后的‘\0'记得补上