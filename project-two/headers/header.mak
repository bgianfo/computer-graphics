#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT.
#
# To use the GNU C or C++ compiler, you will need to add one of the
# following lines:
#
#   CC = gcc
#   CCC = g++
#
# Also, if you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
OWGLUTINC=/opt/csw/include
OWGLUTLIB=/opt/csw/lib
WRCINC=/usr/local/pub/wrc/courses/cg1/project2

INCLUDE = -I$(OWGLUTINC) -I$(WRCINC)
LIBDIRS = -L$(OWGLUTLIB)

LDLIBS = -lglut -lGLU -lGL -lGLw -lXmu -lXext -lX11 -lm

CFLAGS = -g $(INCLUDE)
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)
