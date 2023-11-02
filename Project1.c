#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>

int display(int text);
int input_Check(int option);
int num_lines(void *file);

//Global variables




int main()
{
    clock_t start_time, end_time;
    double total_time;
    
    FILE* file;
    int num_proc = 0;
    int num_file = 0;
    int lines_proc = 0;
    int total_lines = 0;

    //This is the part of the code where the 

    num_proc = display(1);
    num_file = display(2);

    pid_t PIDS[num_proc];

    //Selects what file to open based on what user picked
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

    //Counts how many lines are in the file
    total_lines = num_lines(file);
    lines_proc = total_lines / num_proc;
    int file_result[total_lines];
    printf("There are %d lines in the file you chose\n", total_lines);

    //Moves the pointer back to the beginning of the file
    

    //This part of the code is where the main process sets up the processes

    //Creates the exact number of pipes needed
    int fds[num_proc][2];
    for(int i = 0; i < num_proc; i++)
    {
        pipe(fds[i]);
    }

    //This creates the the number of processes the user selected
    long long proc_result = 0;
    long long results[num_proc];
    long long answer = 0;
    
    unsigned int start, end , ptr = 0;
    start_time = clock();
    for(int i = 0; i < num_proc; i++)
    {
        //rewind(file);
        //ptr = start;
        //fflush(stdin);
        PIDS[i] = fork();
        //int PID = fork(); 
        if(PIDS[i] == 0)
        {
            //char num[6];
            //setbuf(file, NULL);
            printf("Process %d is starting\n", i + 1);
            start = (lines_proc * i * 5);
            end = start + (lines_proc * 5);
            printf("Start: %d, End: %d\n", start, end);
            int temp = 0;
            int test = 0;
            
            
            if(i == 0)
            {
                ptr++;
            }
            else
            {
                ptr = (start / (5*i)) + 1;
            }
           //printf("%d\n", i);
           //printf("Start: %d End: %d\n", start, end);
           // printf("This is where the current pointer is located: %d\n", ptr);
           fseek(file, start, SEEK_SET);
           // printf("value of temp: %d\n", temp);
           for(int j = 0; j < lines_proc; j++)
           {
                //temp = 0;
                //ret = ;
                //fgets(num, sizeof(num), file) != NULL
                if(fscanf(file, "%d", &temp) == 1)
                {
                    //temp = atoi(num);
                    //sscanf(num, "%d", &temp);
                    // if(j == lines_proc - 1)
                    // {
                    //     printf("Process %d: ptr: %d, value: %d, j:%d\n", i+1, ptr, temp, j);
                    // }
                    if(i == 1)
                    {
                        printf("Process %d: ptr: %d, value: %d, j:%d ftell: %ld\n", i+1, ptr, temp, j, ftell(file));
                    }
                    ptr++;
                    proc_result = proc_result + temp;
                }
            }
            write(fds[i][1], &proc_result, sizeof(long));
            close(fds[i][1]);
            close(fds[i][0]);
            printf("Process %d is finished\n", i + 1);
            _exit(0);
        }
        else if(PIDS[i] == -1)
        {
            printf("An error has occurred creating a process\n");
            
        }
    }
    //parent waits for children to be done
    for(int i = 0; i < num_proc; i++)
    {
        wait(NULL);
    }
    
    for(int i = 0; i < num_proc; i ++)
    {
        read(fds[i][0], &results[i], sizeof(long long));
        close(fds[i][0]);
        close(fds[i][1]);
    }
    end_time = clock();
    wait(NULL);
    total_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("It took this long: %f\n", total_time);
    
    for(int i = 0; i < num_proc; i++)
    {
        answer = answer + results[i];
    }

    printf("The total sum is: %lld\n", answer);
    
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

int input_Check(int option)
{
    int temp = 0;
    while(1)
    {
        scanf("%d", &temp);
        while((getchar()) != '\n');
        if(option == 1)
        {
            if(temp <= 0 || temp == 3 || temp > 4)
            {
                printf("Your input is not valid\nTry again\n");
            }
            else
            {
                return temp;
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
        
        // if(temp >= 4)
        // {
        //     printf("Your input is not valid\nTry again\n");
        // }
        // else if (temp <= 0 || temp != 3 || temp > 4)
        // {
        //     printf("Your input is not valid\nTry again\n");
        // }
        // else
        // {
        //     break;
        // }
    }
    //return temp;
}