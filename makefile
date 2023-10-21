# Make 2 rules (target:dependencies)
TicTacToe_Project.obj: TicTacToe_Project.c TicTacToe_Project.h 
# This rule to generate obj file of TicTacToe_Project.c
	gcc -c TicTacToe_Project.c -o TicTacToe_Project.obj
	
main.obj: main.c TicTacToe_Project.h
	gcc -c main.c -o main.obj
# This is where building automation appears.	
# To extract the executable file for all these files by executing the first two rules to be able to find the target for these new dependencies
All:TicTacToe_Project.obj main.obj
	gcc TicTacToe_Project.obj main.obj -o out.exe
# building automation power to track changes at dependencies and at no changes for any file no more compilation	
	