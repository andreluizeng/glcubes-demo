/***************************************************************************
 *   Copyright (C) 2010 by Andre L. V. da Silva   									*
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

#include <glcube.h>

/* Image type - contains height, width, and data */
typedef struct Image_s {
        unsigned long sizeX;
        unsigned long sizeY;
        char *data;
} Image;



// Fragment and vertex shaders code
const char *cubefrag_shader_src =		"uniform sampler2D sampler2d; 				\n"
						"varying mediump vec2	myTexCoord; 			\n"
						"void main (void)					\n"
						"							\n"
						"{							\n"
						" gl_FragColor = texture2D(sampler2d,myTexCoord);	\n"
						"}							\n";
const char *cubevertex_shader_src =		"attribute highp vec4	myVertex;			\n"
						"attribute mediump vec4	myUV;				\n"
						"uniform mediump mat4	myPMVMatrix;			\n"
						"varying mediump vec2	myTexCoord;			\n"
						"uniform   mat4 g_matModelView;				\n"
						"uniform   mat4 g_matProj;				\n"
						"attribute vec4 g_vPosition;				\n"
						"							\n"
						"void main(void)					\n"
						"{							\n"
						" vec4 vPositionES = g_matModelView * g_vPosition;	\n"
						" gl_Position  = g_matProj * vPositionES;		\n"
						" myTexCoord = myUV.st;					\n"
						"}							\n";

//--------------------------------------------------------------------------------------
// Name: CreateCube
// Desc: Create a cube with  user-defined width, height and depth at (0, 0, 0)
// which means center of screen, since coordinates goes from (-x, -y, -z)  to  (x, y, z)
//--------------------------------------------------------------------------------------
void GLCube::CubeCreate (float w, float h, float d)
{
	int i = 0;
	int j = 0;

	float uvcoords[] =
	{
			0.0f, 1.0f,		// lower left
		  	1.0f, 1.0f,		// lower right
		  	0.0f, 0.0f,		// upper left
		  	0.0f, 0.0f,		// upper left
		   1.0f, 1.0f,		// lower right
			1.0f, 0.0f		// upper right
	};

	float xmid;
	float ymid;
	float zmid;

	struct CubeAxis
	{
		float coord[3];
	};

	CubeAxis llf;	// lower left 		- front
	CubeAxis lrf;	// lower right 	- front
	CubeAxis ulf;	// upper left  	- front
	CubeAxis urf;	// upper right		- front

	CubeAxis llb;	// lower left		- back
	CubeAxis lrb;	// lower right		- back
	CubeAxis ulb;	// upper left		- back
	CubeAxis urb;	// upper right		- back

	_width 	= 0.0;
	_height = 0.0;
	_depth 	= 0.0;
	_xpos 	= 0.0;	// translating
	_ypos 	= 0.0;
	_zpos 	= 0.0;
	_xangle	= 0.0;
	_yangle	= 0.0;
	_zangle	= 0.0;
	_xmov 	= 0.0;	// move (screen location)
	_ymov 	= 0.0;
	_zmov 	= 0.0;

	for (i = 0; i < 108; i++)
	{
		vertex[i] = 0;
	}

	for (i = 0; i < 72; i++)
	{
		texcoords[i] = 0;
	}

	_width  = w;
	_height = h;
	_depth  = d;

	xmid = _width / 2.0;
	ymid = _height / 2.0;
	zmid = _depth / 2.0;

	_xscale = 1;
	_yscale = 1;
	_zscale = 1;

	// lower left - front
	llf.coord[0] = -xmid;
	llf.coord[1] = -ymid;
	llf.coord[2] = zmid;

	// lower right - front
	lrf.coord[0] = xmid;
	lrf.coord[1] = -ymid;
	lrf.coord[2] = zmid;

	// upper left - front
	ulf.coord[0] = -xmid;
	ulf.coord[1] = ymid;
	ulf.coord[2] = zmid;

	// upper right - front
	urf.coord[0] = xmid;
	urf.coord[1] = ymid;
	urf.coord[2] = zmid;

	// lower left - back
	llb.coord[0] = -xmid;
	llb.coord[1] = -ymid;
	llb.coord[2] = -zmid;

	// lower right - back
	lrb.coord[0] = xmid;
	lrb.coord[1] = -ymid;
	lrb.coord[2] = -zmid;

	// upper left - back
	ulb.coord[0] = -xmid;
	ulb.coord[1] = ymid;
	ulb.coord[2] = -zmid;

	// upper right - back
	urb.coord[0] = xmid;
	urb.coord[1] = ymid;
	urb.coord[2] = -zmid;

	// -----------------------------
	// front face
	// lower left - front
	vertex[0] 	= llf.coord[0];
	vertex[1] 	= llf.coord[1];
	vertex[2] 	= llf.coord[2];

	// lower right - front
	vertex[3] 	= lrf.coord[0];
	vertex[4] 	= lrf.coord[1];
	vertex[5] 	= lrf.coord[2];

	// upper left - front
	vertex[6] 	= ulf.coord[0];
	vertex[7] 	= ulf.coord[1];
	vertex[8] 	= ulf.coord[2];

	// upper left - front
	vertex[9] 	= ulf.coord[0];
	vertex[10] 	= ulf.coord[1];
	vertex[11] 	= ulf.coord[2];

	// lower right - front
	vertex[12] 	= lrf.coord[0];
	vertex[13] 	= lrf.coord[1];
	vertex[14] 	= lrf.coord[2];

	// upper right - front
	vertex[15] 	= urf.coord[0];
	vertex[16] 	= urf.coord[1];
	vertex[17] 	= urf.coord[2];


	// -----------------------------
	// back face
	// lower right - back
	vertex[18] 	= lrb.coord[0];
	vertex[19] 	= lrb.coord[1];
	vertex[20] 	= lrb.coord[2];

	// lower left - back
	vertex[21] 	= llb.coord[0];
	vertex[22] 	= llb.coord[1];
	vertex[23] 	= llb.coord[2];

	// upper right - back
	vertex[24] 	= urb.coord[0];
	vertex[25] 	= urb.coord[1];
	vertex[26] 	= urb.coord[2];

	// upper right - back
	vertex[27] 	= urb.coord[0];
	vertex[28] 	= urb.coord[1];
	vertex[29] 	= urb.coord[2];

	// lower left - back
	vertex[30] 	= llb.coord[0];
	vertex[31] 	= llb.coord[1];
	vertex[32] 	= llb.coord[2];

	// upper left - back
	vertex[33] 	= ulb.coord[0];
	vertex[34] 	= ulb.coord[1];
	vertex[35] 	= ulb.coord[2];


	// -----------------------------
	// left face
	// lower left - back
	vertex[36] 	= llb.coord[0];
	vertex[37] 	= llb.coord[1];
	vertex[38] 	= llb.coord[2];

	// lower left - front
	vertex[39] 	= llf.coord[0];
	vertex[40] 	= llf.coord[1];
	vertex[41] 	= llf.coord[2];

	// Upper left - back
	vertex[42] 	= ulb.coord[0];
	vertex[43] 	= ulb.coord[1];
	vertex[44] 	= ulb.coord[2];

	// Upper left - back
	vertex[45] 	= ulb.coord[0];
	vertex[46] 	= ulb.coord[1];
	vertex[47] 	= ulb.coord[2];

	// lower left - front
	vertex[48] 	= llf.coord[0];
	vertex[49] 	= llf.coord[1];
	vertex[50] 	= llf.coord[2];

	// upper left - front
	vertex[51] 	= ulf.coord[0];
	vertex[52] 	= ulf.coord[1];
	vertex[53] 	= ulf.coord[2];

	// -----------------------------
	// right face
	// lower right - front
	vertex[54] 	= lrf.coord[0];
	vertex[55] 	= lrf.coord[1];
	vertex[56] 	= lrf.coord[2];

	// lower right - back
	vertex[57] 	= lrb.coord[0];
	vertex[58] 	= lrb.coord[1];
	vertex[59] 	= lrb.coord[2];

	// upper right - front
	vertex[60] 	= urf.coord[0];
	vertex[61] 	= urf.coord[1];
	vertex[62] 	= urf.coord[2];

	// upper right - front
	vertex[63] 	= urf.coord[0];
	vertex[64] 	= urf.coord[1];
	vertex[65] 	= urf.coord[2];

	// lower right - back
	vertex[66] 	= lrb.coord[0];
	vertex[67] 	= lrb.coord[1];
	vertex[68] 	= lrb.coord[2];

	// upper right - back
	vertex[69] 	= urb.coord[0];
	vertex[70] 	= urb.coord[1];
	vertex[71] 	= urb.coord[2];
	

	// -----------------------------
	// top face
	// upper left - front
	vertex[72] 	= ulf.coord[0];
	vertex[73] 	= ulf.coord[1];
	vertex[74] 	= ulf.coord[2];

	// upper right - front
	vertex[75] 	= urf.coord[0];
	vertex[76] 	= urf.coord[1];
	vertex[77] 	= urf.coord[2];

	// Upper left - back
	vertex[78] 	= ulb.coord[0];
	vertex[79] 	= ulb.coord[1];
	vertex[80] 	= ulb.coord[2];

	// Upper left - back
	vertex[81] 	= ulb.coord[0];
	vertex[82] 	= ulb.coord[1];
	vertex[83] 	= ulb.coord[2];

	// upper right - front
	vertex[84] 	= urf.coord[0];
	vertex[85] 	= urf.coord[1];
	vertex[86] 	= urf.coord[2];

	// upper right - back
	vertex[87] 	= urb.coord[0];
	vertex[88] 	= urb.coord[1];
	vertex[89] 	= urb.coord[2];

	// -----------------------------
	// bottom face
	// lower right - front
	vertex[90] 	= lrf.coord[0];
	vertex[91] 	= lrf.coord[1];
	vertex[92] 	= lrf.coord[2];

	// lower left - front
	vertex[93] 	= llf.coord[0];
	vertex[94] 	= llf.coord[1];
	vertex[95] 	= llf.coord[2];

	// lower right - back
	vertex[96] 	= lrb.coord[0];
	vertex[97] 	= lrb.coord[1];
	vertex[98] 	= lrb.coord[2];

	// lower right - back
	vertex[99] 	= lrb.coord[0];
	vertex[100]	= lrb.coord[1];
	vertex[101]	= lrb.coord[2];

	// lower left - front
	vertex[102] = llf.coord[0];
	vertex[103] = llf.coord[1];
	vertex[104] = llf.coord[2];

	// lower left - back
	vertex[105] = llb.coord[0];
	vertex[106] = llb.coord[1];
	vertex[107] = llb.coord[2];


	// -----------------------------
	// UV coords - Front
	for (i = 0, j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	// UV coords - Back
	for (j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	// UV coords - Left
	for (j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	// UV coords - Right
	for (j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	// UV coords - Top
	for (j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	// UV coords - Bottom
	for (j = 0; j < 12; j++, i++)
	{
		texcoords[i] = uvcoords[j];
	}

	LoadIdentityMatrix4x4 (_modelview_matrix);

	if (! CreateShaderProgram ())
	{
		printf ("\nError Creating Cube Shaders Program");
	}

	return;
}


//--------------------------------------------------------------------------------------
// Name: CubeLoadTextureBMP
// Desc: loads a bmp file to a  texture
//--------------------------------------------------------------------------------------
int GLCube::CubeLoadTextureBMP (char *filename, int *width, int *height, char **data)
{
	Image *image;
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	unsigned long i;                    // standard counter.
	unsigned short int planes;          // number of planes in image (must be 1) 
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // temporary color storage for bgr-rgb conversion.


	// allocate space for texture we will use
	image = (Image *) malloc(sizeof(Image));
	if (image == NULL) 
	{
		printf("Error allocating space for image");
		return 0;
	}	

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL)
	{
		printf("File Not Found : %s\n",filename);
		return 0;
	}
    
	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);
    
	// read the height 
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image->sizeX * image->sizeY * 3;
	//printf("size is %lu\n",size);

    // read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

    // read the bpp
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}
	
    // seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

    // read the data. 
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;	
	}

	(*data) = (char *) malloc(size);
	if ((*data) == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;	
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}
	
	(*width) = image->sizeX;
	(*height) = image->sizeY;
	memcpy ((*data), image->data, (*width) * (*height) * 3);
	//data = image->data;
	
	// Free up any memory we may have used
	free(image);
	
	return 1;
}

//--------------------------------------------------------------------------------------
// Name: CubeTranslate
// Desc: Translates the cube along the axis
//--------------------------------------------------------------------------------------
void GLCube::CubeTranslate (float x, float z, float y)
{
 	float trans[16] = {0};
	float aux[16] = {0};
	int i;

	for (i = 0; i < 16; i++)
		aux[i] = _modelview_matrix[i];

	LoadIdentityMatrix4x4 (_modelview_matrix);
 	LoadIdentityMatrix4x4(trans);

	_xpos = x;
	_ypos = y;
	_zpos = z;


 	trans[12] = _xpos;
 	trans[13] = _ypos;
 	trans[14] = _zpos;

 	MultMatrix4x4 (_modelview_matrix, trans, aux);

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeMove
// Desc: move the cube along a determined axis
//--------------------------------------------------------------------------------------
void GLCube::CubeMove	(int axis, float value)
{

	switch (axis)
	{
		case CUBE_X_AXIS:	_xmov = value;
					_xpos = value;
					break;
					
		case CUBE_Y_AXIS:	_ymov = value;
					_ypos = value;
					break;
		
		case CUBE_Z_AXIS:	_zmov = value;
					_zpos = value;
					break;

		default:		printf("invalid axis \n");
					break;
	}

	
	_modelview_matrix[12] = _xmov;
	_modelview_matrix[13] = _ymov;
	_modelview_matrix[14] = _zmov;

	return;
}


//--------------------------------------------------------------------------------------
// Name: CubeRotate
// Desc: Rotates the cube over the given axis
//--------------------------------------------------------------------------------------
void GLCube::CubeRotate (int axis, float angle)
{
	float radians = PI_OVER_360*2*angle;
	float rotate[16] = {0};
	float aux[16] = {0};
	int i;

	for (i = 0; i < 16; i++)
		aux[i] = _modelview_matrix[i];

	LoadIdentityMatrix4x4 (_modelview_matrix);
	LoadIdentityMatrix4x4 (rotate);

	
	switch (axis)
	{
		case CUBE_X_AXIS:		_xangle = radians;
									rotate[5] 	=  cos (_xangle);
									rotate[6] 	=  sin (_xangle);
									rotate[9] 	= -sin (_xangle);
									rotate[10] 	=  cos (_xangle);
									MultMatrix4x4 (_modelview_matrix, rotate, aux);
									break;

		case CUBE_Y_AXIS:		_yangle = radians;
									rotate[0] 	=  cos(_yangle);
									rotate[2] 	= -sin(_yangle);
									rotate[8] 	=  sin(_yangle);
									rotate[10] 	=  cos(_yangle);
									MultMatrix4x4 (_modelview_matrix, rotate, aux);
									break;

		case CUBE_Z_AXIS:		_zangle = radians;
									rotate[0] 	=  cos(_zangle);
									rotate[1] 	=  sin(_zangle);
									rotate[4] 	= -sin(_zangle);
									rotate[5] 	=  cos(_zangle);
									MultMatrix4x4 (_modelview_matrix, rotate, aux);
									break;

		default:					printf("invalid axis \n");
									break;
	}


	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeScale
// Desc: Scales the cube along the given axis
//--------------------------------------------------------------------------------------
void GLCube::CubeScale (int axis, float value)
{
	float aux[16] = {0};
	float scale[16] = {0};
	int i;


	for (i = 0; i < 16; i++)
		aux[i] = _modelview_matrix[i];

	LoadIdentityMatrix4x4 (_modelview_matrix);
	LoadIdentityMatrix4x4 (scale);

	switch (axis)
	{
		case CUBE_X_AXIS:		_xscale = value;
									scale[0] = _xscale;
									MultMatrix4x4 (_modelview_matrix, scale, aux);
									break;

		case CUBE_Y_AXIS:		_yscale = value;
									scale[5] = _yscale;
									MultMatrix4x4 (_modelview_matrix, scale, aux);
									break;

		case CUBE_Z_AXIS:		_zscale = value;
									scale[10] = _zscale;
									MultMatrix4x4 (_modelview_matrix, scale, aux);
									break;

		default:					printf("invalid axis \n");
									break;
	}

	return;

}

//--------------------------------------------------------------------------------------
// Name: CubeLoadIdentity
// Desc: Loads Identity matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeLoadIdentity (void)
{
	LoadIdentityMatrix4x4 (_modelview_matrix);	

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeReset
// Desc: Reset cube rotation and location
//--------------------------------------------------------------------------------------
void GLCube::CubeReset (void)
{
	_xangle = 0;
	_yangle = 0;
	_zangle = 0;

	_xpos = 0;
	_ypos = 0;
	_zpos = 0;

	_xmov = 0;
	_ymov = 0;
	_zmov = 0;

	CubeRotate (CUBE_X_AXIS, _xangle);
	CubeRotate (CUBE_Y_AXIS, _yangle);
	CubeRotate (CUBE_Z_AXIS, _zangle);

	CubeTranslate (_xpos, _ypos, _zpos);

	LoadIdentityMatrix4x4 (_modelview_matrix);

	return;
}


//--------------------------------------------------------------------------------------
// Name: CubeTexFace
// Desc: Texturize a determined cube face with the given texture
//--------------------------------------------------------------------------------------
void GLCube::CubeSetFaceTexBuf (int face, char *texture_data, int w, int h)
{
	switch (face)
	{
		case FRONT_FACE:	glBindTexture(GL_TEXTURE_2D, _texture[FRONT_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		case BACK_FACE:		glBindTexture(GL_TEXTURE_2D, _texture[BACK_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		case LEFT_FACE:	
					glBindTexture(GL_TEXTURE_2D, _texture[LEFT_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		case RIGHT_FACE:	
					glBindTexture(GL_TEXTURE_2D, _texture[RIGHT_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		case TOP_FACE:		
					glBindTexture(GL_TEXTURE_2D, _texture[TOP_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		case BOTTOM_FACE:	glBindTexture(GL_TEXTURE_2D, _texture[BOTTOM_FACE]);
					glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
					break;

		default:				printf ("\nWrong Face\n");
								break;
	}

	// Set the filtering mode
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeGetAxisAngle
// Desc: Get the angle value of rotation over a given axis
//--------------------------------------------------------------------------------------
float GLCube::CubeGetAxisAngle (int axis)
{
	float angle = 0;

	switch (axis)
	{
		case CUBE_X_AXIS:	angle = _xangle;
					break;

		case CUBE_Y_AXIS:	angle = _yangle;
					break;

		case CUBE_Z_AXIS: 	angle = _zangle;
					break;

		default:		printf("invalid axis \n");
					break;
	}

	return angle;
}

//--------------------------------------------------------------------------------------
// Name: CubeGetAxisPos
// Desc: Get the position value of translation on a given axis
//--------------------------------------------------------------------------------------
float GLCube::CubeGetAxisPos (int axis)
{
	float pos = 0;

	switch (axis)
	{
		case CUBE_X_AXIS:	pos = _xpos;
					break;

		case CUBE_Y_AXIS:	pos = _ypos;
					break;

		case CUBE_Z_AXIS: 	pos = _zpos;
					break;

		default:		printf("invalid axis \n");
					break;
	}

	return pos;
}

//--------------------------------------------------------------------------------------
// Name: CubeDraw
// Desc: Draws the previously created cube
//--------------------------------------------------------------------------------------
void GLCube::CubeDraw (void)
{
	// Set the shader program
	glUseProgram (_shader_program);

	// First gets the location of that variable in the shader using its name
	glUniformMatrix4fv (_modelview_location, 1, 0, _modelview_matrix);
	glUniformMatrix4fv (_projview_location,  1, 0, _projection_matrix);

	// Pass the vertex data
	glVertexAttribPointer(CUBE_VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, vertex);
	glEnableVertexAttribArray(CUBE_VERTEX_ARRAY);

	// Pass the texture coordinates data
	glVertexAttribPointer (CUBE_TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, 0, texcoords);
	glEnableVertexAttribArray (CUBE_TEXCOORD_ARRAY);

	// enable depth test
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glDepthMask (GL_TRUE);

	// cull backside of polygons
	glEnable(GL_CULL_FACE);
	glCullFace (GL_BACK);

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, _texture[FRONT_FACE]);
	glDrawArrays (GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, _texture[BACK_FACE]);
	glDrawArrays (GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, _texture[LEFT_FACE]);
	glDrawArrays (GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, _texture[RIGHT_FACE]);
	glDrawArrays (GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, _texture[TOP_FACE]);
	glDrawArrays (GL_TRIANGLES, 24, 6);

	glBindTexture(GL_TEXTURE_2D, _texture[BOTTOM_FACE]);
	glDrawArrays (GL_TRIANGLES, 30, 6);

	//disable client state
	glDisableVertexAttribArray	(CUBE_VERTEX_ARRAY);
	glDisableVertexAttribArray	(CUBE_TEXCOORD_ARRAY);

	LoadIdentityMatrix4x4 (_modelview_matrix);

	return;
}

void GLCube::CubeShowCoords (void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	printf ("\nFront Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
  		printf ("\n");
	}


	printf ("\nBack Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nLeft Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nRight Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
		printf ("\n");
	}


	printf ("\nTop Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nBottom Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			printf ("%lf ", vertex[k]);
			k++;
  		}
		printf ("\n");
	}

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeShowUVCoords
// Desc: Show cube UV coordinates
//--------------------------------------------------------------------------------------
void GLCube::CubeShowUVCoords (void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	printf ("\nFront Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
  		printf ("\n");
	}


	printf ("\nBack Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nLeft Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nRight Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
		printf ("\n");
	}


	printf ("\nTop Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
		printf ("\n");
	}

	printf ("\nBottom Face:\n");
	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < 2; i++)
		{
			printf ("%lf ", texcoords[k]);
			k++;
  		}
		printf ("\n");
	}

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeShowModelMatrix
// Desc: Show cube modelview matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeShowModelMatrix (void)
{
	int i;

	printf ("\nModelview Matrix:\n");

	for (i = 0; i < 4; i++)
		printf ("\n%.2f\t%.2f\t%.2f\t%.2f\t", _modelview_matrix[i*4], _modelview_matrix[i*4+1], _modelview_matrix[i*4+2], _modelview_matrix[i*4+3]);
	printf ("\n");
	
	return;
}

//--------------------------------------------------------------------------------------
// Name: MultMatrix4x4
// Desc: 4x4 Matrix Multiplication
//--------------------------------------------------------------------------------------
void GLCube::MultMatrix4x4 (float *matC, float *matA, float *matB)
{
	matC[ 0] = matA[ 0] * matB[ 0] + matA[ 1] * matB[ 4] + matA[ 2] * matB[ 8] + matA[ 3] * matB[12];
	matC[ 1] = matA[ 0] * matB[ 1] + matA[ 1] * matB[ 5] + matA[ 2] * matB[ 9] + matA[ 3] * matB[13];
	matC[ 2] = matA[ 0] * matB[ 2] + matA[ 1] * matB[ 6] + matA[ 2] * matB[10] + matA[ 3] * matB[14];
	matC[ 3] = matA[ 0] * matB[ 3] + matA[ 1] * matB[ 7] + matA[ 2] * matB[11] + matA[ 3] * matB[15];
	matC[ 4] = matA[ 4] * matB[ 0] + matA[ 5] * matB[ 4] + matA[ 6] * matB[ 8] + matA[ 7] * matB[12];
	matC[ 5] = matA[ 4] * matB[ 1] + matA[ 5] * matB[ 5] + matA[ 6] * matB[ 9] + matA[ 7] * matB[13];
	matC[ 6] = matA[ 4] * matB[ 2] + matA[ 5] * matB[ 6] + matA[ 6] * matB[10] + matA[ 7] * matB[14];
	matC[ 7] = matA[ 4] * matB[ 3] + matA[ 5] * matB[ 7] + matA[ 6] * matB[11] + matA[ 7] * matB[15];
	matC[ 8] = matA[ 8] * matB[ 0] + matA[ 9] * matB[ 4] + matA[10] * matB[ 8] + matA[11] * matB[12];
	matC[ 9] = matA[ 8] * matB[ 1] + matA[ 9] * matB[ 5] + matA[10] * matB[ 9] + matA[11] * matB[13];
	matC[10] = matA[ 8] * matB[ 2] + matA[ 9] * matB[ 6] + matA[10] * matB[10] + matA[11] * matB[14];
	matC[11] = matA[ 8] * matB[ 3] + matA[ 9] * matB[ 7] + matA[10] * matB[11] + matA[11] * matB[15];
	matC[12] = matA[12] * matB[ 0] + matA[13] * matB[ 4] + matA[14] * matB[ 8] + matA[15] * matB[12];
	matC[13] = matA[12] * matB[ 1] + matA[13] * matB[ 5] + matA[14] * matB[ 9] + matA[15] * matB[13];
	matC[14] = matA[12] * matB[ 2] + matA[13] * matB[ 6] + matA[14] * matB[10] + matA[15] * matB[14];
	matC[15] = matA[12] * matB[ 3] + matA[13] * matB[ 7] + matA[14] * matB[11] + matA[15] * matB[15];

	return;
}

//--------------------------------------------------------------------------------------
// Name: LoadIdentityMatrix4x4
// Desc: Load a 4x4 indentity matrix
//--------------------------------------------------------------------------------------
void GLCube::LoadIdentityMatrix4x4 (float *m)
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	
	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;
	
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;

	return;
}

//--------------------------------------------------------------------------------------
// Name: GenTexture()
// Desc: Generate texture
//--------------------------------------------------------------------------------------
GLuint GLCube::GenTextures (void)
{
	GLuint texture_id = 0;

	// Use tightly packed data
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Allocates one texture handle
	glGenTextures (1, &texture_id);
	
	return texture_id;
}

//--------------------------------------------------------------------------------------
// Name: CubeCreateTex()
// Desc: alocates cube textures
//--------------------------------------------------------------------------------------
void GLCube::CubeCreateTex	(void)
{
	// textures
	_texture[FRONT_FACE] 		= GenTextures ();
	_texture[BACK_FACE] 		= GenTextures ();
	_texture[LEFT_FACE] 		= GenTextures ();
	_texture[RIGHT_FACE] 		= GenTextures ();
	_texture[TOP_FACE] 		= GenTextures ();
	_texture[BOTTOM_FACE] 		= GenTextures ();

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeDestroyTex()
// Desc: dealocates cube textures
//--------------------------------------------------------------------------------------
void GLCube::CubeDestroyTex (void)
{

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeSetProjMatrix ()
// Desc: Set the prjection view matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeSetProjMatrix (float *projection_matrix)
{
	_projection_matrix = projection_matrix;

	return;
}

//--------------------------------------------------------------------------------------
// Name: CreateShaderProgram ()
// Desc: Create the shader program needed to render the scene
//--------------------------------------------------------------------------------------
bool GLCube::CreateShaderProgram (void)
{
	GLint shader_compiled_flag;

	_frag_shader_src = cubefrag_shader_src;
	_vertex_shader_src = cubevertex_shader_src;

	// Create the fragment shader object, Load the source code into it and Compile the source code
	_frag_shader = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (_frag_shader, 1, & _frag_shader_src, NULL);
	glCompileShader (_frag_shader);

	// Check if compilation succeeded
	
	glGetShaderiv (_frag_shader, GL_COMPILE_STATUS, &shader_compiled_flag);
	if (! shader_compiled_flag)
	{
		// An error happened, first retrieve the length of the log message
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(_frag_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		// Allocate enough space for the message and retrieve it
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetShaderInfoLog (_frag_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		printf("Failed to compile fragment shader: %s", pszInfoLog);

		delete [] pszInfoLog;
		return false;
	}

	// Loads the vertex shader in the same way
	_vertex_shader = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (_vertex_shader, 1, &_vertex_shader_src, NULL);
	glCompileShader (_vertex_shader);
	glGetShaderiv (_vertex_shader, GL_COMPILE_STATUS, &shader_compiled_flag);
	if (! shader_compiled_flag)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv (_vertex_shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		char* pszInfoLog = new char[i32InfoLogLength];
		glGetShaderInfoLog (_vertex_shader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);


		printf ("Failed to compile vertex shader: %s", pszInfoLog);

		delete [] pszInfoLog;
		return false;
	}

	// Create the shader program
	_shader_program = glCreateProgram();

	// Attach the fragment and vertex shaders to it
	glAttachShader (_shader_program, _frag_shader);
	glAttachShader (_shader_program, _vertex_shader);


	// Bind the custom vertex attribute "myVertex" to location VERTEX_ARRAY
	//glBindAttribLocation (_shader_program, CUBE_VERTEX_ARRAY, "myVertex");

	// Bind the custom vertex attribute "myUV" to location TEXCOORD_ARRAY
	glBindAttribLocation (_shader_program, CUBE_VERTEX_ARRAY,   "g_vPosition" );
	glBindAttribLocation (_shader_program, CUBE_TEXCOORD_ARRAY, "myUV");
	
	// Link the program
	glLinkProgram (_shader_program);

	// Check if linking succeeded in the same way we checked for compilation success
	GLint bLinked;
	glGetProgramiv (_shader_program, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetProgramiv (_shader_program, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog (_shader_program, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		printf ("Failed to link program: %s", pszInfoLog);

		delete [] pszInfoLog;
		return false;
	}

	// Sets the sampler2D variable to the first texture unit
	glUniform1i (glGetUniformLocation (_shader_program, "sampler2d"), 0);

    // Get uniform locations
	_modelview_location = glGetUniformLocation (_shader_program, "g_matModelView");
	_projview_location  = glGetUniformLocation (_shader_program, "g_matProj");

	return true;
}


//--------------------------------------------------------------------------------------
// Name: CubeSetModelMatrix
// Desc: Sets a new model matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeSetModelMatrix (float *m)
{
	int i;

	for (i = 0; i < 16; i++)
		_modelview_matrix[i] = m[i];

	return;
}


//--------------------------------------------------------------------------------------
// Name: CubeSetRotateMatrix
// Desc: Sets the rotation matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeSetRotationMatrix (float *m)
{
	_modelview_matrix[0] = m[0];
	_modelview_matrix[1] = m[1];
	_modelview_matrix[2] = m[2];

	_modelview_matrix[4] = m[3];
	_modelview_matrix[5] = m[4];
	_modelview_matrix[6] = m[5];
	
	_modelview_matrix[8] = m[6];
	_modelview_matrix[9] = m[7];
	_modelview_matrix[10] = m[8];


	
	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeGetModelViewMatrix
// Desc:gets the modelview matrix
//--------------------------------------------------------------------------------------
void GLCube::CubeGetModelViewMatrix(float*m)
{
	for (int i = 0; i < 16; i++)
		m[i] = _modelview_matrix[i];
	
	return;
}



//--------------------------------------------------------------------------------------
// Name: CubeSetTranslateMatrix
// Desc: Sets the translationMatrix
//--------------------------------------------------------------------------------------
void GLCube::CubeSetTranslationMatrix (float *m)
{
	_modelview_matrix[12] = m[0];
	_modelview_matrix[13] = m[1];
	_modelview_matrix[14] = m[2];

	return;
}

//--------------------------------------------------------------------------------------
// Name: CubeDestroy
// Desc: free cube memory
//--------------------------------------------------------------------------------------
void GLCube::CubeDestroy (void)
{
	int i;

	// Frees the texture
	for (i = 0; i < 6; i ++)
	{
		glDeleteTextures(6, _texture);
	}

	// Frees the OpenGL handles for the program and the 2 shaders
	glDeleteProgram	(_shader_program);
	glDeleteShader		(_vertex_shader);
	glDeleteShader		(_frag_shader);

	return;
}




