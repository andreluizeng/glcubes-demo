/************************-***************************************************
 *   Copyright (C) 2011 by Andre L. V. da Silva   									*
 *   andreluizeng@yahoo.com.br   														*
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include "glutils.h"
#include "glcube.h"

GLUtils *window = new GLUtils;

GLCube *cube1 = new GLCube;
GLCube *cube2 = new GLCube;
GLCube *cube3 = new GLCube;
GLCube *cube4 = new GLCube;
GLCube *cube5 = new GLCube;
GLCube *cube6 = new GLCube;
GLCube *cube7 = new GLCube;
GLCube *cube8 = new GLCube;
GLCube *cube9 = new GLCube;
GLCube *cube10 = new GLCube;

float matProj[16] = {0};
float matModel[9] = {0};

void 		Render 		(void);
void 		CalcCubePos 	(float *xpos, float *ypos, float *zpos, float *speedx, float *speedy, float *speedz, int *xflag, int *yflag, int *zflag);
unsigned long 	GetTime		(void);

int main (int argc, char **argv)
{
	int w;
	int h;
	
	unsigned int    frame_count = 0;
	unsigned int    frames_per_second = 0;	
	unsigned int    time_previous_second = GetTime();
	
	char *cube1data1;
	char *cube1data2;
	char *cube1data3;
	char *cube1data4;
	char *cube1data5;
	char *cube1data6;

	char *cube2data1;
	char *cube2data2;
	char *cube2data3;
	char *cube2data4;
	char *cube2data5;
	char *cube2data6;

	char *cube3data1;
	char *cube3data2;
	char *cube3data3;
	char *cube3data4;
	char *cube3data5;
	char *cube3data6;

	char *cube4data1;
	char *cube4data2;
	char *cube4data3;
	char *cube4data4;
	char *cube4data5;
	char *cube4data6;

	char *cube5data1;
	char *cube5data2;
	char *cube5data3;
	char *cube5data4;
	char *cube5data5;
	char *cube5data6;

	char *cube6data1;
	char *cube6data2;
	char *cube6data3;
	char *cube6data4;
	char *cube6data5;
	char *cube6data6;

	char *cube7data1;
	char *cube7data2;
	char *cube7data3;
	char *cube7data4;
	char *cube7data5;
	char *cube7data6;

	char *cube8data1;
	char *cube8data2;
	char *cube8data3;
	char *cube8data4;
	char *cube8data5;
	char *cube8data6;

	char *cube9data1;
	char *cube9data2;
	char *cube9data3;
	char *cube9data4;
	char *cube9data5;
	char *cube9data6;

	char *cube10data1;
	char *cube10data2;
	char *cube10data3;
	char *cube10data4;
	char *cube10data5;
	char *cube10data6;

	// Initializate OGLES2
	printf ("\nInitializing OGLES2...");
	window->GLInit ();
	printf ("OK\n");
	
	printf ("\nInitializing the Cube 1...");
	cube1->CubeCreate(1.5, 1.5, 1.5);
	cube1->CubeCreateTex ();
	printf ("OK\n");
	
	printf ("\nInitializing the Cube 2...");
	cube2->CubeCreate(1.5, 1.5, 1.5);
	cube2->CubeCreateTex ();
	printf ("OK\n");
	
	printf ("\nInitializing the Cube 3...");
	cube3->CubeCreate(1.5, 1.5, 1.5);
	cube3->CubeCreateTex ();
	printf ("OK\n");
	
	printf ("\nInitializing the Cube 4...");
	cube4->CubeCreate(1.5, 1.5, 1.5);
	cube4->CubeCreateTex ();
	printf ("OK\n");
	
	printf ("\nInitializing the Cube 5...");
	cube5->CubeCreate(1.5, 1.5, 1.5);
	cube5->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nInitializing the Cube 6...");
	cube6->CubeCreate(1.5, 1.5, 1.5);
	cube6->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nInitializing the Cube 7...");
	cube7->CubeCreate(1.5, 1.5, 1.5);
	cube7->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nInitializing the Cube 8...");
	cube8->CubeCreate(1.5, 1.5, 1.5);
	cube8->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nInitializing the Cube 9...");
	cube9->CubeCreate(1.5, 1.5, 1.5);
	cube9->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nInitializing the Cube 10...");
	cube10->CubeCreate(1.5, 1.5, 1.5);
	cube10->CubeCreateTex ();
	printf ("OK\n");

	printf ("\nLoading Cube1's texture...");
	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina1.bmp", &w, &h, &cube1data1);
	cube1->CubeSetFaceTexBuf(FRONT_FACE, cube1data1, w, h);

	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina2.bmp", &w, &h, &cube1data2);
	cube1->CubeSetFaceTexBuf(BACK_FACE, cube1data2, w, h);
	
	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina3.bmp", &w, &h, &cube1data3);
	cube1->CubeSetFaceTexBuf(RIGHT_FACE, cube1data3, w, h);
	
	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina4.bmp", &w, &h, &cube1data4);
	cube1->CubeSetFaceTexBuf(LEFT_FACE, cube1data4, w, h);
	
	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina5.bmp", &w, &h, &cube1data5);
	cube1->CubeSetFaceTexBuf(TOP_FACE, cube1data5, w, h);
	
	cube1->CubeLoadTextureBMP((char *)"images/angelina/angelina6.bmp", &w, &h, &cube1data6);
	cube1->CubeSetFaceTexBuf(BOTTOM_FACE, cube1data6, w, h);

	printf ("OK\n");

	printf ("\nLoading Cube2's texture...");
	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha1.bmp", &w, &h, &cube2data1);
	cube2->CubeSetFaceTexBuf(FRONT_FACE, cube2data1, w, h);

	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha2.bmp", &w, &h, &cube2data2);
	cube2->CubeSetFaceTexBuf(BACK_FACE, cube2data2, w, h);
	
	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha3.bmp", &w, &h, &cube2data3);
	cube2->CubeSetFaceTexBuf(RIGHT_FACE, cube2data3, w, h);
	
	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha4.bmp", &w, &h, &cube2data4);
	cube2->CubeSetFaceTexBuf(LEFT_FACE, cube2data4, w, h);
	
	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha5.bmp", &w, &h, &cube2data5);
	cube2->CubeSetFaceTexBuf(TOP_FACE, cube2data5, w, h);
	
	cube2->CubeLoadTextureBMP((char *)"images/elisha/elisha6.bmp", &w, &h, &cube2data6);
	cube2->CubeSetFaceTexBuf(BOTTOM_FACE, cube2data6, w, h);

	printf ("OK\n");
	
	printf ("\nLoading Cube3's texture...");
	cube3->CubeLoadTextureBMP((char *)"images/eva/eva1.bmp", &w, &h, &cube3data1);
	cube3->CubeSetFaceTexBuf(FRONT_FACE, cube3data1, w, h);

	cube3->CubeLoadTextureBMP((char *)"images/eva/eva2.bmp", &w, &h, &cube3data2);
	cube3->CubeSetFaceTexBuf(BACK_FACE, cube3data2, w, h);
	
	cube3->CubeLoadTextureBMP((char *)"images/eva/eva3.bmp", &w, &h, &cube3data3);
	cube3->CubeSetFaceTexBuf(RIGHT_FACE, cube3data3, w, h);
	
	cube3->CubeLoadTextureBMP((char *)"images/eva/eva4.bmp", &w, &h, &cube3data4);
	cube3->CubeSetFaceTexBuf(LEFT_FACE, cube3data4, w, h);
	
	cube3->CubeLoadTextureBMP((char *)"images/eva/eva5.bmp", &w, &h, &cube3data5);
	cube3->CubeSetFaceTexBuf(TOP_FACE, cube3data5, w, h);
	
	cube3->CubeLoadTextureBMP((char *)"images/eva/eva6.bmp", &w, &h, &cube3data6);
	cube3->CubeSetFaceTexBuf(BOTTOM_FACE, cube3data6, w, h);

	printf ("OK\n");
	
		printf ("\nLoading Cube4's texture...");
	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva1.bmp", &w, &h, &cube4data1);
	cube4->CubeSetFaceTexBuf(FRONT_FACE, cube4data1, w, h);

	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva2.bmp", &w, &h, &cube4data2);
	cube4->CubeSetFaceTexBuf(BACK_FACE, cube4data2, w, h);
	
	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva3.bmp", &w, &h, &cube4data3);
	cube4->CubeSetFaceTexBuf(RIGHT_FACE, cube4data3, w, h);
	
	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva4.bmp", &w, &h, &cube4data4);
	cube4->CubeSetFaceTexBuf(LEFT_FACE, cube4data4, w, h);
	
	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva5.bmp", &w, &h, &cube4data5);
	cube4->CubeSetFaceTexBuf(TOP_FACE, cube4data5, w, h);
	
	cube4->CubeLoadTextureBMP((char *)"images/evangeline/eva6.bmp", &w, &h, &cube4data6);
	cube4->CubeSetFaceTexBuf(BOTTOM_FACE, cube4data6, w, h);
	
	printf ("OK\n");
	
	
	printf ("\nLoading Cube5's texture...");
	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi1.bmp", &w, &h, &cube5data1);
	cube5->CubeSetFaceTexBuf(FRONT_FACE, cube5data1, w, h);

	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi2.bmp", &w, &h, &cube5data2);
	cube5->CubeSetFaceTexBuf(BACK_FACE, cube5data2, w, h);
	
	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi3.bmp", &w, &h, &cube5data3);
	cube5->CubeSetFaceTexBuf(RIGHT_FACE, cube5data3, w, h);
	
	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi4.bmp", &w, &h, &cube5data4);
	cube5->CubeSetFaceTexBuf(LEFT_FACE, cube5data4, w, h);
	
	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi5.bmp", &w, &h, &cube5data5);
	cube5->CubeSetFaceTexBuf(TOP_FACE, cube5data5, w, h);
	
	cube5->CubeLoadTextureBMP((char *)"images/grazi/grazi6.bmp", &w, &h, &cube5data6);
	cube5->CubeSetFaceTexBuf(BOTTOM_FACE, cube5data6, w, h);

	printf ("OK\n");
	
	printf ("\nLoading Cube6's texture...");
	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica1.bmp", &w, &h, &cube6data1);
	cube6->CubeSetFaceTexBuf(FRONT_FACE, cube6data1, w, h);

	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica2.bmp", &w, &h, &cube6data2);
	cube6->CubeSetFaceTexBuf(BACK_FACE, cube6data2, w, h);
	
	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica3.bmp", &w, &h, &cube6data3);
	cube6->CubeSetFaceTexBuf(RIGHT_FACE, cube6data3, w, h);
	
	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica4.bmp", &w, &h, &cube6data4);
	cube6->CubeSetFaceTexBuf(LEFT_FACE, cube6data4, w, h);
	
	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica5.bmp", &w, &h, &cube6data5);
	cube6->CubeSetFaceTexBuf(TOP_FACE, cube6data5, w, h);
	
	cube6->CubeLoadTextureBMP((char *)"images/jessica/jessica6.bmp", &w, &h, &cube6data6);
	cube6->CubeSetFaceTexBuf(BOTTOM_FACE, cube6data6, w, h);
	
	printf ("OK\n");
	
	printf ("\nLoading Cube7's texture...");
	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica1.bmp", &w, &h, &cube7data1);
	cube7->CubeSetFaceTexBuf(FRONT_FACE, cube7data1, w, h);

	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica2.bmp", &w, &h, &cube7data2);
	cube7->CubeSetFaceTexBuf(BACK_FACE, cube7data2, w, h);
	
	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica3.bmp", &w, &h, &cube7data3);
	cube7->CubeSetFaceTexBuf(RIGHT_FACE, cube7data3, w, h);
	
	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica4.bmp", &w, &h, &cube7data4);
	cube7->CubeSetFaceTexBuf(LEFT_FACE, cube7data4, w, h);
	
	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica5.bmp", &w, &h, &cube7data5);
	cube7->CubeSetFaceTexBuf(TOP_FACE, cube7data5, w, h);
	
	cube7->CubeLoadTextureBMP((char *)"images/jessicabiel/jessica6.bmp", &w, &h, &cube7data6);
	cube7->CubeSetFaceTexBuf(BOTTOM_FACE, cube7data6, w, h);
	
	printf ("OK\n");
	
	printf ("\nLoading Cube8's texture...");
	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan1.bmp", &w, &h, &cube8data1);
	cube8->CubeSetFaceTexBuf(FRONT_FACE, cube8data1, w, h);

	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan2.bmp", &w, &h, &cube8data2);
	cube8->CubeSetFaceTexBuf(BACK_FACE, cube8data2, w, h);
	
	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan3.bmp", &w, &h, &cube8data3);
	cube8->CubeSetFaceTexBuf(RIGHT_FACE, cube8data3, w, h);
	
	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan4.bmp", &w, &h, &cube8data4);
	cube8->CubeSetFaceTexBuf(LEFT_FACE, cube8data4, w, h);
	
	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan5.bmp", &w, &h, &cube8data5);
	cube8->CubeSetFaceTexBuf(TOP_FACE, cube8data5, w, h);
	
	cube8->CubeLoadTextureBMP((char *)"images/meganfox/megan6.bmp", &w, &h, &cube8data6);
	cube8->CubeSetFaceTexBuf(BOTTOM_FACE, cube8data6, w, h);
	
	printf ("OK\n");
	
	printf ("\nLoading Cube9's texture...");
	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett1.bmp", &w, &h, &cube9data1);
	cube9->CubeSetFaceTexBuf(FRONT_FACE, cube9data1, w, h);

	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett2.bmp", &w, &h, &cube9data2);
	cube9->CubeSetFaceTexBuf(BACK_FACE, cube9data2, w, h);
	
	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett3.bmp", &w, &h, &cube9data3);
	cube9->CubeSetFaceTexBuf(RIGHT_FACE, cube9data3, w, h);
	
	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett4.bmp", &w, &h, &cube9data4);
	cube9->CubeSetFaceTexBuf(LEFT_FACE, cube9data4, w, h);
	
	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett5.bmp", &w, &h, &cube9data5);
	cube9->CubeSetFaceTexBuf(TOP_FACE, cube9data5, w, h);
	
	cube9->CubeLoadTextureBMP((char *)"images/scarlett/scarlett6.bmp", &w, &h, &cube9data6);
	cube9->CubeSetFaceTexBuf(BOTTOM_FACE, cube9data6, w, h);
		
	printf ("OK\n");
	
	printf ("\nLoading Cube10's texture...");
	cube10->CubeLoadTextureBMP((char *)"images/shania/shania1.bmp", &w, &h, &cube10data1);
	cube10->CubeSetFaceTexBuf(FRONT_FACE, cube10data1, w, h);

	cube10->CubeLoadTextureBMP((char *)"images/shania/shania2.bmp", &w, &h, &cube10data2);
	cube10->CubeSetFaceTexBuf(BACK_FACE, cube10data2, w, h);
	
	cube10->CubeLoadTextureBMP((char *)"images/shania/shania3.bmp", &w, &h, &cube10data3);
	cube10->CubeSetFaceTexBuf(RIGHT_FACE, cube10data3, w, h);
	
	cube10->CubeLoadTextureBMP((char *)"images/shania/shania4.bmp", &w, &h, &cube10data4);
	cube10->CubeSetFaceTexBuf(LEFT_FACE, cube10data4, w, h);
	
	cube10->CubeLoadTextureBMP((char *)"images/shania/shania5.bmp", &w, &h, &cube10data5);
	cube10->CubeSetFaceTexBuf(TOP_FACE, cube10data5, w, h);
	
	cube10->CubeLoadTextureBMP((char *)"images/shania/shania6.bmp", &w, &h, &cube10data6);
	cube10->CubeSetFaceTexBuf(BOTTOM_FACE, cube10data6, w, h);
		
	printf ("OK\n");
	
	window->GenPerspectiveMatrix (0.5, 1.0, -1000, 1.0, matProj);
	cube1->CubeSetProjMatrix(matProj);
	cube2->CubeSetProjMatrix(matProj);
	cube3->CubeSetProjMatrix(matProj);
	cube4->CubeSetProjMatrix(matProj);
	cube5->CubeSetProjMatrix(matProj);
	cube6->CubeSetProjMatrix(matProj);
	cube7->CubeSetProjMatrix(matProj);
	cube8->CubeSetProjMatrix(matProj);
	cube9->CubeSetProjMatrix(matProj);
	cube10->CubeSetProjMatrix(matProj);
	
	while (!window->Kbhit ())
	{
		Render ();

		// Measure the frame rate.
		unsigned int time = GetTime();
		frame_count++;

		if ((time - time_previous_second) > 1000)   // Has a one second interval passed?
		{
			time_previous_second = time;
			frames_per_second = frame_count;
			frame_count = 0;

			printf("\nFrame Rate: %d FPS", frames_per_second);
		}
	}
		
	window->GLEnd();
	
	free (cube1data1);
	free (cube1data2);
	free (cube1data3);
	free (cube1data4);
	free (cube1data5);

	free (cube1data6);
	free (cube2data1);
	free (cube2data2);
	free (cube2data3);
	free (cube2data4);
	free (cube2data5);
	free (cube2data6);

	free (cube3data1);
	free (cube3data2);
	free (cube3data3);
	free (cube3data4);
	free (cube3data5);
	free (cube3data6);

	free (cube4data1);
	free (cube4data2);
	free (cube4data3);
	free (cube4data4);
	free (cube4data5);
	free (cube4data6);
	
	free (cube5data1);
	free (cube5data2);
	free (cube5data3);
	free (cube5data4);
	free (cube5data5);
	free (cube5data6);
	
	free (cube6data1);
	free (cube6data2);
	free (cube6data3);
	free (cube6data4);
	free (cube6data5);
	free (cube6data6);

	free (cube7data1);
	free (cube7data2);
	free (cube7data3);
	free (cube7data4);
	free (cube7data5);
	free (cube7data6);

	free (cube8data1);
	free (cube8data2);
	free (cube8data3);
	free (cube8data4);
	free (cube8data5);
	free (cube8data6);

	free (cube9data1);
	free (cube9data2);
	free (cube9data3);
	free (cube9data4);
	free (cube9data5);
	free (cube9data6);

	free (cube10data1);
	free (cube10data2);
	free (cube10data3);
	free (cube10data4);
	free (cube10data5);
	free (cube10data6);

	return 0;
}

void Render (void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;
	static float fAngleZ = 0.0f;

	static int xflag1 = 0;
	static int yflag1 = 0;
	static int zflag1 = 0;
	static float xpos1 = -3.0;
	static float ypos1 = 3.0;
	static float zpos1 = -12.0;
	static float speedx1 = 0.10;
	static float speedy1 = 0.109;
	static float speedz1 = 0.109;

	static int xflag2 = 0;
	static int yflag2 = 0;
	static int zflag2 = 0;
	static float xpos2 = -3.0;
	static float ypos2 = 3.0;
	static float zpos2 = -12.0;
	static float speedx2 = 0.10;
	static float speedy2 = 0.11;
	static float speedz2 = 0.11;

	static int xflag3 = 0;
	static int yflag3 = 0;
	static int zflag3 = 0;
	static float xpos3 = -3.0;
	static float ypos3 = 3.0;
	static float zpos3 = -12.0;
	static float speedx3 = 0.10;
	static float speedy3 = 0.106;
	static float speedz3 = 0.106;

	static int xflag4 = 0;
	static int yflag4 = 0;
	static int zflag4 = 0;
	static float xpos4 = -3.0;
	static float ypos4 = 3.0;
	static float zpos4 = -12.0;
	static float speedx4 = 0.10;
	static float speedy4 = 0.105;
	static float speedz4 = 0.105;

	static int xflag5 = 0;
	static int yflag5 = 0;
	static int zflag5 = 0;
	static float xpos5 = -3.0;
	static float ypos5 = 3.0;
	static float zpos5 = -12.0;
	static float speedx5 = 0.102;
	static float speedy5 = 0.11;
	static float speedz5 = 0.11;

	static int xflag6 = 0;
	static int yflag6 = 0;
	static int zflag6 = 0;
	static float xpos6 = -3.0;
	static float ypos6 = 3.0;
	static float zpos6 = -12.0;
	static float speedx6 = 0.10;
	static float speedy6 = 0.106;
	static float speedz6 = 0.106;

	static int xflag7 = 0;
	static int yflag7 = 0;
	static int zflag7 = 0;
	static float xpos7 = -3.0;
	static float ypos7 = 3.0;
	static float zpos7 = -12.0;
	static float speedx7 = 0.10;
	static float speedy7 = 0.102;
	static float speedz7 = 0.102;

	static int xflag8 = 0;
	static int yflag8 = 0;
	static int zflag8 = 0;
	static float xpos8 = -3.0;
	static float ypos8 = 3.0;
	static float zpos8 = -12.0;
	static float speedx8 = 0.110;
	static float speedy8 = 0.111;
	static float speedz8 = 0.111;

	static int xflag9 = 0;
	static int yflag9 = 0;
	static int zflag9 = 0;
	static float xpos9 = -3.0;
	static float ypos9 = 3.0;
	static float zpos9 = -12.0;
	static float speedx9 = 0.110;
	static float speedy9 = 0.112;
	static float speedz9 = 0.112;
	
	static int xflag10 = 0;
	static int yflag10 = 0;
	static int zflag10 = 0;
	static float xpos10 = -3.0;
	static float ypos10 = 3.0;
	static float zpos10 = -12.0;
	static float speedx10 = 0.155;
	static float speedy10 = 0.090;
	static float speedz10 = 0.120;


	if (fAngleX >= 360) fAngleX = 0;
	else fAngleX += 1.0f;

	if (fAngleY >= 360) fAngleY = 0;
	else fAngleY += 1.0f;

	if (fAngleZ >= 360) fAngleZ = 0;
	else fAngleZ += 1.0f;

	CalcCubePos (&xpos1, &ypos1, &zpos1, &speedx1, &speedy1, &speedz1, &xflag1, &yflag1, &zflag1);
	CalcCubePos (&xpos2, &ypos2, &zpos2, &speedx2, &speedy2, &speedz2, &xflag2, &yflag2, &zflag2);
	CalcCubePos (&xpos3, &ypos3, &zpos3, &speedx3, &speedy3, &speedz3, &xflag3, &yflag3, &zflag3);
	CalcCubePos (&xpos4, &ypos4, &zpos4, &speedx4, &speedy4, &speedz4, &xflag4, &yflag4, &zflag4);
	CalcCubePos (&xpos5, &ypos5, &zpos5, &speedx5, &speedy5, &speedz5, &xflag5, &yflag5, &zflag5);
	CalcCubePos (&xpos6, &ypos6, &zpos6, &speedx6, &speedy6, &speedz6, &xflag6, &yflag6, &zflag6);
	CalcCubePos (&xpos7, &ypos7, &zpos7, &speedx7, &speedy7, &speedz7, &xflag7, &yflag7, &zflag7);
	CalcCubePos (&xpos8, &ypos8, &zpos8, &speedx8, &speedy8, &speedz8, &xflag8, &yflag8, &zflag8);
	CalcCubePos (&xpos9, &ypos9, &zpos9, &speedx9, &speedy9, &speedz9, &xflag9, &yflag9, &zflag9);
	CalcCubePos (&xpos10, &ypos10, &zpos10, &speedx10, &speedy10, &speedz10, &xflag10, &yflag10, &zflag10);

	cube1->CubeRotate (CUBE_X_AXIS, fAngleX * 2);
	cube1->CubeRotate (CUBE_Y_AXIS, fAngleY * 3);
	cube1->CubeRotate (CUBE_Z_AXIS, fAngleZ * 4);

	cube2->CubeRotate (CUBE_X_AXIS, fAngleX * 1);
	cube2->CubeRotate (CUBE_Y_AXIS, fAngleY * 2);
	cube2->CubeRotate (CUBE_Z_AXIS, fAngleZ * 3);

	cube3->CubeRotate (CUBE_X_AXIS, fAngleX * 4);
	cube3->CubeRotate (CUBE_Y_AXIS, fAngleY * 3);
	cube3->CubeRotate (CUBE_Z_AXIS, fAngleZ * 2);

	cube4->CubeRotate (CUBE_X_AXIS, fAngleX * 2);
	cube4->CubeRotate (CUBE_Y_AXIS, fAngleY * 1);
	cube4->CubeRotate (CUBE_Z_AXIS, fAngleZ * 2);

	cube5->CubeRotate (CUBE_X_AXIS, fAngleX * 3);
	cube5->CubeRotate (CUBE_Y_AXIS, fAngleY * 1);
	cube5->CubeRotate (CUBE_Z_AXIS, fAngleZ * 4);

	cube6->CubeRotate (CUBE_X_AXIS, fAngleX * 4);
	cube6->CubeRotate (CUBE_Y_AXIS, fAngleY * 2);
	cube6->CubeRotate (CUBE_Z_AXIS, fAngleZ * 5);

	cube7->CubeRotate (CUBE_X_AXIS, fAngleX * 1);
	cube7->CubeRotate (CUBE_Y_AXIS, fAngleY * 4);
	cube7->CubeRotate (CUBE_Z_AXIS, fAngleZ * 1);

	cube8->CubeRotate (CUBE_X_AXIS, fAngleX * 3);
	cube8->CubeRotate (CUBE_Y_AXIS, fAngleY * 4);
	cube8->CubeRotate (CUBE_Z_AXIS, fAngleZ * 1);

	cube9->CubeRotate (CUBE_X_AXIS, fAngleX * 5);
	cube9->CubeRotate (CUBE_Y_AXIS, fAngleY * 2);
	cube9->CubeRotate (CUBE_Z_AXIS, fAngleZ * 2);

	cube10->CubeRotate (CUBE_X_AXIS, fAngleX * 4);
	cube10->CubeRotate (CUBE_Y_AXIS, fAngleY * 3);
	cube10->CubeRotate (CUBE_Z_AXIS, fAngleZ * 2);

	cube1->CubeMove (CUBE_X_AXIS, xpos1);
	cube1->CubeMove (CUBE_Y_AXIS, ypos1);
	cube1->CubeMove (CUBE_Z_AXIS, zpos1);

	cube2->CubeMove (CUBE_X_AXIS, xpos2);
	cube2->CubeMove (CUBE_Y_AXIS, ypos2);
	cube2->CubeMove (CUBE_Z_AXIS, zpos2);

	cube3->CubeMove (CUBE_X_AXIS, xpos3);
	cube3->CubeMove (CUBE_Y_AXIS, ypos3);
	cube3->CubeMove (CUBE_Z_AXIS, zpos3);

	cube4->CubeMove (CUBE_X_AXIS, xpos4);
	cube4->CubeMove (CUBE_Y_AXIS, ypos4);
	cube4->CubeMove (CUBE_Z_AXIS, zpos4);

	cube5->CubeMove (CUBE_X_AXIS, xpos5);
	cube5->CubeMove (CUBE_Y_AXIS, ypos5);
	cube5->CubeMove (CUBE_Z_AXIS, zpos5);

	cube6->CubeMove (CUBE_X_AXIS, xpos6);
	cube6->CubeMove (CUBE_Y_AXIS, ypos6);
	cube6->CubeMove (CUBE_Z_AXIS, zpos6);

	cube7->CubeMove (CUBE_X_AXIS, xpos7);
	cube7->CubeMove (CUBE_Y_AXIS, ypos7);
	cube7->CubeMove (CUBE_Z_AXIS, zpos7);

	cube8->CubeMove (CUBE_X_AXIS, xpos8);
	cube8->CubeMove (CUBE_Y_AXIS, ypos8);
	cube8->CubeMove (CUBE_Z_AXIS, zpos8);

	cube9->CubeMove (CUBE_X_AXIS, xpos9);
	cube9->CubeMove (CUBE_Y_AXIS, ypos9);
	cube9->CubeMove (CUBE_Z_AXIS, zpos9);
	
	cube10->CubeMove (CUBE_X_AXIS, xpos10);
	cube10->CubeMove (CUBE_Y_AXIS, ypos10);
	cube10->CubeMove (CUBE_Z_AXIS, zpos10);
/*

	plane1->PlaneMove (PLANE_Z_AXIS, -30);

	plane2->PlaneMove (PLANE_X_AXIS, -5);
	plane2->PlaneMove (PLANE_Z_AXIS, -20);
	plane2->PlaneRotate (PLANE_Y_AXIS, 90);

	plane3->PlaneMove (PLANE_X_AXIS, 5);
	plane3->PlaneMove (PLANE_Z_AXIS, -20);
	plane3->PlaneRotate (PLANE_Y_AXIS, -90);

	plane4->PlaneMove (PLANE_Y_AXIS, -5);
	plane4->PlaneMove (PLANE_Z_AXIS, -20);
	plane4->PlaneRotate (PLANE_X_AXIS, -90);

	plane5->PlaneMove (PLANE_Y_AXIS, 5);
	plane5->PlaneMove (PLANE_Z_AXIS, -20);
	plane5->PlaneRotate (PLANE_X_AXIS, 90);


	plane1->PlaneDraw ();
	plane2->PlaneDraw ();
	plane3->PlaneDraw ();
	plane4->PlaneDraw ();
	plane5->PlaneDraw ();
*/
	cube1->CubeDraw ();
	cube2->CubeDraw ();
	cube3->CubeDraw ();
	cube4->CubeDraw ();
	cube5->CubeDraw ();
	cube6->CubeDraw ();
	cube7->CubeDraw ();
	cube8->CubeDraw ();
	cube9->CubeDraw ();
	cube10->CubeDraw ();

	eglSwapBuffers (window->egldisplay, window->eglsurface);
	assert (eglGetError () == EGL_SUCCESS);
}

void CalcCubePos (float *xpos, float *ypos, float *zpos, float *speedx, float *speedy, float *speedz, int *xflag, int *yflag, int *zflag)
{
	static int flagxant;
	static int flagyant;
	static int flagzant;

	flagxant = *xflag;
	flagyant = *yflag;
	flagzant = *zflag;

	if (*xpos >= 4.0) *xflag = 1;
	if (*xpos <= -4.0) *xflag = 0;

	if (*ypos >= 4.0) *yflag = 1;
	if (*ypos <= -4.0) *yflag = 0;

	//if (*zpos >= -12.0) *zflag = 1;
	//if (*zpos <= -30.0) *zflag = 0;

	if (flagxant != *xflag) *speedx = random () / 10000000000.0 * 0.9;
	if (flagyant != *yflag) *speedy = random () / 10000000000.0 * 0.9;
	if (flagzant != *zflag) *speedz = random () / 10000000000.0 * 0.9;
	

	if (! *xflag) *xpos+=*speedx;
	else *xpos-=*speedx;

	if (! *yflag) *ypos+=*speedy;
	else *ypos-=*speedy;

//	if (! *zflag) *zpos+=*speedz;
//	else *zpos-=*speedz;

	if (*speedx >= 0.1) *speedx-=0.01;
	if (*speedy >= 0.1) *speedy-=0.01;
	if (*speedz >= 0.1) *speedz-=0.01;
}

unsigned long GetTime(void)
{
	timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long sec = tv.tv_sec;
	return (unsigned long)((sec * (unsigned long)1000) + (tv.tv_usec / 1000.0));
}
