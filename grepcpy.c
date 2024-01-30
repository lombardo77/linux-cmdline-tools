/*returns 1 if substring in string else returns 0*/
int grep(char * str, char* substr, int s_s, int s_st){
/*	printf("this is buf_s %s this is sub_c%s\n", str, substr);*/
	int i = 0;
	for(int x = 0; x < s_s; x ++){
		if(str[x] == substr[0]){
			while(str[x + i] == substr[i]){
				i++;
				if (i == s_st)
					return 1;
			}
			i = 0;
		}
		
	}
	return 0;

}

