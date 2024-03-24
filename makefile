# Joe Citizen, s1234567 - Operating Systems Project 1
# ca216/myshell

myshell: myshell.c utility.c myshell.h
	gcc -Wall myshell.c utility.c -o myshell