#include <stdexcept>

#include "platform.hh"
#include "font.hh"
#include "gl.hh"

void platform_start(int argc, char*argv[])
{
	
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("GUI Toolkit Framework");

	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);


    initGL();

	glutMainLoop ();

}

/* function to build our font list */
void platform_buildFont()
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	HDC hDC = wglGetCurrentDC();

	font_base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(-14,								// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						0,								// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Segoe UI");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, font_base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}


