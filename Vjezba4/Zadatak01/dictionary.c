#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// kreira novi prazni rjecnik
Dictionary create()
{
	Dictionary dict = (Dictionary)malloc(sizeof(Word));
	dict->word = "";
	dict->count = 0;
	dict->next = NULL;
	return dict;
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
	Dictionary tmp = dict;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		printf("%s", tmp->word);
		printf(" %d\n", tmp->count);
		tmp = tmp->next;
	}
}
// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str)
{
	Dictionary tmp = dict;
	while (tmp->next != NULL)
	{
		if (strcmp(str, tmp->next->word) < 0)
		{
			Dictionary novi = (Dictionary)malloc(sizeof(Word));
			novi->word = _strdup(str);
			novi->count = 1;
			novi->next = tmp->next;
			tmp->next = novi;
			return;
		}
		else if (strcmp(str, tmp->next->word) == 0)
		{
			tmp->next->count++;
			return;
		}
		tmp = tmp->next;
	}
	tmp->next = (Dictionary)malloc(sizeof(Word));
	tmp->next->word = _strdup(str);
	tmp->next->count = 1;
	tmp->next->next = NULL;
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
			Dictionary t = tmp->next;
			tmp->next = tmp->next->next;
			free(t->word);
			free(t);
		}
	}
	return indict;
}
