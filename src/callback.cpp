#include "glad/glad.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class GladInit
{
	// Log every GL call
	static void preGLcall(const char *name, void *funcptr, int len_args, ...)
	{
		static bool gladLoadGLinProgress = false;
		if (!gladLoadGLinProgress)
		{
			gladLoadGLinProgress = true;

			if (!gladLoadGL())
			{
				fprintf(stderr, "Cannot initialize GLAD OpenGL interception\n");
				exit(-1);
			}
		}

		va_list args;
		va_start(args, len_args);

		if (!strcmp(name, "glAlphaFunc"))
		{
			GLenum func = va_arg(args, GLenum);
			GLclampf ref = va_arg(args, double /* GLclampf */);
		
			printf("glAlphaFunc(");
			switch (func)
			{
			case GL_NEVER :
				printf("GL_NEVER");
				break;
			case GL_LESS :
				printf("GL_LESS");
				break;
			case GL_EQUAL :
				printf("GL_EQUAL");
				break;
			case GL_LEQUAL :
				printf("GL_LEQUAL");
				break;
			case GL_GREATER :
				printf("GL_GREATER");
				break;
			case GL_NOTEQUAL :
				printf("GL_NOTEQUAL");
				break;
			case GL_GEQUAL :
				printf("GL_GEQUAL");
				break;
			case GL_ALWAYS :
				printf("GL_ALWAYS");
				break;
			}
			printf(", %ff);\n", ref);
		}
		else if (!strcmp(name, "glBegin"))
		{
			GLenum mode = va_arg(args, GLenum);

			printf("glBegin(");
			switch (mode)
			{
			case GL_POINTS :
				printf("GL_POINTS");
				break;
			case GL_LINES :
				printf("GL_LINES");
				break;
			case GL_LINE_STRIP :
				printf("GL_LINE_STRIP");
				break;
			case GL_LINE_LOOP :
				printf("GL_LINE_LOOP");
				break;
			case GL_TRIANGLES :
				printf("GL_TRIANGLES");
				break;
			case GL_TRIANGLE_STRIP :
				printf("GL_TRIANGLE_STRIP");
				break;
			case GL_TRIANGLE_FAN :
				printf("GL_TRIANGLE_FAN");
				break;
			case GL_QUADS :
				printf("GL_QUADS");
				break;
			case GL_QUAD_STRIP :
				printf("GL_QUAD_STRIP");
				break;
			case GL_POLYGON :
				printf("GL_POLYGON");
				break;
			}
			printf(");\n");
		}
		else if (!strcmp(name, "glBindTexture"))
		{	
			GLenum target = va_arg(args, GLenum);
			GLuint texture = va_arg(args, GLuint);
			
			printf("glBindTexture(");
			switch (target)
			{
			case GL_TEXTURE_1D :
				printf("GL_TEXTURE_1D");
				break;
			case GL_TEXTURE_2D :
				printf("GL_TEXTURE_2D");
				break;
			case GL_TEXTURE_3D :
				printf("GL_TEXTURE_3D");
				break;
			case GL_TEXTURE_1D_ARRAY :
				printf("GL_TEXTURE_3D");
				break;
			case GL_TEXTURE_2D_ARRAY :
				printf("GL_TEXTURE_2D_ARRAY");
				break;
			case GL_TEXTURE_RECTANGLE :
				printf("GL_TEXTURE_RECTANGLE");
				break;
			case GL_TEXTURE_CUBE_MAP :
				printf("GL_TEXTURE_CUBE_MAP");
				break;
			case GL_TEXTURE_CUBE_MAP_ARRAY :
				printf("GL_TEXTURE_CUBE_MAP_ARRAY");
				break;
			case GL_TEXTURE_BUFFER :
				printf("GL_TEXTURE_BUFFER");
				break;
			case GL_TEXTURE_2D_MULTISAMPLE :
				printf("GL_TEXTURE_2D_MULTISAMPLE");
				break;
			case GL_TEXTURE_2D_MULTISAMPLE_ARRAY :
				printf("GL_TEXTURE_2D_MULTISAMPLE_ARRAY");
				break;
			}
			printf(", %d);\n", texture);
		}
		else if (!strcmp(name, "glCallList"))
		{
			GLuint list = va_arg(args, GLuint);

			printf("glCallList(%d);\n", list);
		}
		else if (!strcmp(name, "glCallLists"))
		{
			GLsizei n = va_arg(args, GLsizei);
			GLenum type = va_arg(args, GLenum);
			GLvoid* lists = va_arg(args, GLvoid*);
			
			printf("glCallLists(%d, ", n);
			switch (type)
			{
			case GL_BYTE :
				printf("GL_BYTE");
				break;
			case GL_UNSIGNED_BYTE :
				printf("GL_UNSIGNED_BYTE");
				break;
			case GL_SHORT :
				printf("GL_SHORT");
				break;
			case GL_UNSIGNED_SHORT :
				printf("GL_UNSIGNED_SHORT");
				break;
			case GL_INT :
				printf("GL_INT");
				break;
			case GL_UNSIGNED_INT :
				printf("GL_UNSIGNED_INT");
				break;
			case GL_FLOAT :
				printf("GL_FLOAT");
				break;
			case GL_2_BYTES :
				printf("GL_2_BYTES");
				break;
			case GL_3_BYTES :
				printf("GL_3_BYTES");
				break;
			case GL_4_BYTES :
				printf("GL_4_BYTES");
				break;
			}
			printf(", %p);\n", lists);
		}
		else if (!strcmp(name, "glClear"))
		{
			GLbitfield mask = va_arg(args, GLbitfield);
		
			printf("glClear(0");
			if (mask & GL_COLOR_BUFFER_BIT)
				printf(" | GL_COLOR_BUFFER_BIT");
			if (mask & GL_DEPTH_BUFFER_BIT)
				printf(" | GL_DEPTH_BUFFER_BIT");
			if (mask & GL_ACCUM_BUFFER_BIT)
				printf(" | GL_ACCUM_BUFFER_BIT");
			if (mask & GL_STENCIL_BUFFER_BIT)
				printf(" | GL_STENCIL_BUFFER_BIT");
			printf(");\n");
		}
		else if (!strcmp(name, "glClearColor"))
		{
			GLclampf red = va_arg(args, double /* GLclampf */);
			GLclampf green = va_arg(args, double /* GLclampf */);
			GLclampf blue = va_arg(args, double /* GLclampf */);
			GLclampf alpha = va_arg(args, double /* GLclampf */);

			printf("glClearColor(%ff, %ff, %ff, %ff);\n",
				red, green, blue, alpha);
		}
		else if (!strcmp(name, "glColor3fv"))
		{
			const GLfloat* v = va_arg(args, const GLfloat*);

			printf("glColor3fv(%ff, %ff, %ff);\n", v[0], v[1], v[2]);
		}
		else if (!strcmp(name, "glColor4fv"))
		{
			const GLfloat* v = va_arg(args, const GLfloat*);

			printf("glColor4fv(%ff, %ff, %ff, %ff);\n", v[0], v[1], v[2], v[3]);
		}
		else if (!strcmp(name, "glDeleteLists"))
		{
			GLuint list = va_arg(args, GLuint);
			GLsizei range = va_arg(args, GLsizei);
		
			printf("glDeleteLists(%d, %d)\n", list, range);
		}
		else if (!strcmp(name, "glDeleteTextures"))
		{
			GLsizei n = va_arg(args, GLsizei);
			const GLuint* textures = va_arg(args, const GLuint*);
			
			printf("glDeleteTextures(%d, %p);\n", n, textures);
		}
		else if (!strcmp(name, "glDepthMask"))
		{
		}
		else if (!strcmp(name, "glDisable"))
		{
		}
		else if (!strcmp(name, "glDrawElements"))
		{
		}
		else if (!strcmp(name, "glEnable"))
		{
		}
		else if (!strcmp(name, "glEnd"))
		{
			printf("glEnd();\n");
		}
		else if (!strcmp(name, "glEndList"))
		{
		}
		else if (!strcmp(name, "glFinish"))
		{
		}
		else if (!strcmp(name, "glFogf"))
		{
		}
		else if (!strcmp(name, "glFogfv"))
		{
		}
		else if (!strcmp(name, "glFogi"))
		{
		}
		else if (!strcmp(name, "glFrontFace"))
		{
		}
		else if (!strcmp(name, "glFrustum"))
		{
		}
		else if (!strcmp(name, "glGenLists"))
		{
		}
		else if (!strcmp(name, "glGenTextures"))
		{
		}
		else if (!strcmp(name, "glGetError"))
		{
		}
		else if (!strcmp(name, "glGetFloatv"))
		{
		}
		else if (!strcmp(name, "glGetIntegerv"))
		{
		}
		else if (!strcmp(name, "glGetString"))
		{
		}
		else if (!strcmp(name, "glGetStringi"))
		{
		}
		else if (!strcmp(name, "glGetTexLevelParameteriv"))
		{
		}
		else if (!strcmp(name, "glLightfv"))
		{
		}
		else if (!strcmp(name, "glLightModelfv"))
		{
		}
		else if (!strcmp(name, "glLightModeli"))
		{
		}
		else if (!strcmp(name, "glLoadIdentity"))
		{
		}
		else if (!strcmp(name, "glLoadMatrixf"))
		{
		}
		else if (!strcmp(name, "glMaterialf"))
		{
		}
		else if (!strcmp(name, "glMaterialfv"))
		{
		}
		else if (!strcmp(name, "glMatrixMode"))
		{
		}
		else if (!strcmp(name, "glMultMatrixf"))
		{
		}
		else if (!strcmp(name, "glNewList"))
		{
		}
		else if (!strcmp(name, "glNormal3f"))
		{
		}
		else if (!strcmp(name, "glNormal3fv"))
		{
		}
		else if (!strcmp(name, "glOrtho"))
		{
		}
		else if (!strcmp(name, "glPixelStorei"))
		{
		}
		else if (!strcmp(name, "glPolygonOffset"))
		{
		}
		else if (!strcmp(name, "glPopAttrib"))
		{
		}
		else if (!strcmp(name, "glPopMatrix"))
		{
		}
		else if (!strcmp(name, "glPushAttrib"))
		{
		}
		else if (!strcmp(name, "glPushMatrix"))
		{
		}
		else if (!strcmp(name, "glRotatef"))
		{
		}
		else if (!strcmp(name, "glScalef"))
		{
		}
		else if (!strcmp(name, "glShadeModel"))
		{
		}
		else if (!strcmp(name, "glTexCoord1fv"))
		{
		}
		else if (!strcmp(name, "glTexCoord2f"))
		{
		}
		else if (!strcmp(name, "glTexCoord2fv"))
		{
		}
		else if (!strcmp(name, "glTexEnvf"))
		{
		}
		else if (!strcmp(name, "glTexEnvfv"))
		{
		}
		else if (!strcmp(name, "glTexEnvi"))
		{
		}
		else if (!strcmp(name, "glTexGenfv"))
		{
		}
		else if (!strcmp(name, "glTexGeni"))
		{
		}
		else if (!strcmp(name, "glTexImage1D"))
		{
		}
		else if (!strcmp(name, "glTexImage2D"))
		{
		}
		else if (!strcmp(name, "glTexParameterf"))
		{
		}
		else if (!strcmp(name, "glTexParameterfv"))
		{
		}
		else if (!strcmp(name, "glTexParameteri"))
		{
		}
		else if (!strcmp(name, "glTranslated"))
		{
		}
		else if (!strcmp(name, "glTranslatef"))
		{
		}
		else if (!strcmp(name, "glVertex3f"))
		{
			GLfloat x = va_arg(args, double /* GLfloat */);
			GLfloat y = va_arg(args, double /* GLfloat */);
			GLfloat z = va_arg(args, double /* GLfloat */);

			printf("glVertex3f(%ff, %ff, %ff);\n", x, y, z);
		}
		else if (!strcmp(name, "glVertex3fv"))
		{
			GLfloat* v = va_arg(args, GLfloat*);

			printf("glVertex3fv(%ff, %ff, %ff);\n", v[0], v[1], v[2]);
		}
		else if (!strcmp(name, "glViewport"))
		{
		}
		else
		{
			va_end(args);
			fprintf(stderr, "Unhandled OpenGL function: %s (%d arguments)\n", name, len_args);
			exit(-1);
		}
		
		va_end(args);
	}

public :

	GladInit()
	{
		glad_set_pre_callback(GladInit::preGLcall);
	}
};

GladInit gladInit;

