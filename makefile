
# the following lines pertain to using sound
# if you download FMOD onto your own machine, change the line below
FMOD_DIR = /usr/local/dept/apps/fmod
FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so

# the following lines pertain to setting up compiler options and libraries
OPTS = -Wall -g
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

# here are the usual make rules

game: game.o texture.o Board.o Space.o Player.o Die.o
	g++ $(OPTS) -o game game.o texture.o Board.o Space.o Player.o Die.o  $(LIBS)

texture.o: texture.cpp texture.h
	g++ -g -c texture.cpp

game.o: game.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c game.cpp


Board.o:	Board.cpp Board.h
		g++ -g -c Board.cpp

Space.o:	Space.cpp Space.h
		g++ -g -c Space.cpp

Player.o: 	Player.h Player.cpp Die.o
		g++ -g -c Player.cpp

Die.o:		Die.h Die.cpp
		g++ -g -c Die.cpp

