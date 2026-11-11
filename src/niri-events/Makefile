NAME   := niri-events
CC	   ?= gcc
CFLAGS ?= -O2 -g
CFLAGS += -Wall -Wextra -std=gnu11 -MMD -MP


# cJSON (paso 3). Mientras no lo uses, comenta estas dos líneas.
# CFLAGS += $(shell pkg-config --cflags libcjson)
# LDLIBS += $(shell pkg-config --libs libcjson)

PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=build/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

build/%.o: src/%.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

build:
	mkdir -p build

install: $(NAME)
	install -D -m 755 $(NAME) $(DESTDIR)$(BINDIR)/$(NAME)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(NAME)

clean:
	rm -rf build $(NAME)

-include $(OBJ:.o=.d)

.PHONY: all install uninstall clean
