#makefile pertama

compiler=gcc

main.exe: main.c link_list.o
	${compiler}  $^ -o $@
	
link_list.o: link_list.c 
	${compiler} -c $^ -o $@