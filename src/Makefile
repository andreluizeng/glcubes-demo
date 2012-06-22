DEST_DIR		= ../bin     
                   
CROSS_COMPILE		= $(TOOLCHAIN)/bin/arm-none-linux-gnueabi-

LD			= $(CROSS_COMPILE)g++
DEL_FILE		= rm -rf
CP_FILE			= cp -rf      

TARGET_PATH_LIB 	= $(ROOTFS)/usr/lib
TARGET_PATH_INCLUDE 	= $(ROOTFS)/usr/include



# x11 flags
ifeq ($(EGL_FLAVOR),x11)

	APPNAME			= cubes_demo_x11

	CFLAGS			= -D_LINUX -DEGL_USE_X11 -Wall -O2 -fsigned-char -march=armv7-a -mfpu=neon -mfloat-abi=softfp \
				-I. -I$(TARGET_PATH_INCLUDE)

	LFLAGS			= -Wl,--library-path=$(TARGET_PATH_LIB),-rpath-link=$(TARGET_PATH_LIB) \
				-lEGL -lGLESv2 -lpthread -lX11
# fb flags
else
	APPNAME			= cubes_demo_fb

	CFLAGS			= -D_LINUX -DEGL_API_FB -Wall -O2 -fsigned-char -march=armv7-a -mfpu=neon -mfloat-abi=softfp \
				-I. -I$(TARGET_PATH_INCLUDE)
	
	LFLAGS			= -Wl,--library-path=$(TARGET_PATH_LIB),-rpath-link=$(TARGET_PATH_LIB) \
				-lEGL -lGLESv2 -lpthread
endif

OBJECTS			= main.o glutils.o glcube.o




first: all

all: $(APPNAME)

$(APPNAME): $(OBJECTS)
	$(LD) $(LFLAGS) -o $(APPNAME) $(OBJECTS)

main.o: main.cpp
	$(LD) $(CFLAGS) -c -o main.o main.cpp
glutils.o: glutils.cpp
	$(LD) $(CFLAGS) -c -o glutils.o glutils.cpp
glcube.o: glcube.cpp
	$(LD) $(CFLAGS) -c -o glcube.o glcube.cpp

clean:
	$(DEL_FILE) $(OBJECTS)
	$(DEL_FILE) *~ core *.core

distclean: clean
	$(DEL_FILE) $(APPNAME)


install: all
	$(CP_FILE) $(APPNAME) $(DEST_DIR)
	$(DEL_FILE) $(APPNAME)
