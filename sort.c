#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int partition_alph(char** arr, int lo, int hi){
	int piv = arr[hi][0];
	int i = lo - 1;
	char* tmp;
	for(int j = lo; j <= hi - 1; j ++){
		
		if (tolower(arr[j][0]) < tolower(piv)){
			i++;
			
			/*swapping i and j*/
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		
			
	}
	tmp = arr[i+1];
	arr[i+1] = arr[hi];
	arr[hi] = tmp;

	return i + 1;

}

void sort(char** arr, int lo, int hi){

	int p;
	if (lo < hi){

		p = partition_alph(arr, lo, hi);
		sort(arr, lo, p - 1);
		sort(arr, p + 1, hi);
	
	}

}
