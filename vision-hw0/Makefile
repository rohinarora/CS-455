OPENCV=0
OPENMP=0
DEBUG=0

OBJ=load_image.o process_image.o args.o
EXOBJ=test.o

VPATH=./src/:./
SLIB=libuwimg.so
ALIB=libuwimg.a
EXEC=uwimg
OBJDIR=./obj/

CC=gcc
AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq ($(OPENMP), 1)
CFLAGS+= -fopenmp
endif

ifeq ($(DEBUG), 1)
OPTS=-O0 -g
COMMON= -Iinclude/ -Isrc/
endif

CFLAGS+=$(OPTS)

ifeq ($(OPENCV), 1)
COMMON+= -DOPENCV
CFLAGS+= -DOPENCV
LDFLAGS+= `pkg-config --libs opencv`
COMMON+= `pkg-config --cflags opencv`
endif

EXOBJS = $(addprefix $(OBJDIR), $(EXOBJ))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
# OBJS is ./obj/load_image.o ./obj/process_image.o ./obj/args.o
DEPS = $(wildcard src/*.h) Makefile
# DEPS is src/args.h src/image.h src/stb_image.h src/stb_image_write.h src/test.h Makefile
all: obj $(SLIB) $(ALIB) $(EXEC)
#all: obj $(EXEC)


$(EXEC): $(EXOBJS) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SLIB): $(OBJS)
	@echo "in SLIB"
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	@echo "yo OBJS is $(OBJS)"
	@echo "yo DEPS is $(DEPS)"
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXOBJS) $(OBJDIR)
