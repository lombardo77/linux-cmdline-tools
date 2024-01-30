#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#define EN_NAME list[i]->d_name
#define BUF_SIZE 256

char dirBuf[BUF_SIZE];

void tab_by(int n){
	for(int i = 0; i < n; i++)
			printf("  ");
}

// returns 0 if directory, 1 if not directory
int isDir(const char* file_name){
	struct stat path;
	char buf[BUF_SIZE];
	snprintf(buf, BUF_SIZE, "%s%s",dirBuf, file_name);
	stat(buf, &path);
	return S_ISREG(path.st_mode);
}

void free_sndr(struct dirent ** list, int j){
	for (int i =0; i < j; i++){
		free(list[i]);
	}
	
}

void recur(DIR *dirIn, int depth, int i){
	struct dirent *entry;

	//new stuff
	struct dirent** list;
	int j = scandir(dirBuf, &list, NULL, alphasort);
	//end

	int err;
	char svpath[BUF_SIZE];
	while((entry = readdir(dirIn))){
		i++;
		if (i == j) break;
		if (EN_NAME[0] != '.'){
				if (!isDir(EN_NAME)){
					strcpy(svpath, dirBuf);

					//add dir to the path dirbuf
					err = snprintf(dirBuf, BUF_SIZE, "%s%s/",  svpath, EN_NAME);
					
					tab_by(depth);
					printf("- %s\n", EN_NAME);
					DIR * tmpdir = opendir(dirBuf);
					recur(tmpdir, depth + 1, 0);

					err = snprintf(dirBuf, BUF_SIZE, "%s", svpath);

					closedir(tmpdir);
				}
				else{
					tab_by(depth);
					printf("- %s\n", EN_NAME);
				}
		}
	}
	
	free_sndr(list, j);
	free(list);
}


int main(void){
		printf(".\n");	
		dirBuf[1] = '/';
		dirBuf[0] = '.';
		
		DIR* dir = opendir(".");

		recur(dir, 0, 0);
		closedir(dir);

		return 0;
}



