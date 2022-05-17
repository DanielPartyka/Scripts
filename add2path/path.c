#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define PATH_LENGTH 1000
#define BUFFER_SIZE 1000

void string_insert_and_replace(char *dest, char *src, size_t pos);
void replaceAll(char *str, const char *oldWord, const char *newWord);

int main(int argc, char *argv[]) {

	int choice = 0;
	FILE* fpointer;
	FILE* fTemp;
	char cwd[PATH_MAX];
	char buffer[BUFFER_SIZE];
	char oldWord[PATH_MAX] = "";

	printf("\nWitaj w programie dodajacym permamentnie zmienna PATH\n 1. Dodaj biezacy katalog do PATH\n 2. Usun biezacy katalog z PATH\n 3. Dodaj katalog do PATH jako parametr (sciezke)\n 4. Usun katalog z PATH podajac parametr(sciezke)\n Twoj wybor: "); scanf("%d",&choice);

	switch(choice) {

	case 1:

	if (getcwd(&cwd,sizeof(cwd)) != NULL) {

		fpointer = fopen("/etc/profile","a");
		char path_to_path_variable[PATH_LENGTH] = ("\n export PATH=\"$PATH:");
		int path_len = 0;
		int path_l = 0;
		char path_add[PATH_LENGTH] = ("\"");

		path_l = strlen(path_to_path_variable);
		string_insert_and_replace(path_to_path_variable,cwd,path_l);
		path_len = strlen(path_to_path_variable);
		string_insert_and_replace(path_to_path_variable,path_add,path_len);
		fprintf(fpointer,path_to_path_variable);
		fclose(fpointer);
		printf("\n Dodano biezacy katalog do PATH\n Prosze zrestartuj system aby zobaczyc efekty\n");
	}
	else {
		printf("Blad z pobraniem sciezki");
	}
	break;
	case 2:
	
	fpointer = fopen("/etc/profile","r");
	fTemp = fopen("delete.txt", "w");
	char path_of_var[PATH_LENGTH] = ("export PATH=\"$PATH:");
	int pathlength = 0;
	int pathlength_2 = 0;
	char pathad[PATH_LENGTH] = ("\"");

	if (getcwd(&cwd,sizeof(cwd)) != NULL) {


	pathlength_2 = strlen(path_of_var);
	string_insert_and_replace(path_of_var,cwd,pathlength_2);
	pathlength = strlen(path_of_var);
	string_insert_and_replace(path_of_var,pathad,pathlength);

    	while ((fgets(buffer, BUFFER_SIZE, fpointer)) != NULL)
    	{
    	    replaceAll(buffer,path_of_var,oldWord);
            fputs(buffer, fTemp);
    	}


	fclose(fpointer);
	fclose(fTemp);
	fTemp = fopen("delete.txt", "r");
	fpointer = fopen("/etc/profile","w");

	while ((fgets(buffer, BUFFER_SIZE, fTemp)) != NULL)
    	{
            fputs(buffer, fpointer);
    	}
	fclose(fpointer);
	fclose(fTemp);
	remove("delete.txt");
	printf("\n Usunieto biezacy katalog z PATH\n Prosze zrestartuj system aby zobaczyc efekty\n");

	} else {
		printf("Blad z usunieciem biezacego katalogu z PATH");
	
	}
	break;

	case 3:

	fpointer = fopen("/etc/profile","a");
	char* path_of_directory[PATH_LENGTH];
	char path_to_path_variable[PATH_LENGTH] = ("\n\nexport PATH=\"$PATH:");
	int path_len = 0;
	int path_l = 0;
	char path_add[PATH_LENGTH] = ("\"");

	printf("Podaj sciezke do katalogu: "); scanf("%s",&path_of_directory);
	mkdir(&path_of_directory, 0700);
	path_l = strlen(path_to_path_variable);
	string_insert_and_replace(path_to_path_variable,path_of_directory,path_l);
	path_len = strlen(path_to_path_variable);
	string_insert_and_replace(path_to_path_variable,path_add,path_len);
	fprintf(fpointer,path_to_path_variable);
	fclose(fpointer);
	printf("\n Dodano katalog %s do zmiennej PATH\n Prosze zrestartuj system aby zobaczyc efekty\n",&path_of_directory);
	break;

	case 4:

	fpointer = fopen("/etc/profile","r");
	fTemp = fopen("delete.txt", "w+");
	char* path_of_d[PATH_LENGTH];
	char path_of_v[PATH_LENGTH] = ("export PATH=\"$PATH:");
	int path_length = 0;
	int path_length_2 = 0;
	char path_ad[PATH_LENGTH] = ("\"");

	printf("Podaj sciezke do usuniecia: "); scanf("%s",&path_of_d);

	path_length_2 = strlen(path_of_v);
	string_insert_and_replace(path_of_v,path_of_d,path_length_2);
	path_len = strlen(path_of_v);
	string_insert_and_replace(path_of_v,path_ad,path_len);
	printf("%s",&path_of_d);
	while ((fgets(buffer, BUFFER_SIZE, fpointer)) != NULL)
    	{
    	    replaceAll(buffer,path_of_v,oldWord);
            fputs(buffer, fTemp);
    	}

	fclose(fpointer);
	fclose(fTemp);
	fTemp = fopen("delete.txt", "r");
	fpointer = fopen("/etc/profile","w");

	while ((fgets(buffer, BUFFER_SIZE, fTemp)) != NULL)
    	{
            fputs(buffer, fpointer);
    	}
	fclose(fpointer);
	fclose(fTemp);
	remove("delete.txt");
	printf("\n Usunieto katalog %s ze zmiennej PATH\n Prosze zrestartuj system aby zobaczyc efekty\n",&path_of_directory);	
	break;
	
	default:
		printf("Zly wybor");
	break;	
	}
	return 0;
}
void string_insert_and_replace(char *dest, char *src, size_t pos)
{
    while (*src) {

	*(dest + pos) = *src;
        dest++, src++;
    }
}
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    while ((pos = strstr(str, oldWord)) != NULL)
    {
        
        strcpy(temp, str);
	index = pos - str;
	str[index] = '\0';
	strcat(str, newWord);
	strcat(str, temp + index + owlen);
    }
}

