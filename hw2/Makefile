all:main.exe
	main.exe

CC = g++
LIB = "C:\mingw64\freeglut\lib\x64"
GLFLAGS = -lfreeglut -lopengl32 -lglu32
CFLAGS = -c -o
LIBDIR = "lib"
INCLUDE = "C:\mingw64\freeglut\include"
OBJ = main.o baseObject.o body.o RGBColor.o joint.o limbs.o head.o robot.o block.o gun.o

main.exe: $(OBJ)
	$(CC) -o main.exe $(OBJ) -L$(LIB) $(GLFLAGS)

main.o:
	$(CC) $(CFLAGS) main.o main.cpp -I$(INCLUDE)

robot.o: $(OBJ)
	$(CC) $(CFLAGS) robot.o $(LIBDIR)/robot.cpp -I$(INCLUDE)

baseObject.o:
	$(CC) $(CFLAGS) baseObject.o $(LIBDIR)/baseObject.cpp -I$(INCLUDE)

body.o:
	$(CC) $(CFLAGS) body.o $(LIBDIR)/body.cpp -I$(INCLUDE)

RGBColor.o:
	$(CC) $(CFLAGS) RGBColor.o $(LIBDIR)/RGBColor.cpp -I$(INCLUDE)

joint.o:
	$(CC) $(CFLAGS) joint.o $(LIBDIR)/joint.cpp -I$(INCLUDE)

limbs.o:
	$(CC) $(CFLAGS) limbs.o $(LIBDIR)/limbs.cpp -I$(INCLUDE)

head.o:
	$(CC) $(CFLAGS) head.o $(LIBDIR)/head.cpp -I$(INCLUDE)

block.o:
	$(CC) $(CFLAGS) block.o $(LIBDIR)/block.cpp -I$(INCLUDE)

gun.o:
	$(CC) $(CFLAGS) gun.o $(LIBDIR)/gun.cpp -I$(INCLUDE)

clean:
	del *.o *.exe