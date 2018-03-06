#include "common.h"

int main(void)

{
	DIR *pdir;
	struct dirent *ps;
	char *temp;
	FILE *fp;
	FILE *fp1;

	pdir = opendir("./music");
	fp = fopen("test", "w+");
	fp1 = fopen("test2", "w+");
	while(1) {
		ps = readdir(pdir);
		if(ps != NULL) {
			if((strcmp(ps->d_name, ".") != 0) && (strcmp(ps->d_name, "..") != 0)) {
				sscanf(ps->d_name, "%*[^.].%s", temp);
				if(strcmp(temp, "mp3") == 0) {
					fputs(ps->d_name, fp);
					fputc('\n', fp);
					fputs(ps->d_name, fp1);
					fputc('\n', fp1);

					}
				}
			}

			else 
				break;

			}	

	fclose(fp);
	fclose(fp1);
	closedir(pdir);


	return 0;


}
