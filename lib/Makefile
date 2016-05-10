include ../makefileinc


.PHONY: all clean lib

all: $(LIBRARY)

$(LIBRARY): $(COMMON_OBJECTS)
	$(info building library...)
	$(AR) $(ARARGS) $(LIBRARYFILE) $^

.c.o:
	$(CC) $(INC_PATH) $(CFLAGS) $< -o $@

clean:
	$(info cleaning up library)
	$(RM) *.o
	$(RM) $(LIBRARYFILE)
