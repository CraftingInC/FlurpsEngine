INCLUDES=-Ilibs/glfw-3.3.8.bin.WIN64/include -Ilibs/glad/include -Ilibs/cglm-master/include
LIBINCLUDES=-Llibs/glfw-3.3.8.bin.WIN64/lib-mingw-w64 -lglfw3 -lgdi32
CC=gcc
CODEDIRECTORY=.
GLSOURCE=libs/glad/src/gl.c
CFLAGS=-Wall -std=c99 -m64 -O2
CCFLAGS=-static -m64
CFILES=$(foreach D,$(CODEDIRECTORY),$(wildcard $(D)/*.c))
OBJS=$(patsubst %.c,%.o,$(CFILES))

all: flurpsengine.exe

flurpsengine.exe: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(GLSOURCE) -o gl.o
	$(CC) $(CCFLAGS) -o $@ $^ gl.o $(LIBINCLUDES) -s

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	del *.o flurpsengine.exe log*.txt
