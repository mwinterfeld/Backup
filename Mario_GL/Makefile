#  List of all programs you want to build
EX=mario
OBJ=mario.o objects.o CSCIx229.a

#  Libraries - Linux
LIBS=-lglut -lGLU -lGL -lm
#  Libraries - OSX
#LIBS=-framework GLUT -framework OpenGL
#  Libraries - MinGW
#LIBS=-lglut32cu -lglu32 -lopengl32

#  Main target
all: $(EX)

#  Generic compile rules
$(EX): $(OBJ)
	g++ -Wall $(OBJ) -o $@ $(LIBS)

%.o: %.cpp
	g++ $< -c 

#  Delete unwanted files
clean:
	rm -f $(EX) *.o

#  Create archive (include glWindowPos here if you need it)
#CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
#	ar -rcs CSCIx229.a $^

#  Obligatory UNIX inside joke
love:
	@echo "not war?"