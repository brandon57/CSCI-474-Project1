#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int display();
int input_Check(int option);

int main()
{
    int num_proc = 0;
    int num_file = 0;

    num_proc = display(1);
    //printf("%d\n", num_proc);
    num_file = display(2);
    //printf("%d\n", num_file);
    //test
    
    
    
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