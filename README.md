# CSCI-474-Project1

This project is about creating a multiprocess program that uses fork and pipe to read a file.

# These are the requirments for the project

<p align="center">
  <img src="Documents/project_1_2023_Fall_pg1.png" width="688" />
</p>

<p align="center">
  <img src="Documents/project_1_2023_Fall_pg2.png" width="688" />
</p>

# Running the program
Note: This program can only run on Linux Distros.

In order to run the program you are gonna need to compile it first. The compiler that'll be used is GCC.

## Installing GCC
To install GCC you will need to open the terminal.

* Once you have the terminal open typing this command will install it:
```
sudo apt install gcc
```
It'll then ask you for your password and then ask if you want to continue.

Once you do that GCC will start installing.

## Compiling the program
Now that gcc is installed you need to navigate to where ever you downloaded the program. Once you've navigated to where the program is, you'll need to compile the file.

* Running this command will compile it:
```
gcc project1.c -o project1.out
```
After running the command a new file will be created. This is the file that we will run.

## Running
Now to run the program you can use this command:
```
./project1.out
```
Using this command will then run the program.
