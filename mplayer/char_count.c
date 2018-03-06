#include "common.h"


char **count_order(void)
{
	FILE *fp;
	char buffer[80];
	int i = 0;
	char *name = "loadfile ./music/";
	static char *pname[10];
	char *s;

	fp = fopen("test", "r");
	if(fp == NULL)
		perror("fopen error!\n");	
	while(1) {

		s = fgets(buffer, 80, fp);
		if(s == NULL)
			break;
		pname[i] = malloc(100);
		strcpy(pname[i], name);
		strcat(pname[i], buffer);
//		printf("%s", pname[i]);
		i++;
	}

	fclose(fp);

	return pname;
}

 
char **count_lrc(void)
{
	FILE *fp;
	char buffer[80];
	int i = 0;
	int j = 0;
	char *name = "./music/";
	char *lname = ".lrc";
	char sname[70];
	static char *pname[10];
	char *s;

	fp = fopen("test2", "r");
	if(fp == NULL)
		perror("fopen error!\n");	
	while(1) {

		s = fgets(buffer, 80, fp);
		if(s == NULL)
			break;
		sscanf(buffer, "%[^.]", sname);	
		strcat(sname, lname);
		pname[i] = malloc(100);
		strcpy(pname[i], name);
		strcat(pname[i], sname);
/*		
		while(1) {
		
			if(pname[i][j] == '\n') {
				pname[i][j] = '\0';
				j = 0;
				break;
				}
			j++;
		}
*/		
//		printf("%s\n", pname[i]);
		i++;
	}

	fclose(fp);

	return pname;

}
