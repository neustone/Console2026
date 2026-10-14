#include "pch.h"
#include "WndOpengl.h"
///
#include <gl\gl.h>
#include <gl\glu.h>

namespace CWndOpengl_Pri
{
	static PIXELFORMATDESCRIPTOR pixelFormatDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),//固定值
		1,//固定值
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //|PFD_DOUBLEBUFFER support window,OpenGL,Double Buffering
		PFD_TYPE_RGBA,//RGBA模式，不用调色板
		16,//程序在16位色彩下运行
		0,0,0,0,0,0, //color bits ignored
		0, //no alpha buffer
		0, //shift bit ignored
		0,//no accumulation buffer
		0,0,0,0,//accumbits ignored
		32,//32-bitz-buffer
		0,//nostencilbuffer
		0,//noauxiliarybuffer
		PFD_MAIN_PLANE,//mainlayer
		0,//reserved
		0,0,0//layermasksignored
	};
	///.
	static int nPixelFormat = 0;
	static int nSpin = 0;

#define X .525731112119133606
#define Z .850650808352039932
	static GLfloat vdata[12][3] = {
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} };
	static GLuint tindices[20][3] = {
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };
}


CWndOpengl::CWndOpengl(WND_STYLE_ wndStyle)
	: CWndAurora()
	, m_wndStyle(wndStyle)
	, m_hRC(0)
	, m_rtViewPort()
{
}

CWndOpengl::~CWndOpengl(void)
{
}

int CWndOpengl::onWndCreate()
{
	CWndAurora::onWndCreate();

	return onInitializeOpengl();
}

void CWndOpengl::onWndDestroy()
{
	onReleaseOpengl();

	CWndAurora::onWndDestroy();
}

int CWndOpengl::onInitializeOpengl()
{
	int nRet = -1;
	ASSERT(m_pClientDC);
	///. 
	if (CWndOpengl_Pri::nPixelFormat == 0)
	{
		CWndOpengl_Pri::nPixelFormat = ChoosePixelFormat(m_pClientDC->GetSafeHdc(), &CWndOpengl_Pri::pixelFormatDesc);
	}
	ASSERT(CWndOpengl_Pri::nPixelFormat);
	///. 
	if (SetPixelFormat(m_pClientDC->GetSafeHdc(), CWndOpengl_Pri::nPixelFormat, &CWndOpengl_Pri::pixelFormatDesc) == FALSE)
	{
		MessageBox(L"CWndOpengl::OnInitializeOpenGL, 2");
		return nRet;
	}
	///. link the Win Device Context with the OGL Rendering Context
	if (m_hRC == 0)
	{
		m_hRC = wglCreateContext(m_pClientDC->GetSafeHdc());
	}
	ASSERT(m_hRC);

	//////////////////////////////////////////////////////////////////////////

	if (::wglMakeCurrent(m_pClientDC->GetSafeHdc(), m_hRC))
	{
		glClearDepth(1.0f);			// Depth Buffer Setup

		/* Controls certain aspects of OpenGL behavior in AntiAliasing */
		/* to exercise some control over the trade-off between image quality and speed */
		glHint(
			/* indicates which behavior is to be controlled: */
			/* Specifies the desired quality of color and texture-coordinate interpolation.*/
			GL_PERSPECTIVE_CORRECTION_HINT,
			/* indicate that how the efficient\quality option should be chosen: */
			/* Really Nice Perspective Calculations.*/
			GL_NICEST
		);

		//Note that dithering, unlike many other features, is enabled by default.
		glEnable(GL_DITHER);

		// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
		glColorMaterial(
			GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		GLfloat light_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

		GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		//setup the texture coord generation
//		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);//GL_OBJECT_LINEAR//
//		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		//setup the tex gen
		float xPlane[] = { 1.0f, 0.0f, 0.0f, 0.0f };
		float yPlane[] = { 0.0f, 1.0f, 0.0f, 0.0f };
		float zPlane[] = { 0.0f, 0.0f, 1.0f, 0.0f };
		glTexGenfv(GL_S,GL_EYE_PLANE,xPlane);
		glTexGenfv(GL_T,GL_EYE_PLANE,yPlane);
		glTexGenfv(GL_R,GL_EYE_PLANE,zPlane);

		nRet = 0;
	}
	::wglMakeCurrent(nullptr, nullptr);
	return nRet;
}

void CWndOpengl::onReleaseOpengl()
{
	::wglMakeCurrent(nullptr, nullptr);
	if (m_hRC)
	{
		::wglDeleteContext(m_hRC);
		m_hRC = 0;
	}
}

void CWndOpengl::resetScene()
{
	ASSERT(m_pClientDC);
	ASSERT(m_hRC);
	if (::wglMakeCurrent(m_pClientDC->GetSafeHdc(), m_hRC))
	{
		int nViewOffX(m_rtViewPort.left);
		int nViewOffY(m_rtViewPort.top);
		int nViewWidth(m_rtViewPort.Width());
		int nViewHeight(m_rtViewPort.Height());
		// Reset The Current Viewport
		glViewport(
			nViewOffX, nViewOffY, nViewWidth, nViewHeight);
		///. Select The PROJECTION Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Calculate The Aspect Ratio Of The Window
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		//.Select The Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
		//		glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
		if (nViewHeight > nViewWidth)
		{
			glOrtho(
				-1.5, 1.5,
				-1.5 * nViewHeight / nViewWidth, 1.5 * nViewHeight / nViewWidth,
				-10.0, 10.0);
		}
		else
		{
			glOrtho(
				-1.5 * nViewWidth / nViewHeight, 1.5 * nViewWidth / nViewHeight,
				-1.5, 1.5,
				-10.0, 10.0);
		}

		::wglMakeCurrent(NULL, NULL);
	}
}

int CWndOpengl::onWndRender(CDC* pDC)
{
	TRACE(_T("CWndCoverPage::onWndRender\n"));
	int nRet = -1;
	ASSERT(pDC);
	ASSERT(m_hRC);
	if (::wglMakeCurrent(pDC->GetSafeHdc(), m_hRC))
	{
		/// *** Initialize Environment ***

		/* select clearing (background) color */
		/* Blue background (0.01f, 0.03f, 0.06f, 0.0f);0.0f, 0.0f, 0.0f, 0.0f*/
		glClearColor(0.01f, 0.03f, 0.06f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		//////////////////////////////////////////////////////////////////////////

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);

		/* initialize viewing values */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		///.
//		gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, 1.0); /* modeling transformation */

		CWndOpengl_Pri::nSpin = (CWndOpengl_Pri::nSpin + 30) % 360;
		glPushMatrix();
		{
			GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };
			//glTranslatef (0.0, 0.0, -5.0);
			//glPushMatrix ();
//			glRotated((GLdouble)CWndOpengl_Pri::nSpin, 1.0, 0.0, 0.0);
			glColor3f(0.0, 1.0, 1.0);
			{
				glBegin(GL_TRIANGLES);
				for (int i = 0; i < 20; i++)
				{
					/* color information here */
					glVertex3fv(&CWndOpengl_Pri::vdata[CWndOpengl_Pri::tindices[i][0]][0]);
					glVertex3fv(&CWndOpengl_Pri::vdata[CWndOpengl_Pri::tindices[i][1]][0]);
					glVertex3fv(&CWndOpengl_Pri::vdata[CWndOpengl_Pri::tindices[i][2]][0]);
				}
				glEnd();
			}
		}
		glPopMatrix();

		glDisable(GL_DEPTH_TEST);

		/// *** Release Environment ***

		/// forces execution of OpenGL functions in finite time
		glFlush();
		SwapBuffers(m_pClientDC->GetSafeHdc());
		nRet = 0;
	}
	::wglMakeCurrent(nullptr, nullptr);

	return nRet;
}

void CWndOpengl::onWndSize(UINT nType, int cx, int cy)
{
	CWndAurora::onWndSize(nType, cx, cy);

	if (GetSafeHwnd() && cx > 0 && cy > 0)
	{
		getClientRect(m_rtViewPort);
		
		resetScene();
		onWndRender(getClientDC());
	}
}