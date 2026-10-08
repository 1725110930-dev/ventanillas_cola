CC      := gcc
CFLAGS  := -Wall -Wextra -Wpedantic -Iinclude
BUILD   := build

SRCS    := src/main.c src/estudiante.c src/cola.c src/io.c src/sistema.c
HDRS    := include/cola.h include/estudiante.h include/io.h include/sistema.h

all: servicios_escolares

$(BUILD):
	mkdir -p $(BUILD)

servicios_escolares: $(BUILD) $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(BUILD)/servicios_escolares $(SRCS)

run: servicios_escolares
	./$(BUILD)/servicios_escolares

test_cola: $(BUILD) src/cola.c src/estudiante.c tests/test_cola.c
	$(CC) $(CFLAGS) -DMAX_ESTUDIANTES=5 -o $(BUILD)/test_cola \
	    src/cola.c src/estudiante.c tests/test_cola.c

test: test_cola
	./$(BUILD)/test_cola

clean:
	rm -rf $(BUILD)