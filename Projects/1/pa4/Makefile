BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

ModelMatrixBackup : ModelMatrixBackup.o $(BASE_OBJECTS)
	$(LINK) ModelMatrixBackup ModelMatrixBackup.o $(BASE_OBJECTS)

ListTest : ListTest.o $(BASE_OBJECTS)
	$(LINK) ListTest ListTest.o $(BASE_OBJECTS)

ModelListBackup : ModelListBackup.o $(BASE_OBJECTS)
	$(LINK) ModelListBackup ModelListBackup.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ModelMatrixBackup.o : ModelMatrixBackup.c $(HEADERS)
	$(COMPILE) ModelMatrixBackup.c

ListTest.o : ListTest.c $(HEADERS)
	$(COMPILE) ListTest.c

ModelListBackup.o : ModelListBackup.c $(HEADERS)
	$(COMPILE) ModelListBackup.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse MatrixTest Sparse.o MatrixTest.o $(BASE_OBJECTS)

checkFind : Sparse
	$(MEMCHECK) Sparse in7 junk7

checkTest : MatrixTest
	$(MEMCHECK) MatrixTest
