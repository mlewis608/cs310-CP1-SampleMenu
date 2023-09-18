COURSE = cs310
SEMESTER = fall2023
CP_NUMBER = 1
LASTNAME = Lewis
GITUSERID = mlewis608
EXE = movie_db
MENU_EXE = menu_sample

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = ../CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar
ZIPFILE = $(TARFILE).gz

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -Wextra -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(MENU_EXE)

$(BIN)/$(MENU_EXE): $(OBJ)/sample_menu.o
	$(CC) $(FLAGS) $(OBJ)/sample_menu.o -o $@

$(OBJ)/sample_menu.o: sample_menu.cpp Parser.h
	$(CC) $(FLAGS) -c sample_menu.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)
	@echo "Tarred and gzipped file is in the directory one level up"
	@echo $(ZIPFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(MENU_EXE) $(ZIPFILE)
