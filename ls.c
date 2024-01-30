#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include "sort.h"

#define TIMEBUF 100


int dir_size;

char** getdir(DIR * d){
	//DIR * d = opendir(".");
	struct dirent *e;
	
	e = readdir(d);
	char ** dirar = malloc(sizeof(e->d_name));
	dirar[0] = e->d_name;
	dir_size ++;
	int p = 0;
	while((e=readdir(d))){
		if (e->d_name[0] != '.'){
			dirar = realloc(dirar, sizeof(dirar) + sizeof(e->d_name));
			dirar[p] = e->d_name;
			p++;
			dir_size ++;
		}
	}
	/*sort the files*/
	sort(dirar, 0, dir_size - 2);
	return dirar;
}


void reg(){
		DIR * d = opendir(".");
		char** files = getdir(d);
		
		for (int i = 0; i < dir_size - 1; i++)
				printf("%s\n", files[i]);
		closedir(d);
		free(files);
}

void lflag(){

	char buf[TIMEBUF];
	struct stat statbuf;
	//struct dirent *e;

	DIR * d = opendir(".");;

	char ** files = getdir(d);	
	
	struct passwd *pw;
	struct group *gr;
	stat("a", &statbuf);
	//time_t t;

	for(int i = 0; i < dir_size - 1 ; i++){
			stat(files[i], &statbuf);
			pw = getpwuid(statbuf.st_uid);
			gr = getgrgid(statbuf.st_gid);
			

			printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
			printf( statbuf.st_mode & S_IRUSR ? "r" : "-");
			printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
			
			printf(" %s", pw->pw_name);
			printf(" %s", gr->gr_name);
			printf(" %ld\t", statbuf.st_size);
			
			strftime(buf, TIMEBUF, "%b %d %H:%M", localtime(&statbuf.st_ctime));
			printf(" %s", buf);
			printf(" %s",files[i]);
			printf("\n");
	}
	closedir(d);
	free(files);
}

int main(int argc, char** argv){
	if (argc == 1)
		reg();
	else if (strcmp(argv[1], "-l") == 0){
		lflag();
	}
	else
		printf("don't recognize flag\n");
	return 0;
}


