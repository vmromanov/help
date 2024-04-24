﻿#include "rgr.h"
#include <stdio.h>
#include <stdlib.h>




result* rgr(char* name)
{
	FILE* file = fopen(name, "r");
	if (file == NULL) { printf("cant open file"); return NULL; }
	char lastsimb = getc(file);

	char space; 
	unsigned int counter = 0;
	while ((space = fgetc(file)) != EOF)												
		if (space == ' '&& space!=EOF) ++counter;
	result* answers = malloc((counter-1) * sizeof(result));						
	if (answers == NULL) { printf("memmory allocation error(answers)"); return NULL; }
	
	fseek(file, 0, SEEK_SET); 

	unsigned int maxlen = 0;
	char c;
	unsigned int counterm = 0; // максимальная длинна слова
	while ((c = fgetc(file)) != EOF) 
	{
		counterm = 0;
		while ((c = fgetc(file) )!= ' ' && c != '\n' && c!='\0' && c!= EOF)
			counterm++;
		if (counterm > maxlen) maxlen = counterm;
	}
	for (unsigned int i = 0; i < counter-1; ++i)
	answers[i].where = calloc(counterm , sizeof(int));
	
	
	fseek(file, 0, SEEK_SET);
	while (lastsimb != EOF)
	{
		unsigned int counter1 = 0; 
		unsigned int counter2 = 0; 
		char simb;

		while ((simb = fgetc(file)) != ' ') 
			if (simb!=' ')counter1++;													

		while ((simb = fgetc(file)) != '\n' && simb != EOF)
			if (simb != '\n'&&simb!=' ')counter2++;											
		
		char* s1 = malloc(sizeof(char) * counter1);										
		if (s1 == NULL) { printf("s1 memmory allocation error"); return NULL; }

		char* s2 = malloc(sizeof(char) * counter2);										
		if (s2 == NULL) { printf("s2 memmory allocation error"); return NULL; }

		int elements = (int)(counter1 + counter2);
		fseek(file, -(elements)-3, SEEK_CUR); 

		
		unsigned int i = 0;
		if(i < (unsigned)counter && fscanf(file, "%[^ ] %[^\n]\n", s1, s2) == 2) {
			
			unsigned int amount = 0;
			unsigned int position = 0;
			for (unsigned int k = 0; k <= (counter1 - counter2); ++k) {
				int found = 1;
				for (unsigned int j = 0; j < counter2; ++j) 
				{
					char s1s = s1[k + j];
					char s2s = s2[j];
					if (s1s!=s2s) {
						found = 0;
						break;
					}
				}
				if (found == 1) 
				{
					position = k;
					answers[i].where[amount] = position;
					amount+=1;
					k += counter2 -1;
				}
				
			}
			
		}
		
		
		
		
		++i;
		lastsimb = fgetc(file);
		fseek(file, -1, SEEK_CUR);
		
		free(s1);free(s2);
	}
        
        for (unsigned int u=0;u<counter-1;++u)
        for (unsigned int m=0;m<counterm;++m)
        if ((answers[u].where[m])==0)
        if (m!=0)
        {
        answers[u].where = realloc(answers[u].where,(m+1)*sizeof(int));
        if ((answers[u].where)==NULL){printf("realloc error");return answers;}
        }
	for (unsigned int i = 0; i < counter-1; ++i) //counter кол-во пробелов +1;
	{
		printf("amount: %u\n", answers[i].amount);
		printf("positions: ");
		for (unsigned int j = 0; j < answers[i].amount; ++j)
			printf("%u ", answers[i].where[j]);
	}
	fclose(file);

	return answers;
}
