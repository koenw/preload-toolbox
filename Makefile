sources=$(wildcard src/*.c)
objects=$(patsubst src/%.c, build/%.so, $(sources))

$(objects): build/%.so: src/%.c build
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

build:
	@mkdir build

clean:
	rm -rf build

.PHONY: clean
