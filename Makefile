# Variables for compiling the executable
TARGET:=scheduler
OBJS:=matrix.o scheduler.o
SRC:=src/
BIN:=bin/
OBJ:=$(BIN)obj/
DIR_LIST:=$(SRC) $(BIN) $(OBJ)
VPATH:=$(SRC) $(SRC)utils/
CC:=gcc
CFLAGS?= -Wall -std=c99 -pthread -O2 -g
MKDIR_P:=mkdir -p

# Variables for compiling the report
REPORT:=report.pdf
TEX_DIR:=latex/
TEX:=pdflatex
TEXFLAGS?=

.PHONY: all directories report clean

all: directories $(TARGET)

directories: $(DIR_LIST)

$(DIR_LIST):
	$(MKDIR_P) $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)$@ $(addprefix $(OBJ), $(OBJS))

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(OBJ)$@

report: $(REPORT)

# Generally LaTeX must be compiled at least twice in order to prepare a final document
$(REPORT):
	for i in {1..2}
	do
		$(TEX) $(TEXFLAGS) $(TEX_DIR)$@
	done

clean:
	rm -f $(addprefix $(OBJ), $(OBJS))
	rm -f $(addprefix $(BIN), $(TARGET))
	rm -f $(REPORT)
