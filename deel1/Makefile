src = $(wildcard *.c)
obj = $(src:.c=.o)
CFLAGS=``

main: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -f $(obj) main