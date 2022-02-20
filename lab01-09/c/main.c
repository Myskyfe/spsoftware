#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PROCESS_QUANTITY 9

void child(int i)
{
    FILE * t = fopen("file_v4", "w");

    fprintf(t, "Child number %d, ID %d Son: %d Parent %d \n", i,  getpid(), getpid() + 1, getppid());
    
    int pid;

    if (i == PROCESS_QUANTITY)
        return;
    pid = fork();
    if (pid < 0){
        ;
    }
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);

    fclose(t);

    exit(0);
}

int main() {
    int i = 0;  
    int pid = fork();
    if (pid < 0)
        ;
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);

    char strMass[PROCESS_QUANTITY + 1][80];

    FILE * u = fopen("file_v4", "r");

    int k = 0,
        l = 0;

    while(!feof(u)){
        char j = fgetc(u);
        if(j == '\n'){
            k++;
            l = 0;
        }
        else{
            strMass[k][l] = j;
            l++;
        }
    }

    for(int i = PROCESS_QUANTITY -2; 
        i >= 1; 
        --i)
        printf("%s\n", strMass[i]);

    fclose(u);

    exit(1);

}