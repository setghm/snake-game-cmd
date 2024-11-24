APPNAME=SnakeGame

CC=gcc
RC=windres
SRCDIR=src
RESDIR=res
OUTDIR=out
OBJDIR=$(OUTDIR)/obj

INCLUDE=-I$(SRCDIR)/core -I$(RESDIR)

LIBS=-luser32 -lkernel32 -lwinmm

SRCFILES=src/main.o src/core/console.o src/core/timer.o src/core/strings.o src/core/storage.o src/game/game.o src/game/ui/helpers.o src/game/ui/menu_bar.o src/game/ui/menu_option.o src/game/ui/menu_options.o src/game/ui/menu_popup.o src/game/ui/string.o src/game/scenes/scene_menu.o src/game/scenes/scene_play.o src/game/game_objects/snake.o src/game/game_objects/snake_quads.o src/game/game_objects/fruit.o src/game/settings.o
OBJFILES=$(OBJDIR)/$%*.o
RESFILE=resource

all: $(APPNAME).exe

$(APPNAME).exe: $(SRCFILES) $(OBJDIR)/$(RESFILE).o
	$(CC) $(OBJFILES) -o $(OUTDIR)/$(APPNAME).exe $(LIBS)

$(SRCFILES):
	$(CC) -c -o $(OBJDIR)/$(notdir $@) $(@:.o=.c) $(INCLUDE)

$(OBJDIR)/$(RESFILE).o: $(RESDIR)/$(RESFILE).rc $(RESDIR)/$(RESFILE).h
	$(RC) -i $< -o $@

.PHONY: clean
clean:
	del out\obj\*.o out\*.exe
