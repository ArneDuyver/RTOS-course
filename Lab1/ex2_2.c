#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    int child_pid = 0;
    printf("parent with pid = %ld is alive\n",getpid());
    fflush(stdout);
    
    child_pid = fork();
    if (child_pid == 0){
    	printf("\tchild with pid = %ld is alive\n", getpid());
    }

    for (int i = 1; i <= 5; i++){
        printf("This line is from pid %ld, value = %d\n", getpid(),i);
    }
    
    return(0);
}