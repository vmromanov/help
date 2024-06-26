﻿#include "rgr.h"
#include <stdio.h>
#include <stdlib.h>




result* rgr(char* name)
{
	FILE* file = fopen(name, "r");
	if (file == NULL) { printf("cant open file"); return NULL; }

	char space;
	unsigned int counter = 0;

	while ((space = fgetc(file)) != EOF)
		if (space == ' ' && space != EOF && space != '\0') ++counter;


	result* answers = malloc((counter) * sizeof(result));
	if (answers == NULL) { printf("memmory allocation error(answers)"); return NULL; }

	for (unsigned int i = 0; i < counter; ++i)
		(answers[i].amount) = 0;

	fseek(file, 0, SEEK_SET);
	for (unsigned int i = 0; i < counter; ++i)
	{
		unsigned int counter1 = 0;
		unsigned int counter2 = 0;
		char simb;

		while ((simb = fgetc(file)) != ' ')
			if (simb != ' ')counter1++;

		while ((simb = fgetc(file)) != '\n' && simb != EOF)
			if (simb != '\n' && simb != ' ')counter2++;

		char* s1 = malloc(sizeof(char) * (counter1+1));
		if (s1 == NULL) { printf("s1 memmory allocation error"); return NULL; }
                  
		char* s2 = malloc(sizeof(char) * (counter2+1));
		if (s2 == NULL) { printf("s2 memmory allocation error"); return NULL; }
                  
		int elements = (int)(counter1 + counter2);
		fseek(file, -(elements)-3, SEEK_CUR);


                char ch;
               unsigned int u=0;
               while ((ch=fgetc(file))!=' ')
               {s1[u]=ch;++u;}
               u=0;
               while ((ch=fgetc(file))!='\0'&& ch!='\n'&& ch!=EOF)
               {s2[u]=ch;++u;}
		s1[counter1]='\0';
		s2[counter2]='\0'; 
			unsigned int amount = 0;
			for (unsigned int k = 0; k <= (counter1 - counter2); ++k) {
				int found = 1;
				for (unsigned int j = 0; j < counter2; ++j)
				{
				
					if (s1[k + j] != s2[j]) 
					{
						found = 0;
						break;
					}
				}
				if (found == 1)
				{
					amount += 1;
					k += counter2 - 1;
				}

			}
			(answers[i].amount) = amount;
		


		fseek(file, -1, SEEK_CUR);

	}

	for (unsigned int i = 0; i < counter; ++i)
	{
		unsigned int amount = (answers[i].amount);
		answers[i].where = malloc(amount * sizeof(unsigned int));

		for (unsigned int j = 0; j < amount; ++j)
			(answers[i].where[j]) = 0;
	}

	fseek(file, 0, SEEK_SET);

	for (unsigned int i = 0; i < counter; ++i)
	{
		unsigned int counter1 = 0;
		unsigned int counter2 = 0;
		char simb;

		while ((simb = fgetc(file)) != ' ')
			if (simb != ' ')counter1++;

		while ((simb = fgetc(file)) != '\n' && simb != EOF)
			if (simb != '\n' && simb != ' ')counter2++;

		char* s1 = malloc(sizeof(char) * (1+counter1));
		if (s1 == NULL) { printf("s1 memmory allocation error"); return NULL; }

		char* s2 = malloc(sizeof(char) * (1+counter2));
		if (s2 == NULL) { printf("s2 memmory allocation error"); return NULL; }

		int elements = (int)(counter1 + counter2);
		fseek(file, -(elements)-3, SEEK_CUR);

                char ch;
               unsigned int u=0;
               while ((ch=fgetc(file))!=' ')
               {s1[u]=ch;++u;}
               u=0;
               while ((ch=fgetc(file))!='\0'&& ch!='\n'&& ch!=EOF)
               {s2[u]=ch;++u;}
		s1[counter1]='\0';
		s2[counter2]='\0';

			unsigned int amount = 0;
			for (unsigned int k = 0; k <= (counter1 - counter2); ++k) {
				int found = 1;
				for (unsigned int j = 0; j < counter2; ++j)
				{
				    
					if (s1[k + j] != s2[j]) {
						found = 0;
						break;
					}
				}
				if (found == 1)
				{
					(answers[i].where[amount]) = k;
					amount++;
					k += counter2 - 1;
				}
			}
		

            free(s1);
            free(s2);
	}


	for (unsigned int i = 0; i < counter; ++i)
	{
		printf("\namount: %u\n", answers[i].amount);
		printf("positions: ");
		for (unsigned int j = 0; j < answers[i].amount; ++j)
			printf("%u ", answers[i].where[j]);
	}
	
	fclose(file);
	return answers;
}

