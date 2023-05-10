#############
#
# Makefile generico
# Autor: PaikLC
#
#############

# COSAS MISC
LIBRARY_PATH		= 	.\lib


# descomentar para hacer una compilacion de depuracion.
#DEBUG = 1

# Comentar para hacer una compilacion el Windows.
#LINUX_MODE = 1

# Definimos los programas que compilaran por nosotros
CC				= gcc.exe

export PATH := $(COMPILER_PATH):$(PATH)

# Las cosas a compilara
TARGET			= main
OBJS			= $(TARGET).o $(LIBRARY_PATH)\base64\buffer.o $(LIBRARY_PATH)\base64\decode.o $(LIBRARY_PATH)\base64\encode.o
OBJS			+= $(LIBRARY_PATH)\deserializer\deserializer.o $(LIBRARY_PATH)\deserializer\list.o

ifdef DEBUG
NAME			= main_dbg.exe
else
NAME			= DecPric.exe
endif


# Las opciones de compilacion
CFLAGS			= -Wall -static 
LDFLAGS			= 
DEBUG_FLAGS		= -g -O1
RELEASE_FLAGS	= -s -O3

ifdef DEBUG
CFLAGS			+= $(DEBUG_FLAGS)
else
CFLAGS			+= $(RELEASE_FLAGS)
endif


all: $(NAME)

# Compilar el programa listo para ser compilado para windows...
$(NAME).exe: $(OBJS)
	$(CC) -o $(NAME).exe $(OBJS) $(LDFLAGS)


# Compilar el programa para linux...
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compilar .c ¿Para que es el $*.o? ¿Renombrar?
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

#Trabajar con el .rc
%.o: %.rc
	windres -i $< -o $*.o

# Limpiar las cosas
.PHONY clean:
	rm *.o /s
	rm *.exe /s