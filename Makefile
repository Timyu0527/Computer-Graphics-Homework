all:main.exe
	main.exe

CC = g++
LIB = "C:\mingw64\freeglut\lib\x64"
GLFLAGS = -lfreeglut -lopengl32 -lglu32
CFLAGS = -c -o
INCLUDE = "C:\mingw64\freeglut\include"
LIBDIR = .\lib
UIDIR = .\lib\UI
OBJECTDIR = .\lib\object
OBJ = button.o menu.o entry.o text_function.o navbar.o object.o line.o point.o poly.o curve.o circle.o slider.o RGBColor.o adjuster.o label.o imageHandler.o pointer.o main.o

main.exe: $(OBJ)
	$(CC) -o main.exe $(OBJ) -L$(LIB) $(GLFLAGS)

main.o:
	$(CC) $(CFLAGS) main.o main.cpp -I$(INCLUDE)

pointer.o:
	$(CC) $(CFLAGS) pointer.o $(UIDIR)\pointer.cpp -I$(INCLUDE)

menu.o:
	$(CC) $(CFLAGS) menu.o $(UIDIR)\menu.cpp -I$(INCLUDE)

navbar.o:
	$(CC) $(CFLAGS) navbar.o $(UIDIR)\navbar.cpp -I$(INCLUDE)

adjuster.o:
	$(CC) $(CFLAGS) adjuster.o $(UIDIR)\adjuster.cpp -I$(INCLUDE)

slider.o:
	$(CC) $(CFLAGS) slider.o $(UIDIR)\slider.cpp -I$(INCLUDE)

button.o:
	$(CC) $(CFLAGS) button.o $(UIDIR)\button.cpp -I$(INCLUDE)

entry.o:
	$(CC) $(CFLAGS) entry.o $(UIDIR)\entry.cpp -I$(INCLUDE)

label.o:
	$(CC) $(CFLAGS) label.o $(OBJECTDIR)\label.cpp -I$(INCLUDE)

circle.o:
	$(CC) $(CFLAGS) circle.o $(OBJECTDIR)\circle.cpp -I$(INCLUDE)

curve.o:
	$(CC) $(CFLAGS) curve.o $(OBJECTDIR)\curve.cpp -I$(INCLUDE)

poly.o:
	$(CC) $(CFLAGS) poly.o $(OBJECTDIR)\poly.cpp -I$(INCLUDE)

point.o:
	$(CC) $(CFLAGS) point.o $(OBJECTDIR)\point.cpp -I$(INCLUDE)

line.o:
	$(CC) $(CFLAGS) line.o $(OBJECTDIR)\line.cpp -I$(INCLUDE)

object.o:
	$(CC) $(CFLAGS) object.o $(OBJECTDIR)\object.cpp -I$(INCLUDE)

text_function.o:
	$(CC) $(CFLAGS) text_function.o $(LIBDIR)\text_function.cpp -I$(INCLUDE)

imageHandler.o:
	$(CC) $(CFLAGS) imageHandler.o $(LIBDIR)\imageHandler.cpp -I$(INCLUDE)

RGBColor.o:
	$(CC) $(CFLAGS) RGBColor.o $(LIBDIR)\RGBColor.cpp -I$(INCLUDE)



clean:
	del $(OBJ) main.exe