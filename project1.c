#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>

//Functions
int display(int text);
int input_Check(int option);
int num_lines(void *file);
FILE* file_picked(int num_file);

int main()
{
    struct timeval start_time, end_time;
    float total_time;
    FILE *file;
    int num_proc = 0, num_file = 0, lines_proc = 0, total_lines = 0;

    //this is where we get 
    num_proc = display(1);
    num_file = display(2);

    pid_t PIDS[num_proc];

    //Selects what file to open based on what user picked
    file = file_picked(num_file);

    //Counts how many lines are in the file
    total_lines = num_lines(file);
    lines_proc = total_lines / num_proc;
    int file_result[total_lines];
    fclose(file);
    printf("There are %d lines in the file you chose\n", total_lines);

    //Creates the exact number of pipes needed
    int fds[num_proc][2];
    for(int i = 0; i < num_proc; i++)
    {
        pipe(fds[i]);
    }

    //This creates the the number of processes the user selected
    long long proc_result = 0;
    long long answer = 0;
    long long results = 0;
    unsigned int start;
    gettimeofday(&start_time, NULL); //Starts timer
    for(int i = 0; i < num_proc; i++)
    {   
        PIDS[i] = fork();
        if(PIDS[i] == 0)
        {
            printf("Process %d is starting\n", i + 1);
            file = file_picked(num_file);
            start = (lines_proc * i * 5);
            int temp = 0;
            
            fseek(file, start, SEEK_SET);
            for(int j = 0; j < lines_proc; j++)
            {
                if(fscanf(file, "%d", &temp) == 1)
                {
                    proc_result = proc_result + temp;
                }
            }
            write(fds[i][1], &proc_result, sizeof(long long));
            close(fds[i][1]);
            close(fds[i][0]);
            printf("Process %d is finished\n", i + 1);
            fclose(file);
            _exit(0);
        }
        else if(PIDS[i] == -1) //This is incase a process couldn't be created
        {
            printf("An error has occurred creating process %d\n", i+1);
            _exit(0);
        }
    }
    
    //This reads all of the values recieved from the child processes
    //and adds them together to get the final result
    for(int i = 0; i < num_proc; i ++)
    {
        read(fds[i][0], &results, sizeof(long long));
        answer = answer + results;
        close(fds[i][0]);
        close(fds[i][1]);
    }
    gettimeofday(&end_time, NULL); //Ends timer
    wait(NULL);

    total_time = ((float)((end_time.tv_sec - start_time.tv_sec) * 1000000 + end_time.tv_usec - start_time.tv_usec) / 1000); //This calculates the time it took
    printf("It took this long: %.3f ms\n", total_time);
    printf("The total sum is: %lld\n", answer);
    
}

//Opens the file the user picked
FILE* file_picked(int num_file)
{
    FILE *file;
    switch(num_file)
    {
        case 1:
            file = fopen("file1.dat", "rb");
            break;
        case 2:
            file = fopen("file2.dat", "rb");
            break;
        case 3:
            file = fopen("file3.dat", "rb");
            break;
    }
    return file;
}

//Counts the amount of lines in the file
int num_lines(void *file)
{
    int temp = 0;
    int total_lines = 0;
    while(fscanf(file, "%d", &temp) == 1)
    {
        total_lines++;
    }
    return total_lines;
}

//Asks the user how many processes they want to make
//Also asks which file they want to go through
int display(int text)
{
    int input = 0;
    switch (text)
    {
        case 1:
            printf("How many processes do you want to create? \n1\n2\n4\n");
            input = input_Check(1);
            break;
        case 2:
            printf("Which file do you want to parse through? \n1. file1\n2. file2\n3. file3\n");
            input = input_Check(0);
            break;
        case 3:
            break;
    }
    return input;
}

//Checks if the users input is valid
int input_Check(int option)
{
    int temp = 0;
    while(1)
    {
        scanf("%d", &temp);
        while((getchar()) != '\n');
        if(option == 1)
        {
            if(temp == 1 || temp == 2 || temp == 4)
            {
                return temp;
            }
            else
            {
                printf("Your input is not valid\nTry again\n");
            }
        }
        else if(option == 0)
        {
            if(temp <= 0 || temp >= 4)
            {
                printf("Your input is not valid\nTry again\n");
            }
            else
            {
                return temp;
            }
        }
    }
}