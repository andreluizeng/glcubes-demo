APPNAME			= cubes_demo
DEST_DIR		= ../bin     
                   

TOOLCHAIN		= /opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi
CROSS_COMPILE		= $(TOOLCHAIN)/bin/arm-none-linux-gnueabi-

LD			= $(CROSS_COMPILE)g++
DEL_FILE		= rm -rf
CP_FILE			= cp -rf      

ROOTFS_DIR		= /home/andre/bsps/mx5x/sep/ltib/rootfs/
			  
TARGET_PATH_LIB 	= $(ROOTFS_DIR)/usr/lib
TARGET_PATH_INCLUDE 	= $(ROOTFS_DIR)/usr/include


CFLAGS			= -D_LINUX -DEGL_API_FB -Wall -O2 -fsigned-char -march=armv7-a -mfpu=neon -mfloat-abi=softfp \
			  -I. -I$(TARGET_PATH_INCLUDE) 
	
LFLAGS			= -Wl,--library-path=$(TARGET_PATH_LIB),-rpath-link=$(TARGET_PATH_LIB) \
			  -lEGL -lGLESv2 -lpthread 

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
