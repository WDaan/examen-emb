src = $(wildcard *.c)
obj = $(src:.c=.o)
CFLAGS=``
LIBS = -lpthread

main: $(obj)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -f $(obj) main