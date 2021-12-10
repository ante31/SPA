#include "longnumber.h"
//promini
LongNumber reverse(LongNumber num)
{
	LongNumber okrenuti = NULL;
	while (num != NULL)
	{
		LongNumber preb = num;
		num = num->next;
		preb->next = okrenuti;
		okrenuti = preb;
	}
	return okrenuti;
}

LongNumber dodaj_u_glavu(LongNumber lst, int broj)
{
	LongNumber novi = (LongNumber)malloc(sizeof(Digit));
	novi->z = broj;
	novi->next = lst;
	return novi;
}

LongNumber read_longnum(char* fname)
{
	FILE* f;
	LongNumber num = NULL;
	f = fopen(fname, "r");
	int broj;
	int c;
	for (c = getc(f); c != EOF; c = getc(f))
	{
		c = c - 48;
		num = dodaj_u_glavu(num, c);
	}
	num = reverse(num);
	return num;
}
void write_longnum(LongNumber num, char* fname)
{
	FILE* f;
	f = fopen(fname, "w");
	while (num != NULL)
	{
		fprintf(f, "%d", num->z);
		num = num->next;
	}
}
void print_longnum(LongNumber num)
{
	while (num != NULL)
	{
		printf("%d", num->z);
		num = num->next;
	}
	printf("\n");
}
void delete_longnum(LongNumber num)
{
	while (num != NULL)
	{
		LongNumber tmp = num;
		num = num->next;
		free(tmp);
	}
}
LongNumber dodaj_na_kraj(LongNumber lst, int broj) {
	LongNumber novi = (LongNumber)malloc(sizeof(Digit));
	novi->z = broj;
	novi->next = NULL;

	if (lst == NULL) {
		return novi;
	}

	LongNumber tmp = lst;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	tmp->next = novi;
	return lst;
}

LongNumber add_longnum(LongNumber a, LongNumber b)
{
	LongNumber c = NULL;
	int ostatak = 0;
	LongNumber tmpA = a;
	LongNumber tmpB = b;
	tmpA = reverse(tmpA);
	tmpB = reverse(tmpB);
	LongNumber tmptmpA = tmpA;
	LongNumber tmptmpB = tmpB;
	
	while (tmpA != NULL && tmpB != NULL)
	{
		int broj = tmpA->z + tmpB->z;
		if (broj + ostatak > 9)
		{
			int znam = broj % 10;
			c = dodaj_u_glavu(c, (znam + ostatak) % 10);
			ostatak = 1;
		}
		else
		{
			c = dodaj_u_glavu(c, broj + ostatak);
			ostatak = 0;
		}
		tmpA = tmpA->next;
		tmpB = tmpB->next;
	}
	while (tmpA != NULL) {
		//a jos postoji
		c = dodaj_u_glavu(c, (tmpA->z+ostatak)%10);
		if (a->z + ostatak > 9) {
			ostatak = 1;
		}
		else {
			ostatak = 0;
		}
		tmpA = tmpA->next;

	}
	while (tmpB != NULL) {
		c = dodaj_u_glavu(c, (tmpB->z + ostatak) % 10);
		if (tmpB->z + ostatak > 9) {
			ostatak = 1;
		}
		else {
			ostatak = 0;
		}
		tmpB = tmpB->next;
	}

	if (ostatak)
	{
		c = dodaj_u_glavu(c, ostatak);
	}
	delete_longnum(tmpA);
	delete_longnum(tmpB);
	a = reverse(tmptmpA);
	b = reverse(tmptmpB);
	return c;

}
LongNumber mul_by_digit(LongNumber num, int x)
{
	LongNumber numd = NULL;
	LongNumber tmp = num;
	tmp = reverse(tmp);
	LongNumber tmptmp = tmp;
	int ostatak = 0;
	while (tmp != NULL)
	{
		if (tmp->z * x > 9)
		{
			int znam = (tmp->z * x) % 10;
			numd = dodaj_u_glavu(numd, (znam + ostatak) % 10);
			ostatak = (tmp->z * x + ostatak) / 10;
		}
		else
		{
			numd = dodaj_u_glavu(numd, (tmp->z * x) + ostatak);
			ostatak = 0;
		}
		tmp = tmp->next;
	}
	if (ostatak)
	{
		numd = dodaj_u_glavu(numd, ostatak);
	}
	num = reverse(tmptmp);
	delete_longnum(tmp);
	return numd;
}
LongNumber mul_by_pow10(LongNumber num, int pow)
{
	LongNumber tmp = num;
	LongNumber nume = NULL;
	while (tmp != NULL)
	{
		nume = dodaj_u_glavu(nume, tmp->z);
		tmp = tmp->next;
	}
	for (int i = 0; i < pow; i++)
	{
		nume = dodaj_u_glavu(nume, 0);
	}
	nume = reverse(nume);
	delete_longnum(tmp);
	return nume;
}

LongNumber mul_longnum(LongNumber numa, LongNumber numb)
{
	LongNumber pomocni = NULL;
	LongNumber numf = NULL;
	LongNumber tmpA = numa;
	LongNumber tmpB = numb;
	int br = 0;
	int i = 0;
	tmpB = reverse(tmpB);
	LongNumber tmptmpB = tmpB;
	while (tmpB != NULL)
	{
		pomocni = mul_by_pow10(tmpA, i);
		pomocni = mul_by_digit(pomocni, tmpB->z);
		i++;
		numf = add_longnum(numf, pomocni);
		tmpB = tmpB->next;
	}
	tmptmpB = reverse(tmpB);
	delete_longnum(tmpB);
	delete_longnum(pomocni);
	return numf;
}
