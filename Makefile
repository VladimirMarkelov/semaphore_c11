include makefileinc

DIRS = lib tests

.PHONY: all clean $(DIRS)

all: $(DIRS)
	$(info building everything...)

$(DIRS):
	$(info building $@...)
	$(MAKE) -C $@

clean:
	$(MAKE) -C tests clean
	$(MAKE) -C lib clean
