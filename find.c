#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "grepcpy.h"

#define EN_NAME entry->d_name
#define BUF_SIZE 256
#define NAME finf_arr[i]->name

char dirBuf[BUF_SIZE];

typedef struct file_info{
	char* name;
	char* path;
}finf;

finf** finf_arr;
int p;

// returns 0 if directory, 1 if not directory
int isDir(const char* file_name){
	struct stat path;
	char buf[BUF_SIZE];
	snprintf(buf, BUF_SIZE, "%s%s",dirBuf, file_name);
	stat(buf, &path);
	return S_ISREG(path.st_mode);
}



void recur(DIR *dirIn, int depth){
	struct dirent *entry;
	int err;
	char svpath[BUF_SIZE];
	while((entry = readdir(dirIn))){
		if (EN_NAME[0] != '.'){
				if (!isDir(EN_NAME)){
					strcpy(svpath, dirBuf);

					//add dir to the path dirbuf
					err = snprintf(dirBuf, BUF_SIZE, "%s%s/",  svpath, EN_NAME);
					

					// copy svpath and EN_NAME into new char*, then create a new struct
					// then put that stuct into an array of type finf*
					char* pth_cpy = (char*)malloc(strlen(svpath) + 1);
					char* nme_cpy = (char*)malloc(strlen(EN_NAME) + 1);
					finf* tmp_finf = (finf*)malloc(sizeof(finf));
					
					// copy strings
					strcpy(pth_cpy, svpath);
					strcpy(nme_cpy, EN_NAME);
					
					// add strings to struct
					tmp_finf->name = nme_cpy;
					tmp_finf->path = pth_cpy;
					
					// add struct to list
					finf_arr = (finf**)realloc(finf_arr, (p + 1)*sizeof(finf));
					finf_arr[p] = tmp_finf;

					// iterate struct
					p ++;

					//open new dir to recurse
					DIR * tmpdir = opendir(dirBuf);
					recur(tmpdir, depth + 1);
					
					// go back to old path
					err = snprintf(dirBuf, BUF_SIZE, "%s", svpath);

					// close tmp dir
					closedir(tmpdir);
				}
				else{
					// copy svpath and EN_NAME into new char*, then create a new struct
					// then put that stuct into an array of type finf*
					char* pth_cpy = (char*)malloc(strlen(dirBuf)+1);
					char* nme_cpy = (char*)malloc(strlen(EN_NAME)+1);
					finf* tmp_finf = (finf*)malloc(sizeof(finf));
					
					// copy strings
					strcpy(pth_cpy, dirBuf);
					strcpy(nme_cpy, EN_NAME);
					
					// add strings to struct
					tmp_finf->name = nme_cpy;
					tmp_finf->path = pth_cpy;
					
					// add struct to list
					finf_arr = (finf**)realloc(finf_arr, (p + 1)*sizeof(finf));
					finf_arr[p] = tmp_finf;


					finf_arr[p] = tmp_finf;
					p ++;

				}
		}
	}
}

void free_finf(void){

		for (int i=0; i< p; i++){
			free(finf_arr[i]->name);
			free(finf_arr[i]->path);
			free(finf_arr[i]);
		}
		free(finf_arr);
}

int main(int argc, char** argv){
		
		if (argc != 2) return 1;

		dirBuf[1] = '/';
		dirBuf[0] = '.';
		
		DIR* dir = opendir(".");
		
		//init finf array
		finf_arr = (finf**)malloc(1);

		recur(dir, 0);
		
		for(int i=0; i < p; i++){
				if(grep(NAME, argv[1], strlen(NAME), strlen(argv[1])) == 1)
					printf("%s%s\n", finf_arr[i]->path, NAME);
		}
		closedir(dir);
		free_finf();

		return 0;
}








