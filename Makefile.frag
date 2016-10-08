lib.o: lib.nasm
	nasm -felf64 -o$(srcdir)/lib.o $(srcdir)/lib.nasm
	touch $(srcdir)/lib.c
