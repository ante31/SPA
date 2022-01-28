#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaèa)
	HashTable *nova = (HashTable*)malloc(sizeof(HashTable));
	nova->table = (Bin**)malloc(size * sizeof(Bin*));
	nova->size = size;
	nova->load = 0;
	for (int i = 0; i < nova->size; i++)
	{
		nova->table[i] = NULL;
	}
	return nova;
}

unsigned int hash(char *word)
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while (*word != '\0')
	{
		key = key * HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable *ht, char *word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu
	Bin *novi = (Bin*)malloc(sizeof(Bin));
	unsigned int i = hash(word) % ht->size;
	novi->word = word;
	novi->next = ht->table[i];
	ht->table[i] = novi;
	ht->load++;
}

int Get(HashTable *ht, char *word)
{
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici
	unsigned int i = hash(word) % ht->size;
	Bin *h = ht->table[i];
	while (h != NULL)
	{
		if (strcmp(h->word, word) == 0)
			return 0;
		else
			h = h->next;
	}
	return 1;
}

void DeleteTable(HashTable *ht)
{
	// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)
	for (int i = 0; i < ht->size; i++)
	{
		Bin *h = ht->table[i];
		while (h != NULL)
		{
			Bin *del = h;
			h = h->next;
			free(del->word);
			free(del);
		}
	}
	free(ht->table);
	free(ht);
}
