#ifndef __glcvcube_h__
#define __glcvcube_h__

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <malloc.h> 
#include <math.h> 
#include <stdlib.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#define CUBE_VERTEX_ARRAY 		0
#define CUBE_TEXCOORD_ARRAY 	1
	

#define FRONT_FACE 	0
#define BACK_FACE 	1
#define LEFT_FACE 	2
#define RIGHT_FACE 	3
#define TOP_FACE 		4
#define BOTTOM_FACE 	5

#define CUBE_X_AXIS 0
#define CUBE_Y_AXIS 1
#define CUBE_Z_AXIS 2

#ifndef PI_OVER_360
#define PI_OVER_360		0.00872664f
#endif

class GLCube
{
	public:

		void 	CubeCreate 			(float w, float h, float d);
		void 	CubeCreateTex			(void);
		int	CubeLoadTextureBMP 		(char *filename, int *width, int *height, char **data);			
		void  	CubeDestroyTex			(void);
		void 	CubeTranslate			(float x, float z, float y);
		void 	CubeMove			(int axis, float value);
		void 	CubeRotate			(int axis, float angle);
		void 	CubeScale			(int axis, float value);
		void 	CubeReset			(void);
		void    CubeSetFaceTexBuf 		(int face, char *texture_data, int w, int h);
		void 	CubeSetModelMatrix		(float *m);
		void 	CubeSetTranslationMatrix	(float *m);
		void 	CubeSetRotationMatrix		(float *m);
		float 	CubeGetAxisAngle 		(int axis);
		float	CubeGetAxisPos			(int axis);
		void 	CubeShowCoords			(void);
		void 	CubeShowUVCoords		(void);
		void	CubeDraw			(void);
		void 	CubeShowModelMatrix		(void);
		void 	CubeSetProjMatrix 		(float *projection_matrix);
		void	CubeGetModelViewMatrix		(float *m);
		void 	CubeLoadIdentity		(void);
		void 	CubeDestroy			(void);

	private:


		float _width;
		float _height;
		float _depth;

		float _xpos;
		float _ypos;
		float _zpos;

		float _xmov;
		float _ymov;
		float _zmov;

		float _xangle;
		float _yangle;
		float _zangle;

		float _xscale;
		float _yscale;
		float _zscale;

		float vertex[108];
		float	texcoords[72];

		// textures
		GLuint _texture[6];

		//modelview matrix
		float _modelview_matrix[16];

		// texture_w and h
		GLuint _texture_w;
		GLuint _texture_h;

		// shader program	
		GLuint _shader_program;

		// The vertex and fragment shader OpenGL handles
		GLuint _vertex_shader;
		GLuint _frag_shader;

		// model and projection matrix view
		GLuint _modelview_location;
		GLuint _projview_location;

		const char *_frag_shader_src;
		const char *_vertex_shader_src;

		// projection view matrix
		float *_projection_matrix;

		void 		MultMatrix4x4 		(float *matC, float *matA, float *matB);
		void 		LoadIdentityMatrix4x4 	(float *m);
		GLuint		GenTextures 		(void);
		bool		CreateShaderProgram 	(void);
		
};

#endif
