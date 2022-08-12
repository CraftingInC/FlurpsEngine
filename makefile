INCLUDES=-Ilibs/GLFW3/glfw-3.3.8.bin.WIN64/include -Ilibs/glad -Ilibs/freetype/include -Ilibs/cglm-master/include
LIBINCLUDES=-Llibs/GLFW3/glfw-3.3.8.bin.WIN64/lib-mingw-w64 -Llibs/freetype/lib -lglfw3 -lgdi32 -lfreetype
CC=gcc
CODEDIRECTORY=. libs/glad/glad
CFLAGS=-Wall -std=c99 -m64 -O2
CCFLAGS=-static -m64
CFILES=$(foreach D,$(CODEDIRECTORY),$(wildcard $(D)/*.c))
OBJS=$(patsubst %.c,%.o,$(CFILES))

all: flurpsengine.exe

flurpsengine.exe: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBINCLUDES) -s

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
	del *.o libs\glad\glad\glad.o flurpsengine.exe log*.txt
