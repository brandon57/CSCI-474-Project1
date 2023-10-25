#include <stdio.h>
#include <unistd.h>
#include <string.h>

int display();
int input_Check(int check);

int main()
{
    int test = 0;
    //for(int i = 0; i < )
    test = display(1);
    test = display(2);
    printf("%d\n", test);
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
            while(1)
            {
                if(scanf("%d", &input) <= 0 || scanf("%d", &input) == 3 || scanf("%d", &input) > 4)
                {
                    printf("Not valid input\nTry again");
                }
                else
                {}
            }
            break;
        case 2:
            printf("Which file do you want to parse through? \n1. file1\n2. file2\n3. file3\n");
            
            break;
        case 3:
            break;
    }
    return input;
}

int input_Check(int check)
{
    switch()
    {
        //Checks if input is an int
        case 0:
            if(check > )
            break;
        case 1:
    }
}