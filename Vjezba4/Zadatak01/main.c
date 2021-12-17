#include "dictionary.h"
int readWord(FILE* fd, char* buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

void main()
{
	FILE* fd;
	char buffer[1024];
	Dictionary dict, dict2, dict3;

	fd = fopen("liar.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	//dict=create()
	dict = create();
	dict3 = create();

	while (readWord(fd, buffer))
	{
		//sve rijeèi
		//printf("%s\n", buffer);
		add(dict, buffer);
	}
	fclose(fd);

	dict = filterDictionary(dict);

	print(dict);

	destroy(dict);

}
