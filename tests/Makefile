include ../makefileinc

SOURCES_RING=ringbuffer.c ringtest.c

OBJECTS_RING=$(SOURCES_RING:.c=.o)

EXE_RING=ring
EXECUTABLES=$(EXE_RING)

.PHONY: all clean $(EXECUTABLES)

all: $(EXECUTABLES)

$(EXE_RING): $(OBJECTS_RING)
	$(CC) -o $@ $^ $(INC_PATH) $(LIB_PATH) -l$(LIBRARY) $(STDLIBS)
	$(STRIP) $(addsuffix .exe, $(EXE_RING))

.c.o:
	$(CC) $(INC_PATH) $(CFLAGS) $< -o $@

clean:
	$(info removing tests...)
	$(RM) *.o
	$(RM) $(addsuffix .exe, $(EXECUTABLES))
