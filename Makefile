solver : common.o graphreader.o mkk.o nwe.o problem.o solver.o vogel.o zyklus.o stepstone.o modi.o
		gcc -o solver common.o graphreader.o mkk.o nwe.o problem.o solver.o vogel.o zyklus.o stepstone.o modi.o
		rm *.o

common.o : common.c solver.h
		gcc -c common.c
graphreader.o : graphreader.c solver.h
		gcc -c graphreader.c
mkk.o : mkk.c solver.h
		gcc -c mkk.c
nwe.o : nwe.c solver.h
		gcc -c nwe.c
problem.o : problem.c solver.h
		gcc -c problem.c
solver.o : solver.c solver.h
		gcc -c solver.c
vogel.o : vogel.c solver.h
		gcc -c vogel.c
zyklus.o : zyklus.c solver.h
		gcc -c zyklus.c
stepstone.o : stepstone.c solver.h
		gcc -c stepstone.c
modi.o : modi.c solver.h
		gcc -c modi.c
clean :
		rm solver *.o

tarball :
		rm solver.tar.bz2
		tar -cjvf solver.tar.bz2 *.c *.h Makefile
