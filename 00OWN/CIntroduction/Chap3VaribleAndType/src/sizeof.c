#include <stdio.h>

int main(){
	short a = 10;
	int b = 100;

	int short_len =  sizeof a;
	int int_len = sizeof(b);
	int long_len =  sizeof(long);
	int char_len =  sizeof(char);

    printf("short=%d, int=%d, long=%d, char=%d\n", short_len, int_len, long_len, char_len);
   
    return 0;
}
