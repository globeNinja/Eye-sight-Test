# You can use command line mingw32-make and pretend you are on linux
# Be sure to rename this file Makefile
# UPDATED to use freeglut and the tanktemplate
CC=g++
CFLAGS=-Wall -I"C:\MinGW\freeglut\include" -L"C:\MinGW\freeglut\lib"
DEPS=graphicUtils.h GamePlay.h Boxes.h
OBJ =F20_V375_E5_WeibinNg.o graphicUtils.o GamePlay.o Boxes.o

LIBS=-lfreeglut -lopengl32 -lglu32 -static-libstdc++
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

F20_V375_E5_WeibinNg: $(OBJ)
	$(MAKE) recompile
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	$(MAKE) clean

#housekeeping
clean:
	del -f *.o

recompile:
	del -f *.exe