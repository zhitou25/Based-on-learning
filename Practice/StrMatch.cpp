

#define size 1000//��ʼջ�Ĵ�С
typedef struct
{
	int stacksize;
	char *top;
	char *base;
}stack, *pstack;
void stackinit(pstack pp)//ջ��ʼ��
{

	pp->top = pp->base;
	pp->stacksize = size;
}

void push(pstack pp, char data)//ѹջ
{
	if ((pp->top - pp->base)>pp->stacksize)
	{
		pp->base = (char*)realloc(pp->base, sizeof(stack)*size * 2);
	}
	*(pp->top) = data;
	pp->top++;
}
bool pop(pstack pp)//��ջ
{
	if ((pp->top)>(pp->base))
	{
		pp->top--;
	}
	return false;
}

bool isValid(char* s) //�ַ���ƥ�亯��
{
	pstack pp;
	pp = (pstack)malloc(sizeof(stack));
	pp->base = (char*)malloc(sizeof(stack)*size);
	stackinit(pp);
	while (*s != '\0')
	{
		if (*s == '(' || *s == '[' || *s == '{')
		{
			push(pp, *s);
			s++;
			continue;
		}
		else if (pp->top - pp->base == 0) {
			return false;
		}
		else
		{
			if (*s == ')')
			{

				if (*(pp->top - 1) == '(')
				{
					pop(pp);
					s++;
					continue;
				}
				return false;
			}
			if (*s == ']')
			{
				if (*(pp->top - 1) == '[')
				{
					pop(pp);
					s++;
					continue;
				}
				return false;
			}
			if (*s == '}')
			{

				if (*(pp->top - 1) == '{')
				{
					pop(pp);
					s++;
					continue;
				}
				return false;
			}
		}

	}
	if (((pp->top) - (pp->base)) == 0)
		return true;
	return false;
}
