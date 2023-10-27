#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int display(int text);
int input_Check(int option);

int main()
{
    clock_t start_time, end_time;
    double total_time;
    int size = 3;
    FILE* file;
    char temp[size];
    int lines = 0;
    int num_proc = 0;
    int num_file = 0;

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
    start_time = clock();
    while(fscanf(file, "%s", temp) == 1)
    {
        lines++;
    }
    end_time = clock();
    total_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    printf("There are %d lines in the file you chose\nIt took %lf seconds\n", lines, total_time);

    //Moves the pointer back to the beginning of the file
    rewind(file);

    //This creates the the number of processes the user selected
    for(int i = 0; i < num_proc; i++)
    {
        // if()
        // {

        // }
    }



    //parent waits for children to be done
    for(int i = 0; i < num_proc; i ++)
    {
        
    }

    
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