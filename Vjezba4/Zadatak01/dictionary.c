#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
// kreira novi prazni rjecnik
Dictionary create()
{
	Dictionary w = (Dictionary)malloc(sizeof(Word));
	w->word = " ";
	w->count = 0;
	w->next = NULL;
	return w;
}
// briše cijeli rjeènik
void destroy(Dictionary dict)
{
	Dictionary tmp = dict;
	while (tmp->next != NULL)
	{
		Dictionary del = tmp->next;
		tmp->next = tmp->next->next;
		free(del->word);
		free(del);
	}
}
// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict)
{
	Dictionary s = dict;
	s = s->next;
	while (s != NULL)
	{
		printf("%s", s->word);
		printf(" %d\n", s->count);
		s = s->next;
	}
}
// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str)
{
	Dictionary q = dict;
	while (q->next != NULL)
	{
		if (strcmp(str, q->next->word) < 0)
		{
			Dictionary novi = (Dictionary)malloc(sizeof(Word));
			novi->word = _strdup(str);
			novi->count = 1;
			novi->next = q->next;
			q->next = novi;
			return;
		}
		else if (strcmp(str, q->next->word) == 0)
		{
			q->next->count++;
			return;
		}
		q = q->next;
	}
	q->next = (Dictionary)malloc(sizeof(Word));
	q->next->word = _strdup(str);
	q->next->count = 1;
	q->next->next = NULL;
}
int filter(Word* w)
{
	return (w->count >= 5 && w->count <= 10 && strlen(w->word) > 3);
}
Dictionary filterDictionary(Dictionary indict)
{
	Dictionary tmp = indict;
	if (tmp->next == NULL)
	{
		return NULL;
	}
	while (tmp->next != NULL)
	{
		if (filter(tmp->next))
		{
			tmp = tmp->next;
		}
		else
		{
			Dictionary del = tmp->next;
			tmp->next = tmp->next->next;
			free(del->word);
			free(del);
		}
	}
	return indict;
}
