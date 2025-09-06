librename.so: rename.c
	gcc -fPIC -shared -o $@ $<

.PHONY: clean
clean:
	rm librename.so
