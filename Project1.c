#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

int display(int text);
int input_Check(int option);
int num_lines(void *file);

//Global variables
long long answer = 0;



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


    //Selects what file to open based on what user picked
    switch(num_file)
    {
        case 1:
            file = fopen("file1.dat", "r");
            break;
        case 2:
            file = fopen("file2.dat", "r");
            break;
        case 3:
            file = fopen("file3.dat", "r");
            break;
    }

    //Counts how many lines are in the file
    total_lines = num_lines(file);
    lines_proc = total_lines / num_proc;
    int file_result[total_lines];
    printf("There are %d lines in the file you chose\n", total_lines);

    //Moves the pointer back to the beginning of the file
    rewind(file);

    //This part of the code is where the main process sets up the processes

    //Creates the exact number of pipes needed
    int fds[num_proc][2];
    for(int i = 0; i < num_proc; i++)
    {
        pipe(fds[i]);
    }

    //This creates the the number of processes the user selected
    long proc_result;
    long long results[num_proc];
    int temp = 0;
    int start, end = 0;
    start_time = clock();
    for(int i = 0; i < num_proc; i++)
    {
        if(fork() == 0)
        {
            //read(fds[i][0], &start, sizeof(int));
            //read(fds[i][0], &end, sizeof(int));
            fseek(file, (lines_proc * i), ((lines_proc * i) + lines_proc));
            printf("%d\n", i);
            while(fscanf(file, "%d", &temp) == 1)
            {
                 proc_result = proc_result + temp;
            }        
            write(fds[i][1], &proc_result, sizeof(long));
            //printf("%s\n", temp);
            _exit(0);
        }
    }

    //parent waits for children to be done
    for(int i = 0; i < num_proc; i ++)
    {
        //write(fds[i][1], (lines_proc * i), sizeof(int));
        //write(fds[i][1], (lines_proc * i), sizeof(int));
        read(fds[i][0], &results[i], sizeof(long long));
    }
    end_time = clock();
    wait(NULL);
    total_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("It took this long: %f\n", total_time);
    //wait(NULL);
    
    for(int i = 0; i < num_proc; i++)
    {
        answer = answer + results[i];
    }

    printf("The total sum is: %lld\n", answer);
    
}

//Counts the amount of lines in the file
int num_lines(void *file)
{
    char temp[3];
    int total_lines = 0;
    while(fscanf(file, "%s", temp) == 1)
    {
        total_lines++;
    }
    return total_lines;
}

//Creates the pipes


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