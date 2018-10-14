CC = gcc
RM = rm
CFLAGS  = -Wall -g
LDFLAGS = -g

SOURCES = $(wildcard *.c)
OBJETS  = $(SOURCES:.c=.o)
EXE     = testsUnitaires

CMOCKA_PATH = cmocka/install

LISTE_FIC_A_LIVRER = arbreAVL_$(USER).c testsUnitaires_$(USER).c arbreAVL.h Makefile
DIR_POUR_LIV = ArbreAVL_$(USER)
FIC_POUR_LIV = arbreAVL_$(USER).tgz
WORKDIR = $(shell pwd)

.PHONY: all clean cleanall gentgz run

all: $(EXE)

$(EXE): $(OBJETS)
	$(CC) $(LDFLAGS) $^ -o $@ -L$(CMOCKA_PATH)/lib -lcmocka

%.o:%.c
	$(CC) -c $(CFLAGS) -I$(CMOCKA_PATH)/include $<

clean:
	$(RM) -f *~ *.bak *.tmp \
	         *.o *.s

cleanall: clean
	$(RM) -f $(EXE) $(FIC_POUR_LIV)

run: $(EXE)
	./$(EXE)

gentgz: $(LISTE_FIC_A_LIVRER)
	@rm -Rf /tmp/$(DIR_POUR_LIV)
	@mkdir /tmp/$(DIR_POUR_LIV)
	@cp $(LISTE_FIC_A_LIVRER) /tmp/$(DIR_POUR_LIV)
	@if [ -f readme.txt ] ; \
	then \
		cp -f readme.txt /tmp/$(DIR_POUR_LIV) ; \
	fi;
	@(cd /tmp ; tar cfz $(FIC_POUR_LIV) $(DIR_POUR_LIV) ; mv $(FIC_POUR_LIV) $(WORKDIR) ; rm -Rf $(DIR_POUR_LIV)) 
	@echo '===> ' OK, fichier $(FIC_POUR_LIV) genere : vous pouvez le remonter dans Moodle.

