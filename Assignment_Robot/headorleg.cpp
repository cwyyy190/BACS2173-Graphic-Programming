
#include <Windows.h>
#include <Windowsx.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Robot"                  // Can change the window name
#pragma region define
// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define PI 3.1415927
#pragma endregion
#pragma region void
// VOID for LEG
void wKeyAction();
void aKeyAction();
void sKeyAction();
void dKeyAction();
void qKeyAction();
void lKeyAction();
void jKeyAction();
void vKeyAction();
void rKeyAction();
// VOID for HAND
void zKeyAction(); //arm rotate left 
void xKeyAction(); //arm rotate right 
void cKeyAction();
void bKeyAction();
void nKeyAction();
void mKeyAction();
void lThumb();
void lIndex();
void lMiddle();
void lRing();
void lPinky();
void rThumb();
void rIndex();
void rMiddle();
void rRing();
void rPinky();
void attack();
void shoot();
void createLaserBall();
GLuint loadTexture(LPCSTR filename);
//Lighting Material
void lightGreyMaterial();
void greyMaterial();
void whiteMaterial();
void blackMaterial();
void yellowMaterial();
void redMaterial();
void orangeMaterial();
void lighting();
#pragma endregion
#pragma region Set Variable
double rotateDegree = 0;
int axis[3] = { 0,0,0 };
//======================================			VIEW
// Variable for Viewing
//======================================
//Variable for rotating using mouse
float xRotated = 0.0f, yRotated = 0.0f, zRotated = 0.0f;
float zoomLevel = -8.0f;
//======================================			SHAPE
// Variable to draw Sphere
float radius = 0, slices = 0, stacks = 0;
#pragma region DRAW CURVE CYLINDER VARIABLE
//variable for curve cylinder
GLfloat w0, w1, ang0, ang1, angle, x, y, xb, yb, zb;
int i, j;
int     slice = 4;
GLfloat bend_radius = 1.0f;

GLfloat bend_angle, bend_ang0, bend_ang1;
#pragma endregion
//======================================			BODY
//head
//rotating head
float headDegree = 0.0f;

//rotating jet
bool jetWeapon = false;
float jetDegree = 0.0f;

//smoke particle
float smokeTranslate = 0.0f;
bool enableSmoke = false;

float bodyAngle = 0.0f;

//Energy core variable
//reactor
double degreeReactor = 0;

#pragma region HAND PART VARIABLE
//hand
float leftShoulderAngle = 0.0f;
float rightShoulderAngle = 0.0f;
float leftUpperArmAngle = 0.0f;
float rightUpperArmAngle = 0.0f;
float leftElbowAngle = 0.0f;
float leftElbowAngle1 = 0.0f;
float rightElbowAngle = 0.0f;
float rightElbowAngle1 = 0.0f;
float punchAngle = 0.0f;

//finger rotation
float lThumbAngle = 0.0f;
float lIndexAngle = 0.0f;
float lMiddleAngle = 0.0f;
float lRingAngle = 0.0f;
float lPinkyAngle = 0.0f;

float rThumbAngle = 0.0f;
float rIndexAngle = 0.0f;
float rMiddleAngle = 0.0f;
float rRingAngle = 0.0f;
float rPinkyAngle = 0.0f;

boolean rotateLeft = false;
boolean rotateRight = false;
boolean rotateUp = false;
boolean rotateDown = false;
boolean rUp = false;
boolean punch = false;
#pragma endregion
#pragma region LEG PART VARIABLE
// leg
int chooseInteraction = 0;
// Variable for full leg --- Walking
float rightkneeAngle = 180.0f;
float leftkneeAngle = 180.0f;
float leftLegAngle = 180.0f;
float rightLegAngle = 180.0f;

bool leftFrontMax = false, rightFrontMax = false;
bool firstWalk = true, leftFrontWalked = false, rightFrontWalked = true;


float xPosition = 0.0f, yPosition = 0.0f, zPosition = 3.5f;
float zAfterMoved = 0.0;
float leftLegAxis[3][3] = { {1.0f,0.0f,0.0f},{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };
float rightLegAxis[3][3] = { { 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };

// Variable for Jumping
bool jumpMax = false;
bool firstJump = true, frontJump = false;
bool squatBeforeJump = false;
#pragma endregion
//======================================			WEAPON
#pragma region weapon
//weapon
//1. laser ball
bool laserBall = false;
float size = 0.0f;
float shootBall = 0.0f;
bool moveBackBall = false;

//gun
boolean bulletShoot = false;
boolean gunFire = false;
float gunX = 0.0f;
float gunSpin = 0.0f;
#pragma endregion
//======================================			TEXTURE
#pragma region TEXTURE 
//Texture
GLuint textureArr[5];
GLuint armorTexture, metalTexture, glassTexture, galaxyTexture, reactorTexture, flameTexture;
BITMAP BMP;
HBITMAP hBMP = NULL;
LPCSTR textureArray[2][4] = {
	{"textures/galaxy_texture.bmp", "textures/lava_texture2.bmp", "textures/blue_texture.bmp", "textures/reactor.bmp"},
	{"textures/galaxy_texture3.bmp", "textures/lava_texture.bmp", "textures/blue_texture2.bmp", "textures/reactor.bmp"}
};
int textureOption = 0;
bool textureOn = false;
GLuint texture;
#pragma endregion
//======================================			LIGHTING
#pragma region LIGHTING
//lightning
bool lightningOn = false;
GLfloat ambient[4] = { 1,1,1,1 };	//white
GLfloat diffuse[4] = { 1,1,1,1 };	//white
GLfloat specular[4] = { 1,1,1, 1 };	//white
GLfloat lightClose[4] = { 0,0,0,0 };
bool isDiffuse = true;
bool isAmbient = true;
bool isSpecular = true;
float positionX = -2.0f, positionY = 5.0f, positionZ = -0.5f;

float red[4] = { 1, 0, 0, 1 };
float blue[4] = { 0, 0, 1, 1 };
float white[4] = { 1, 1, 1, 1 };
float darkGrey[4] = { 0.1, 0.1, 0.1, 1 };
float lightGrey[4] = { 0.7, 0.7, 0.7, 1 };
float yellow[4] = { 1, 1, 0, 1 };
float grey[4] = { 0.6, 0.6, 0.6, 1 };
float orange[4] = { 1, 0.5, 0, 1 };
#pragma endregion
//======================================
bool scene1 = false;
//======================================

//perspective
bool isPerspective = true;
bool isOrtho = false;

//background
float backgroundDegree = 0;
bool onBackground = true;
#pragma endregion
GLuint loadTexture(LPCSTR filename) {

	glColor3f(1.0f, 1.0f, 1.0f);

	//Step 3 : Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4 : Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//take from step 5
	DeleteObject(hBMP);
	return texture;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		switch (wParam) {
		case MK_LBUTTON:
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			zRotated = xPos;
			xRotated = yPos;
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f;
		break;
	case WM_KEYDOWN:
	{
		switch (wParam) {
#pragma region General Utility							  
		case VK_ESCAPE:	PostQuitMessage(0);	break;
		case VK_I: zoomLevel += 1.0f;   	break;
		case VK_O: zoomLevel -= 1.0f;		break;
			//Reset the things (Not included finger)
		case VK_SPACE: {
			xRotated = 0.0f;
			yRotated = 0.0f;
			zRotated = 0.0f;
			zoomLevel = -8.0f;
			zPosition = 3.5f;
			yPosition = 0;
			//Hand
			leftShoulderAngle = 0.0f;
			leftUpperArmAngle = 0.0f;
			leftElbowAngle = 0.0f;
			leftElbowAngle1 = 0.0f;
			rightShoulderAngle = 0.0f;
			rightElbowAngle = 0.0f;
			rightElbowAngle1 = 0.0f;
			rightUpperArmAngle = 0.0f;
			punchAngle = 0.0f;
			//Leg
			rightkneeAngle = 180.0f;
			leftkneeAngle = 180.0f;
			leftLegAngle = 180.0f;
			rightLegAngle = 180.0f;
			leftFrontMax = false;
			rightFrontMax = false;
			firstWalk = true;
			leftFrontWalked = false;
			rightFrontWalked = true;
			jumpMax = false;
			firstJump = true;
			frontJump = false;
			headDegree = 0;
			//light
			positionX = -2.0f;
			positionY = 5.0f;
			positionZ = -0.5f;
		}				break;
			//Reset finger
		case VK_TAB: {
			lThumbAngle = 0.0f;
			lIndexAngle = 0.0f;
			lMiddleAngle = 0.0f;
			lRingAngle = 0.0f;
			lPinkyAngle = 0.0f;
			rThumbAngle = 0.0f;
			rIndexAngle = 0.0f;
			rMiddleAngle = 0.0f;
			rRingAngle = 0.0f;
			rPinkyAngle = 0.0f;
		}				break;
#pragma endregion				 
#pragma region Whole Body Control Movement
		case VK_W: wKeyAction();			break;		//Face Front
		case VK_A: aKeyAction();			break;		//Face Left
		case VK_S: sKeyAction();			break;		//Face Right
		case VK_D: dKeyAction();			break;		//Face Back
#pragma endregion
#pragma region Walk&Jump&Punch
		case VK_Q: qKeyAction();			break;      //Walk
		case VK_J: jKeyAction();			break;      //Jump
#pragma endregion
#pragma region RotatetheView							
		case VK_UP: {
			xRotated -= 5.0f;
		}				break;
		case VK_DOWN: {
			xRotated += 5.0f;
		}				break;
		case VK_LEFT: {
			yRotated += 5.0f;
		}				break;
		case VK_RIGHT: {
			yRotated -= 5.0f;
		}			break;
#pragma endregion
			//Jet
		case VK_NUMPAD1: {
			jetWeapon = true;
			enableSmoke = true;
		}			break;
		case VK_NUMPAD3: {
			jetWeapon = false;
			enableSmoke = false;
		}			break;
			//laser ball
		case VK_NUMPAD5: {
			laserBall = true;
		}			break;
			//gun
		case VK_K: {
			gunFire = !gunFire;
			shoot();
		} break;
#pragma region Head Control Movement
		case VK_NUMPAD7: {
			if (headDegree > -35)
				headDegree -= 2.0f;
		}			break;
		case VK_NUMPAD9: {
			if (headDegree < 35)
				headDegree += 2.0f;
		}			break;
#pragma endregion			 
#pragma region Leg Control Movement
		case VK_L: lKeyAction();			break;      //Left Leg
		case VK_R: rKeyAction();			break;      //Right Leg
#pragma endregion
#pragma region Hand Control Movement
		case VK_Z: {
			rotateLeft = true;
			rotateRight = false;
			zKeyAction();
		}					break;
		case VK_X: {
			rotateLeft = false;
			rotateRight = true;
			xKeyAction();
		}					break;
		case VK_C: {
			rotateUp = true;
			rotateDown = false;
			cKeyAction();

		}					break;
		case VK_B: {
			rotateUp = false;
			rotateDown = true;
			bKeyAction();
		}					break;
		case VK_N: {
			rotateUp = true;
			rotateDown = false;
			nKeyAction();
		}					break;
		case VK_M: {
			rotateUp = false;
			rotateDown = true;
			mKeyAction();
		}					break;
		case VK_P:
		{
			lThumbAngle = 75;
			lIndexAngle = 75;
			lMiddleAngle = 75;
			lRingAngle = 75;
			lPinkyAngle = 75;
			rThumbAngle = 75;
			rIndexAngle = 75;
			rMiddleAngle = 75;
			rRingAngle = 75;
			rPinkyAngle = 75;
			rotateUp = true;
			rotateDown = false;
			rUp = true;
			attack();
		}
#pragma endregion
#pragma region Finger Control Movement
		case VK_1: {
			rotateUp = true;
			rotateDown = false;
			lThumb();
		}					break;
		case VK_2: {
			rotateUp = true;
			rotateDown = false;
			lIndex();
		}					break;
		case VK_3: {
			rotateUp = true;
			rotateDown = false;
			lMiddle();
		}					break;
		case VK_4: {
			rotateUp = true;
			rotateDown = false;
			lRing();
		}					break;
		case VK_5: {
			rotateUp = true;
			rotateDown = false;
			lPinky();
		}					break;
		case VK_6: {
			rotateUp = true;
			rotateDown = false;
			rThumb();
		}					break;
		case VK_7: {
			rotateUp = true;
			rotateDown = false;
			rIndex();
		}					break;
		case VK_8: {
			rotateUp = true;
			rotateDown = false;
			rMiddle();
		}					break;
		case VK_9: {
			rotateUp = true;
			rotateDown = false;
			rRing();
		}					break;
		case VK_0: {
			rotateUp = true;
			rotateDown = false;
			rPinky();
		}					break;
#pragma endregion	
#pragma region Texture control
		case VK_T: {
			textureOn = !textureOn;
		}				break;
		case VK_G: {
			if (textureOn) {
				textureOption += 1;

				if (textureOption == 3) {
					textureOption = 0;
				}
			}
		}				break;
#pragma endregion	
#pragma region Lighting Control 
			// lighting on and off
		case VK_U: {
			lightningOn = !lightningOn;
		}				break;
			// lighting position
		case VK_F1: {
			positionX -= 0.5f;
		}			break;
		case VK_F2: {
			positionX += 0.5f;
		}			break;
		case VK_F3: {
			positionY -= 0.5f;
		}			break;
		case VK_F4: {
			positionY += 0.5f;
		}			break;
		case VK_F5: {
			positionZ -= 0.5f;
		}			break;
		case VK_F6: {
			positionZ += 0.5f;
		}			break;
			//Diffuse, Ambient, Specular, Perspective, Onbackground
		case VK_NUMPAD2: {
			isDiffuse = !isDiffuse;
		}			break;
		case VK_NUMPAD4: {
			isAmbient = !isAmbient;
		}			break;
		case VK_NUMPAD6: {
			isSpecular = !isSpecular;
		}			break;
		case VK_NUMPAD8: {
			isPerspective = !isPerspective;
		}			break;
		case VK_NUMPAD0: {
			onBackground = !onBackground;
		}			break;
#pragma endregion
		
		}
	default:
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}

}
//--------------------------------------------------------------------
#pragma region 3D SHAPE
void drawFootBone(float fw, float sw, float tw, float fx, float sx, float tx, float fy, float sy, float ty, float fz, float sz, float tz) {
	//Base
	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fx - sy, sx, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fy, sx, tx);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fz, sx, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fw - sy, sx, tw);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fx - sw, sz, tx - tz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fy, sz, tx - tz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sx, tx);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx - sy, sx, tx);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fz, sz + ty, tw);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fy, sz, tx - tz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sx, tx);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fz, sx - ty, tw);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw - sw, sz + ty, tw);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx - sw, sz, tx - tz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx - sy, sx, tx);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fw - sy, sx - ty, tw);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw - sw, sz + ty, tw);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fz, sz + ty, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fz, sx - ty, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fw - sy, sx - ty, tw);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Top
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw - sw, sz, tw);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx - sw, sz, tx - tz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sz, tx - tz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fz, sz, tw);
	glEnd();
}
//Diamond Shape
//Fz,sw,ty,tz will be empty
void drawFootOutlook(float fw, float sw, float tw, float fx, float sx, float tx, float fy, float sy, float ty, float fz, float sz, float tz) {
	//Back
	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	whiteMaterial();
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw, sy, tw);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, sx, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sy, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, sz, tw);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Front
	whiteMaterial();
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw, sy, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, sx, tx);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sy, tx);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, sz, tx);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//TopRight
	lightGreyMaterial();
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fx, sz, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, sz, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fy, sy, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fy, sy, tx);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//TopLeft
	lightGreyMaterial();
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fx, sz, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, sz, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fw, sy, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fw, sy, tx);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//BottomRight
	lightGreyMaterial();
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fy, sy, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fy, sy, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, sx, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, sx, tx);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//BottomLeft
	lightGreyMaterial();
	glColor3f(0.7, 0.7, 0.7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fw, sy, tx);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fw, sy, tw);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, sx, tw);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, sx, tx);
	glEnd();
}
void drawTriangleForWinge(float xValue, float yValue, float zValue, float sx, float sy, float sz, float fx, float fy, float fz) {
	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Base
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xValue, yValue, fz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, yValue, fz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, zValue);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xValue, yValue, zValue);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Front
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xValue, yValue, fz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, fz);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Right
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, yValue, fz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, zValue);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xValue, yValue, zValue);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xValue, yValue, fz);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, yValue, zValue);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xValue, yValue, zValue);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Top
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glEnd();
}
void drawTriangleWingeFB(float xValue, float yValue, float zValue, float sx, float sy, float sz, float fx, float fy, float fz) {
	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Base
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, sy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(sx, yValue, fz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, fz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, yValue, sz);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Top
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, fy, sz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, fz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(sx, yValue, fz);
	glEnd();

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_LOOP);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, sy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, fy, sz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(fx, sy, sz);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(sx, sy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(sx, fy, sz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(sx, yValue, fz);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINE_LOOP);
	//Back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(fx, fy, sz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(fx, sy, sz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(fx, yValue, fz);
	glEnd();
}
void drawSphere(float radius, float slices, float stacks) {
	GLUquadricObj* sphere = gluNewQuadric();
	glPushMatrix();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, radius, slices, stacks);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawCone(float baseRadius, float topRadius, float height, float slices, float stacks) {
	glPushMatrix();
	{
		GLUquadricObj* cone = gluNewQuadric();
		//Inside
		whiteMaterial();
		glColor3f(1, 1, 1);
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluQuadricTexture(cone, true);
		gluCylinder(cone, baseRadius, topRadius, height, slices, stacks);
		gluDeleteQuadric(cone);
	}
	glPopMatrix();
}

void drawCyclinder2(double baseR, double topR, double height, double slices, double stacks) {
	GLUquadric* cyl = NULL;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricTexture(cyl, true);
	gluCylinder(cyl, baseR, topR, height, slices, stacks);
	gluDeleteQuadric(cyl);
}
void drawCyclinder(double baseR, double topR, double height) {
	GLUquadric* cyl = NULL;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricTexture(cyl, true);
	gluCylinder(cyl, baseR, topR, height, 20, 20);
	gluDeleteQuadric(cyl);
}
void drawDisk(double innerR, double outerR) {
	GLUquadric* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_LINE);
	gluQuadricTexture(disk, true);
	gluDisk(disk, innerR, outerR, 10, 5);
	gluDeleteQuadric(disk);
}
void drawDisk2(double innerR, double outerR, double slices, double stacks) {
	GLUquadric* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_FILL);
	gluQuadricTexture(disk, true);
	gluDisk(disk, innerR, outerR, slices, stacks);
	gluDeleteQuadric(disk);
}
void gluPartialDisk(double innerR, double outerR, double startAngle, double sweepAngle) {
	GLUquadric* parDisk = NULL;
	parDisk = gluNewQuadric();
	gluQuadricDrawStyle(parDisk, GLU_FILL);
	gluPartialDisk(parDisk, innerR, outerR, 100, 100, startAngle, sweepAngle);
	gluDeleteQuadric(parDisk);
}

void drawTexturedQuads(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4) {
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x2, y2, z2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, y3, z3);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x4, y4, z4);
	}
	glEnd();
}
void drawTexturedTriangles(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x2, y2, z2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, y3, z3);
	}
	glEnd();
}
#pragma endregion
//--------------------------------------------------------------------
#pragma region Control Movement
//-------------------------
//Leg
void wKeyAction() {
	bodyAngle = 0.0f;
}
void aKeyAction() {
	bodyAngle = 90.0f;
}
void sKeyAction() {
	bodyAngle = 180.0f;
}
void dKeyAction() {
	bodyAngle = 270.0f;
}
//Walk
void qKeyAction() {
	glPushMatrix();
	{
		if (!leftFrontWalked) {
			if (firstWalk) {
				rightShoulderAngle -= 0.6f;
				//rightElbowAngle -= 3.0f;
			}
			else {
				rightShoulderAngle -= 0.6f;
				//rightElbowAngle -= 3.0f;
				leftShoulderAngle += 0.6f;
				//leftElbowAngle += 3.0f;
			}

			if (!leftFrontMax && leftLegAngle >= 140.0f && leftkneeAngle <= 250.0f) {
				leftLegAngle -= 2.0f;
				leftkneeAngle += 2.5f;
			}
			else {
				leftFrontMax = true;
			}
			if (leftFrontMax) {
				if (leftkneeAngle >= 220.0f) {
					leftkneeAngle -= 2.0f;
				}

				if (leftkneeAngle < 220.0f && leftLegAngle <= 180.0f) {
					leftLegAngle += 2.0f;
					leftkneeAngle -= 2.0f;
					zPosition += 0.01f;
				}

			}
			if (leftLegAngle == 180.0f) {
				firstWalk = false;
				leftFrontMax = false;
				leftFrontWalked = true;
			}
		}
		else {
			rightShoulderAngle += 0.6f;
			//rightElbowAngle += 3.0f;
			leftShoulderAngle -= 0.6f;
			//rightElbowAngle -= 3.0f;
			if (!rightFrontMax && rightLegAngle >= 140.0f && rightkneeAngle <= 250.0f) {
				rightLegAngle -= 2.0f;
				rightkneeAngle += 2.5f;
			}
			else {
				rightFrontMax = true;
			}
			if (rightFrontMax) {
				if (rightkneeAngle >= 220.0f)
					rightkneeAngle -= 2.0f;

				if (rightkneeAngle < 220.0f && rightLegAngle <= 180.0f) {
					rightLegAngle += 2.0f;
					rightkneeAngle -= 2.0f;
					zPosition += 0.01f;
				}

			}
			if (rightLegAngle == 180.0f) {
				rightFrontMax = false;
				leftFrontWalked = false;
				rightFrontWalked = true;
			}
		}
	}
	glPopMatrix();
}
//Jump
void jKeyAction() {
	glPushMatrix();
	{
		if (!frontJump) {
			if (firstJump) {
				lThumbAngle += 2.0f;
				lIndexAngle += 2.0f;
				lMiddleAngle += 2.0f;
				lRingAngle += 2.0f;
				lPinkyAngle += 2.0f;
				rThumbAngle += 2.0f;
				rIndexAngle += 2.0f;
				rMiddleAngle += 2.0f;
				rRingAngle += 2.0f;
				rPinkyAngle += 2.0f;
			}
			else {
				//rightArmAngle1 -= 0.2f;
				//rightArmAngle2 -= 0.3f;
				//leftArmAngle1 += 0.2f;
				//leftArmAngle2 += 0.3f;
			}
			if (!jumpMax && leftLegAngle >= 180.0f && leftkneeAngle <= 250.0f) {
				leftkneeAngle += 3.0f;
				rightkneeAngle += 3.0f;
				yPosition -= 0.07f;
			}
			else {
				jumpMax = true;
			}
			if (jumpMax) {
				lThumbAngle = 0.0f;
				lIndexAngle = 0.0f;
				lMiddleAngle = 0.0f;
				lRingAngle = 0.0f;
				lPinkyAngle = 0.0f;
				rThumbAngle = 0.0f;
				rIndexAngle = 0.0f;
				rMiddleAngle = 0.0f;
				rRingAngle = 0.0f;
				rPinkyAngle = 0.0f;
				if (leftkneeAngle >= 220.0f) {
					leftkneeAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
				}

				if (leftkneeAngle < 220.0f && leftLegAngle <= 180.0f) {
					leftkneeAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
					yPosition += 0.08f;

				}
			}
			if (leftkneeAngle == 180.0f && rightkneeAngle == 180.0f) {
				firstJump = false;
				jumpMax = false;
				frontJump = true;
			}
		}
		else {
			lThumbAngle += 2.0f;
			lIndexAngle += 2.0f;
			lMiddleAngle += 2.0f;
			lRingAngle += 2.0f;
			lPinkyAngle += 2.0f;
			rThumbAngle += 2.0f;
			rIndexAngle += 2.0f;
			rMiddleAngle += 2.0f;
			rRingAngle += 2.0f;
			rPinkyAngle += 2.0f;
			if (!jumpMax && rightLegAngle >= 180.0f && rightkneeAngle <= 250.0f) {
				//leftLegAngle -= 2.0f;
				leftkneeAngle += 3.0f;
				rightkneeAngle += 3.0f;
				yPosition -= 0.07f;

			}
			else {
				jumpMax = true;
			}
			if (jumpMax) {
				lThumbAngle = 0.0f;
				lIndexAngle = 0.0f;
				lMiddleAngle = 0.0f;
				lRingAngle = 0.0f;
				lPinkyAngle = 0.0f;
				rThumbAngle = 0.0f;
				rIndexAngle = 0.0f;
				rMiddleAngle = 0.0f;
				rRingAngle = 0.0f;
				rPinkyAngle = 0.0f;
				if (leftkneeAngle >= 220.0f) {
					leftkneeAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
				}

				if (rightkneeAngle < 220.0f && rightLegAngle <= 180.0f) {
					leftkneeAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
					yPosition += 0.08f;
				}
			}
			if (rightkneeAngle == 180.0f && leftkneeAngle == 180.0f) {
				firstJump = false;
				jumpMax = false;
				frontJump = true;
			}
		}
	}
	glPopMatrix();
}
void vKeyAction() {
	glPushMatrix();
	{
		if (!frontJump) {
			if (firstJump) {
				lThumbAngle += 2.0f;
				lIndexAngle += 2.0f;
				lMiddleAngle += 2.0f;
				lRingAngle += 2.0f;
				lPinkyAngle += 2.0f;
				rThumbAngle += 2.0f;
				rIndexAngle += 2.0f;
				rMiddleAngle += 2.0f;
				rRingAngle += 2.0f;
				rPinkyAngle += 2.0f;
			}
			else {
				//rightArmAngle1 -= 0.2f;
				//rightArmAngle2 -= 0.3f;
				//leftArmAngle1 += 0.2f;
				//leftArmAngle2 += 0.3f;
			}
			if (!jumpMax && leftLegAngle >= 180.0f && leftkneeAngle <= 250.0f) {
				leftLegAngle += 2.0f;
				leftkneeAngle += 3.0f;
				yPosition -= 0.07f;
			}
			else {
				jumpMax = true;
			}
			if (jumpMax) {
				lThumbAngle = 0.0f;
				lIndexAngle = 0.0f;
				lMiddleAngle = 0.0f;
				lRingAngle = 0.0f;
				lPinkyAngle = 0.0f;
				rThumbAngle = 0.0f;
				rIndexAngle = 0.0f;
				rMiddleAngle = 0.0f;
				rRingAngle = 0.0f;
				rPinkyAngle = 0.0f;
				if (leftkneeAngle >= 220.0f) {
					leftkneeAngle -= 2.0f;
				}

				if (leftkneeAngle < 220.0f && leftLegAngle <= 180.0f) {
					leftkneeAngle -= 2.0f;
					leftLegAngle -= 2.0f;
					yPosition += 0.08f;

				}
			}
			if (leftkneeAngle == 180.0f && rightkneeAngle == 180.0f) {
				firstJump = false;
				jumpMax = false;
				frontJump = true;
			}
		}
		else {
			lThumbAngle += 2.0f;
			lIndexAngle += 2.0f;
			lMiddleAngle += 2.0f;
			lRingAngle += 2.0f;
			lPinkyAngle += 2.0f;
			rThumbAngle += 2.0f;
			rIndexAngle += 2.0f;
			rMiddleAngle += 2.0f;
			rRingAngle += 2.0f;
			rPinkyAngle += 2.0f;
			if (!jumpMax && rightLegAngle >= 180.0f && rightkneeAngle <= 250.0f) {
				//leftLegAngle -= 2.0f;
				rightLegAngle += 2.0f;
				rightkneeAngle += 3.0f;
				yPosition -= 0.07f;

			}
			else {
				jumpMax = true;
			}
			if (jumpMax) {
				lThumbAngle = 0.0f;
				lIndexAngle = 0.0f;
				lMiddleAngle = 0.0f;
				lRingAngle = 0.0f;
				lPinkyAngle = 0.0f;
				rThumbAngle = 0.0f;
				rIndexAngle = 0.0f;
				rMiddleAngle = 0.0f;
				rRingAngle = 0.0f;
				rPinkyAngle = 0.0f;
				if (leftkneeAngle >= 220.0f) {
					rightLegAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
				}

				if (rightkneeAngle < 220.0f && rightLegAngle <= 180.0f) {
					rightLegAngle -= 2.0f;
					rightkneeAngle -= 2.0f;
					yPosition += 0.08f;
				}
			}
			if (rightkneeAngle == 180.0f && leftkneeAngle == 180.0f) {
				firstJump = false;
				jumpMax = false;
				frontJump = true;
			}
		}
	}
	glPopMatrix();
}
//Left Leg Move
void lKeyAction() {
	glPushMatrix(); {
		if (!leftFrontMax && leftLegAngle >= 140.0f && leftkneeAngle <= 250.0f) {
			leftLegAngle -= 2.0f;
			leftkneeAngle += 3.0f;
		}
		else {
			leftFrontMax = true;
		}
		if (leftFrontMax) {
			if (leftkneeAngle >= 220.0f) {
				leftkneeAngle -= 2.0f;
			}

			if (leftkneeAngle < 220.0f && leftLegAngle <= 180.0f) {
				leftLegAngle += 2.0f;
				leftkneeAngle -= 2.0f;
			}

		}
		if (leftLegAngle == 180.0f) {
			firstWalk = false;
			leftFrontMax = false;
			leftFrontWalked = true;
		}
	}
	glPopMatrix();
}
//Right Leg Move
void rKeyAction() {
	glPushMatrix();
	{
		if (!rightFrontMax && rightLegAngle >= 140.0f && rightkneeAngle <= 250.0f) {
			rightLegAngle -= 2.0f;
			rightkneeAngle += 3.0f;
		}
		else {
			rightFrontMax = true;
		}
		if (rightFrontMax) {
			if (rightkneeAngle >= 220.0f) {
				rightkneeAngle -= 2.0f;
			}

			if (rightkneeAngle < 220.0f && rightLegAngle <= 180.0f) {
				rightLegAngle += 2.0f;
				rightkneeAngle -= 2.0f;
			}

		}
		if (rightLegAngle == 180.0f) {
			firstWalk = false;
			rightFrontMax = false;
			rightFrontWalked = true;
		}
	}
	glPopMatrix();
}
//--------------------------
//Hand
void zKeyAction() { //rotate left

	if (rotateLeft && leftElbowAngle < 90 && rightElbowAngle < 90) {
		leftElbowAngle += 2.5;
		rightElbowAngle += 2.5;
	}
	else {
		rotateLeft = false;
	}

}
void xKeyAction() { // rotate right

	if (rotateRight && leftElbowAngle > -90 && rightElbowAngle > -90) {
		//rotateUp = false;
		leftElbowAngle -= 2.5;
		rightElbowAngle -= 2.5;
	}
	else {
		rotateRight = false;
	}
}
void cKeyAction() { // arm rotate down
	if (rotateUp && leftShoulderAngle < 0) {
		//rotateUp = false;
		leftShoulderAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void bKeyAction() {//arm rotate up 
	if (rotateDown && leftShoulderAngle > -180) {
		//rotateUp = false;
		leftShoulderAngle -= 5;
	}
	else {
		rotateDown = false;
	}
}
void nKeyAction() { // arm rotate down
	if (rotateUp && rightShoulderAngle < 0) {
		//rotateUp = false;
		rightShoulderAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void mKeyAction() {//arm rotate up 
	if (rotateDown && rightShoulderAngle > -180) {
		//rotateUp = false;
		rightShoulderAngle -= 5;
	}
	else {
		rotateDown = false;
	}
}
void lThumb() {
	if (rotateUp && lIndexAngle < 80) {
		//rotateUp = false;
		lIndexAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void lIndex() {
	if (rotateUp && lMiddleAngle < 80) {
		//rotateUp = false;
		lMiddleAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void lMiddle() {
	if (rotateUp && lRingAngle < 80) {
		//rotateUp = false;
		lRingAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void lRing() {
	if (rotateUp && lThumbAngle < 80) {
		//rotateUp = false;
		lThumbAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void lPinky() {
	if (rotateUp && lPinkyAngle < 80) {
		//rotateUp = false;
		lPinkyAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void rThumb() {
	if (rotateUp && rThumbAngle < 80) {
		//rotateUp = false;
		rThumbAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void rIndex() {
	if (rotateUp && rIndexAngle < 80) {
		//rotateUp = false;
		rIndexAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void rMiddle() {
	if (rotateUp && rMiddleAngle < 80) {
		//rotateUp = false;
		rMiddleAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void rRing() {
	if (rotateUp && rRingAngle < 80) {
		//rotateUp = false;
		rRingAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void rPinky() {
	if (rotateUp && rPinkyAngle < 80) {
		//rotateUp = false;
		rPinkyAngle += 5;
	}
	else {
		rotateUp = false;
	}
}
void attack() {
	if (rotateUp && leftElbowAngle1 > -110 && leftUpperArmAngle > -40) {
		leftElbowAngle1 -= 15;
		leftUpperArmAngle -= 5;
		punch = true;
		rightShoulderAngle += 5;
		rightElbowAngle1 += 13;
	}
	else {
		rotateUp = false;

	}

	if (punch == true && rightElbowAngle1 > 15) {
		rightShoulderAngle -= 10;
		if (punch == true && rightShoulderAngle < -40) {
			rightElbowAngle1 -= 25;




		}
	}
}
void shoot() {
	if (gunFire) {
		lThumbAngle = 75;
		lIndexAngle = 75;
		lMiddleAngle = 75;
		lRingAngle = 75;
		lPinkyAngle = 75;
		leftShoulderAngle = -90;
		leftElbowAngle = -90;
	}


}
#pragma endregion
//-------------------------------------------------------------------
//Draw the whole machine
#pragma region HEAD
void head() {

	yellowMaterial();

	//eye glass pane
	glColor3f(1, 1, 1);
	if (textureOn) {
		glassTexture = loadTexture("textures/glass_texture.bmp");
	}
	drawTexturedQuads(0.075, 0.93, -0.0, 0, 0.90, -0.08, 0, 0.75, -0.08, 0.075, 0.75, -0.02);//right
	drawTexturedQuads(-0.075, 0.93, -0.0, -0, 0.90, -0.08, -0, 0.75, -0.08, -0.075, 0.75, -0.02);//left
	glDeleteTextures(1, &glassTexture);

	redMaterial();

	//head deco
	if (textureOn) {
		galaxyTexture = loadTexture("textures/head_texture.bmp");
	}
	drawTexturedQuads(0.01, 1.02, 0.02, 0.01, 1.05, -0.03, 0.01, 0.98, -0.075, 0.01, 0.95, -0.075);	//right
	drawTexturedQuads(-0.01, 1.02, 0.02, -0.01, 1.05, -0.03, -0.01, 0.98, -0.075, -0.01, 0.95, -0.075);	//left
	drawTexturedQuads(0.01, 1.02, 0.02, 0.01, 1.05, -0.03, -0.01, 1.05, -0.03, -0.01, 1.02, 0.02);		//top
	drawTexturedQuads(0.01, 0.98, -0.075, 0.01, 0.95, -0.075, -0.01, 0.95, -0.075, -0.01, 0.98, -0.075);	//btm
	drawTexturedQuads(0.01, 1.05, -0.03, 0.01, 0.98, -0.075, -0.01, 0.98, -0.075, -0.01, 1.05, -0.03);	//front
	drawTexturedQuads(0.01, 1.02, 0.02, 0.01, 0.95, -0.075, -0.01, 0.95, -0.075, -0.01, 1.02, 0.02);	//back
	glDeleteTextures(1, &galaxyTexture);

	blackMaterial();

	//near brain
	glColor3f(0.4, 0.4, 0.4);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	glPushMatrix();
	{
		glTranslatef(0, 0.94, -0.01);
		drawSphere(0.06,50,50);
	}
	glPopMatrix();
	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	//triangle near nose 
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	drawTexturedTriangles(0.03, 0.8, -0.08, -0.03, 0.8, -0.08, 0.0, 0.85, -0.08);//front piece
	drawTexturedTriangles(0.03, 0.8, -0.09, -0.03, 0.8, -0.09, 0.0, 0.85, -0.09);//front piece
	drawTexturedQuads(0.03, 0.8, -0.08, 0.03, 0.8, -0.09, 0.0, 0.85, -0.08, 0.0, 0.85, -0.09);	//front piece
	drawTexturedQuads(-0.03, 0.8, -0.08, -0.03, 0.8, -0.09, 0.0, 0.85, -0.08, 0.0, 0.85, -0.09);

	//square below triangle
	drawTexturedQuads(0.035, 0.8, -0.092, -0.035, 0.8, -0.092, -0.035, 0.75, -0.092, 0.035, 0.75, -0.092);	//front
	drawTexturedQuads(0.035, 0.8, -0.075, -0.035, 0.8, -0.075, -0.035, 0.75, -0.075, 0.03, 0.75, -0.075);	//back
	drawTexturedQuads(0.035, 0.8, -0.092, -0.035, 0.8, -0.092, -0.035, 0.8, -0.075, 0.035, 0.8, -0.075);	//top
	drawTexturedQuads(-0.035, 0.75, -0.092, 0.035, 0.75, -0.092, 0.03, 0.75, -0.075, -0.035, 0.75, -0.075);	//btm
	drawTexturedQuads(-0.035, 0.8, -0.092, -0.035, 0.75, -0.092, -0.035, 0.75, -0.075, -0.035, 0.8, -0.075);	//left
	drawTexturedQuads(0.035, 0.8, -0.092, 0.035, 0.75, -0.092, 0.03, 0.75, -0.075, 0.035, 0.8, -0.075);

	//square at right cheek
	drawTexturedQuads(0.03, 0.8, -0.08, 0.07, 0.88, -0.02, 0.078, 0.83, -0.02, 0.038, 0.75, -0.08);	//right
	drawTexturedQuads(0.04, 0.8, -0.08, 0.08, 0.88, -0.02, 0.088, 0.83, -0.02, 0.048, 0.75, -0.08);	//left
	drawTexturedQuads(0.03, 0.8, -0.08, 0.04, 0.8, -0.08, 0.08, 0.88, -0.02, 0.07, 0.88, -0.02);	//front
	drawTexturedQuads(0.078, 0.83, -0.02, 0.038, 0.75, -0.08, 0.048, 0.75, -0.08, 0.088, 0.83, -0.02);	//bottom
	drawTexturedQuads(0.04, 0.8, -0.08, 0.03, 0.8, -0.08, 0.038, 0.75, -0.08, 0.048, 0.75, -0.08);	//front
	drawTexturedQuads(0.08, 0.88, -0.02, 0.07, 0.88, -0.02, 0.078, 0.83, -0.02, 0.088, 0.83, -0.02);	//back

	//square at left cheek
	drawTexturedQuads(-0.03, 0.8, -0.08, -0.07, 0.88, -0.02, -0.078, 0.83, -0.02, -0.038, 0.75, -0.08);	//right
	drawTexturedQuads(-0.04, 0.8, -0.08, -0.08, 0.88, -0.02, -0.088, 0.83, -0.02, -0.048, 0.75, -0.08);	//left
	drawTexturedQuads(-0.03, 0.8, -0.08, -0.04, 0.8, -0.08, -0.08, 0.88, -0.02, -0.07, 0.88, -0.02);	//top
	drawTexturedQuads(-0.078, 0.83, -0.02, -0.038, 0.75, -0.08, -0.048, 0.75, -0.08, -0.088, 0.83, -0.02);	//btm
	drawTexturedQuads(-0.04, 0.8, -0.08, -0.03, 0.8, -0.08, -0.038, 0.75, -0.08, -0.048, 0.75, -0.08);	//front
	drawTexturedQuads(-0.08, 0.88, -0.02, -0.07, 0.88, -0.02, -0.078, 0.83, -0.02, -0.088, 0.83, -0.02);	//back

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	greyMaterial();
	glColor3f(0.3, 0.3, 0.3);
	//cylinder left hs
	if (textureOn) {
		armorTexture = loadTexture("textures/armor_texture.bmp");
	}

	glPushMatrix();
	{
		glTranslatef(0, 0.90, -0.1);
		glRotatef(-38, 1, 0, 0);

		glPushMatrix();
		{
			glRotatef(40, 0, 1, 0);
			drawCyclinder(0.008, 0.008, 0.1);
		}
		glPopMatrix();
	}

	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, 0.88, -0.1);
		glRotatef(-38, 1, 0, 0);
		glPushMatrix();
		{
			glRotatef(40, 0, 1, 0);
			drawCyclinder(0.008, 0.008, 0.1);

		}
		glPopMatrix();
	}
	glPopMatrix();

	//right hs
	glPushMatrix();
	{
		glTranslatef(0, 0.90, -0.1);
		glRotatef(-38, 1, 0, 0);
		glPushMatrix();
		{
			glRotatef(-40, 0, 1, 0);
			drawCyclinder(0.008, 0.008, 0.1);
		}
		glPopMatrix();

	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0, 0.88, -0.1);
		glRotatef(-38, 1, 0, 0);
		glPushMatrix();
		{
			glRotatef(-40, 0, 1, 0);
			drawCyclinder(0.008, 0.008, 0.1);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);
}

void neck() {

	blackMaterial();

	glColor3f(0.3, 0.3, 0.3);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	//left cheek & neck
	drawTexturedQuads(-0.09, 0.85, 0.04, -0.05, 0.77, -0.08, -0.09, 0.74, -0.08, -0.13, 0.82, 0.04);	//top
	drawTexturedQuads(-0.09, 0.83, 0.04, -0.05, 0.75, -0.08, -0.09, 0.72, -0.08, -0.13, 0.8, 0.04);	//btm
	drawTexturedQuads(-0.09, 0.85, 0.04, -0.05, 0.77, -0.08, -0.05, 0.75, -0.08, -0.09, 0.83, 0.04);	//left
	drawTexturedQuads(-0.09, 0.74, -0.08, -0.13, 0.82, 0.04, -0.13, 0.8, 0.04, -0.09, 0.72, -0.08);	//right
	drawTexturedQuads(-0.05, 0.77, -0.08, -0.09, 0.74, -0.08, -0.09, 0.72, -0.08, -0.05, 0.75, -0.08);	//front
	drawTexturedQuads(-0.09, 0.85, 0.04, -0.13, 0.82, 0.04, -0.13, 0.8, 0.04, -0.09, 0.83, 0.04);	//back

	//right cheek & neck
	drawTexturedQuads(0.09, 0.85, 0.04, 0.05, 0.77, -0.08, 0.09, 0.74, -0.08, 0.13, 0.82, 0.04);	//top
	drawTexturedQuads(0.09, 0.83, 0.04, 0.05, 0.75, -0.08, 0.09, 0.72, -0.08, 0.13, 0.8, 0.04);	//btm
	drawTexturedQuads(0.09, 0.85, 0.04, 0.05, 0.77, -0.08, 0.05, 0.75, -0.08, 0.09, 0.83, 0.04);	//left
	drawTexturedQuads(0.09, 0.74, -0.08, 0.13, 0.82, 0.04, 0.13, 0.8, 0.04, 0.09, 0.72, -0.08);	//right
	drawTexturedQuads(0.05, 0.77, -0.08, 0.09, 0.74, -0.08, 0.09, 0.72, -0.08, 0.05, 0.75, -0.08);	//front
	drawTexturedQuads(0.09, 0.85, 0.04, 0.13, 0.82, 0.04, 0.13, 0.8, 0.04, 0.09, 0.83, 0.04);	//back

	//square at right ear
	drawTexturedQuads(0.075, 0.93, -0.03, 0.085, 0.98, 0.0, 0.095, 0.85, 0.02, 0.08, 0.8, -0.01);//left
	drawTexturedQuads(0.065, 0.93, -0.03, 0.075, 0.98, 0.01, 0.085, 0.85, 0.02, 0.07, 0.8, -0.01);//right
	drawTexturedQuads(0.075, 0.93, -0.03, 0.085, 0.9, 0.01, 0.075, 0.98, 0.01, 0.065, 0.93, -0.03);//top
	drawTexturedQuads(0.095, 0.85, 0.02, 0.08, 0.8, -0.01, 0.07, 0.8, -0.01, 0.085, 0.85, 0.02);//bottom
	drawTexturedQuads(0.075, 0.93, -0.03, 0.08, 0.8, -0.01, 0.07, 0.8, -0.01, 0.065, 0.93, -0.03);//front
	drawTexturedQuads(0.085, 0.98, 0.02, 0.095, 0.85, 0.01, 0.085, 0.85, 0.02, 0.075, 0.98, 0.01);//back

	//square at left ear
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.085, 0.98, 0.01, -0.095, 0.85, 0.02, -0.08, 0.8, -0.01);	//left
	drawTexturedQuads(-0.065, 0.93, -0.03, -0.075, 0.98, 0.01, -0.085, 0.85, 0.02, -0.07, 0.8, -0.01);//right
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.085, 0.98, 0.01, -0.075, 0.98, 0.01, -0.065, 0.9, -0.03);//top
	drawTexturedQuads(-0.095, 0.85, 0.02, -0.08, 0.8, -0.01, -0.07, 0.80, -0.01, -0.085, 0.85, 0.02);//bottom
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.08, 0.8, -0.01, -0.07, 0.80, -0.01, -0.065, 0.93, -0.03);//front
	drawTexturedQuads(-0.085, 0.98, 0.02, -0.095, 0.85, 0.01, -0.085, 0.85, 0.02, -0.075, 0.98, 0.01);//back

	//behind ear
	drawTexturedQuads(0.09, 1, 0.0, -0.09, 1, 0.0, -0.09, 0.85, 0.03, 0.09, 0.85, 0.03);//front
	drawTexturedQuads(0.09, 1.01, 0.035, -0.09, 1.01, 0.035, -0.09, 0.86, 0.075, 0.09, 0.86, 0.075);	//back
	drawTexturedQuads(0.09, 1.01, 0.035, -0.09, 1.01, 0.035, -0.09, 1, 0.0, 0.09, 1, 0.0);	//top
	drawTexturedQuads(-0.09, 0.85, 0.03, 0.09, 0.85, 0.03, 0.09, 0.86, 0.075, -0.09, 0.86, 0.075);//btm
	drawTexturedQuads(-0.09, 1, 0.0, -0.09, 0.85, 0.03, -0.09, 0.86, 0.075, -0.09, 1.01, 0.035);//left
	drawTexturedQuads(0.09, 1, 0.0, 0.09, 0.85, 0.03, 0.09, 0.86, 0.075, 0.09, 1.01, 0.035);//right

	//square at right ear
	drawTexturedQuads(0.075, 0.93, -0.03, 0.085, 0.98, 0.0, 0.095, 0.85, 0.02, 0.08, 0.8, -0.01);//left
	drawTexturedQuads(0.065, 0.93, -0.03, 0.075, 0.98, 0.01, 0.085, 0.85, 0.02, 0.07, 0.8, -0.01);//right
	drawTexturedQuads(0.075, 0.93, -0.03, 0.085, 0.9, 0.01, 0.075, 0.98, 0.01, 0.065, 0.93, -0.03);//top
	drawTexturedQuads(0.095, 0.85, 0.02, 0.08, 0.8, -0.01, 0.07, 0.8, -0.01, 0.085, 0.85, 0.02);//bottom
	drawTexturedQuads(0.075, 0.93, -0.03, 0.08, 0.8, -0.01, 0.07, 0.8, -0.01, 0.065, 0.93, -0.03);//front
	drawTexturedQuads(0.085, 0.98, 0.02, 0.095, 0.85, 0.01, 0.085, 0.85, 0.02, 0.075, 0.98, 0.01);//back

	//square at left ear
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.085, 0.98, 0.01, -0.095, 0.85, 0.02, -0.08, 0.8, -0.01);	//left
	drawTexturedQuads(-0.065, 0.93, -0.03, -0.075, 0.98, 0.01, -0.085, 0.85, 0.02, -0.07, 0.8, -0.01);//right
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.085, 0.98, 0.01, -0.075, 0.98, 0.01, -0.065, 0.9, -0.03);//top
	drawTexturedQuads(-0.095, 0.85, 0.02, -0.08, 0.8, -0.01, -0.07, 0.80, -0.01, -0.085, 0.85, 0.02);//bottom
	drawTexturedQuads(-0.075, 0.93, -0.03, -0.08, 0.8, -0.01, -0.07, 0.80, -0.01, -0.065, 0.93, -0.03);//front
	drawTexturedQuads(-0.085, 0.98, 0.02, -0.095, 0.85, 0.01, -0.085, 0.85, 0.02, -0.075, 0.98, 0.01);//back

	//behind ear
	drawTexturedQuads(0.09, 1, 0.0, -0.09, 1, 0.0, -0.09, 0.85, 0.03, 0.09, 0.85, 0.03);//front
	drawTexturedQuads(0.09, 1.01, 0.035, -0.09, 1.01, 0.035, -0.09, 0.86, 0.075, 0.09, 0.86, 0.075);	//back
	drawTexturedQuads(0.09, 1.01, 0.035, -0.09, 1.01, 0.035, -0.09, 1, 0.0, 0.09, 1, 0.0);	//top
	drawTexturedQuads(-0.09, 0.85, 0.03, 0.09, 0.85, 0.03, 0.09, 0.86, 0.075, -0.09, 0.86, 0.075);//btm
	drawTexturedQuads(-0.09, 1, 0.0, -0.09, 0.85, 0.03, -0.09, 0.86, 0.075, -0.09, 1.01, 0.035);//left
	drawTexturedQuads(0.09, 1, 0.0, 0.09, 0.85, 0.03, 0.09, 0.86, 0.075, 0.09, 1.01, 0.035);//right

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	//support the head 
	if (textureOn) {
		armorTexture = loadTexture("textures/armor_texture.bmp");
	}
	drawTexturedQuads(-0.09, 0.84, 0.065, 0.09, 0.84, 0.065, 0.09, 0.75, -0.02, -0.09, 0.75, -0.02);	//top
	drawTexturedQuads(-0.09, 0.80, 0.08, 0.09, 0.80, 0.08, 0.09, 0.7, 0.03, -0.09, 0.7, 0.03);	//btm
	drawTexturedQuads(-0.09, 0.84, 0.065, 0.09, 0.84, 0.065, 0.09, 0.80, 0.08, -0.09, 0.80, 0.08);	//back
	drawTexturedQuads(0.09, 0.75, -0.02, -0.09, 0.75, -0.02, -0.09, 0.70, 0.03, 0.09, 0.70, 0.03);	//front
	drawTexturedQuads(-0.09, 0.84, 0.065, -0.09, 0.75, -0.02, -0.09, 0.70, 0.03, -0.09, 0.80, 0.08);	//left
	drawTexturedQuads(0.09, 0.84, 0.065, 0.09, 0.75, -0.02, 0.09, 0.70, 0.03, 0.09, 0.8, 0.08);	//right

	//support again
	drawTexturedQuads(-0.07, 0.8, 0.08, 0.07, 0.8, 0.08, 0.12, 0.67, 0.15, -0.12, 0.67, 0.15);//front
	drawTexturedQuads(-0.07, 0.8, 0.06, 0.07, 0.8, 0.06, 0.12, 0.67, 0.13, -0.12, 0.67, 0.13);//back
	drawTexturedQuads(-0.07, 0.8, 0.08, 0.07, 0.8, 0.08, 0.07, 0.8, 0.06, -0.07, 0.8, 0.06);	//top
	drawTexturedQuads(0.12, 0.67, 0.15, -0.12, 0.67, 0.15, -0.12, 0.67, 0.13, 0.12, 0.67, 0.13); // btm
	drawTexturedQuads(-0.07, 0.8, 0.08, -0.12, 0.67, 0.15, -0.12, 0.67, 0.13, -0.07, 0.8, 0.06);	//left
	drawTexturedQuads(0.07, 0.8, 0.08, 0.12, 0.67, 0.15, 0.12, 0.67, 0.13, 0.07, 0.8, 0.06);	//right

	//beside support again - left
	drawTexturedQuads(-0.12, 0.8, 0.05, -0.07, 0.8, 0.09, -0.12, 0.68, 0.16, -0.17, 0.68, 0.12);//front
	drawTexturedQuads(-0.12, 0.8, 0.03, -0.07, 0.8, 0.07, -0.12, 0.68, 0.14, -0.17, 0.68, 0.10);//back
	drawTexturedQuads(-0.12, 0.8, 0.05, -0.07, 0.8, 0.09, -0.07, 0.8, 0.07, -0.12, 0.8, 0.03);	//top
	drawTexturedQuads(-0.12, 0.68, 0.16, -0.17, 0.68, 0.12, -0.17, 0.68, 0.10, -0.12, 0.68, 0.14);//btm
	drawTexturedQuads(-0.12, 0.8, 0.05, -0.17, 0.68, 0.12, -0.17, 0.68, 0.10, -0.12, 0.8, 0.03);//left
	drawTexturedQuads(-0.07, 0.8, 0.09, -0.12, 0.68, 0.16, -0.12, 0.68, 0.14, -0.07, 0.8, 0.07);	//right

	//beside support again - right
	drawTexturedQuads(0.12, 0.8, 0.05, 0.07, 0.8, 0.09, 0.12, 0.68, 0.16, 0.17, 0.68, 0.12);	//front
	drawTexturedQuads(0.12, 0.8, 0.03, 0.07, 0.8, 0.07, 0.12, 0.68, 0.14, 0.17, 0.68, 0.10);	//back
	drawTexturedQuads(0.12, 0.8, 0.05, 0.07, 0.8, 0.09, 0.07, 0.8, 0.07, 0.12, 0.8, 0.03);		//top
	drawTexturedQuads(0.12, 0.68, 0.16, 0.17, 0.68, 0.12, 0.17, 0.68, 0.10, 0.12, 0.68, 0.14);	//btm
	drawTexturedQuads(0.12, 0.8, 0.05, 0.17, 0.68, 0.12, 0.17, 0.68, 0.10, 0.12, 0.8, 0.03);	//left
	drawTexturedQuads(0.07, 0.8, 0.09, 0.12, 0.68, 0.16, 0.12, 0.68, 0.14, 0.07, 0.8, 0.07);	//right
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);
}
#pragma endregion
#pragma region LEG
// Done
void waist() {
	glPushMatrix();
	{
		/*glTranslatef(0.3,0,0);*/

		glPushMatrix();
		{
			glTranslatef(0.7, 0, 0);
			glRotatef(-90, 0, 0, 1);
			blackMaterial();
			glColor3f(0, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawTriangleForWinge(-0.2, -0.2, -0.2, 0, 0, 0, 0.2, 0.1, 0.2);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.4, 0, 0);
			blackMaterial();
			glColor3f(0, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawFootBone(-0.4, 0, -0.2, -0.4, 0, 0.2, 0.9, 0, 0, 0.9, 0.2, 0);
			glDeleteTextures(1, &galaxyTexture);

		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1, 0, 0);
			glRotatef(-90, 0, 0, -1);
			blackMaterial();
			glColor3f(0, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawTriangleForWinge(-0.2, -0.2, -0.2, 0, 0, 0, 0.2, 0.1, 0.2);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.6, -0.20, 0.202);
			blackMaterial();
			glColor3f(0, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawTriangleWingeFB(0.1, 0.2, 0.2, -0.3, 0, 0, 1.2, 0.4, 0.3);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotatef(180, 1, 0, 0);
			glTranslatef(-0.6, -0.2, 0.202);
			blackMaterial();
			glColor3f(0, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawTriangleWingeFB(0.1, 0.2, 0.2, -0.3, 0, 0, 1.2, 0.4, 0.3);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
// Modifying
void thighBone() { // big leg
	glPushMatrix();
	{
		glPushMatrix();
		{
			greyMaterial();
			glColor3f(0.4, 0.4, 0.4);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(-0.1, 0, 0.2, -0.1, -0.3, 0.4, 0.3, 0, 0, 0.3, 0.2, 0);
			glDeleteTextures(1, &armorTexture);
		}//0.1, -0.3, 0.3

		glPopMatrix();
		glPushMatrix();
		{
			greyMaterial();
			glColor3f(0.4, 0.4, 0.4);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(-0.1, 0, 0.2, -0.1, 0.2, 0.4, 0.3, 0, 0, 0.3, 0.8, 0);
			glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();

	}
	glPopMatrix();
}
void thighOutlook() {
	glPushMatrix();
	{
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
		}
		drawFootOutlook(-0.48, 0, 0.1, 0.08, -0.5, 0.5, 0.58, 0.4, 0, 0, 0.8, 0);
		glDeleteTextures(1, &galaxyTexture);
	}//0.08,-0.5,0.3
	glPopMatrix();
}
void calfBone() { // small leg
	glPushMatrix(); {

		glPushMatrix(); {
			lightGreyMaterial();
			glColor3f(0.7, 0.7, 0.7);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(-0.1, 0, 0.2, -0.1, 1.0, 0.4, 0.3, 0, 0, 0.3, 1.4, 0);
			glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
		glPushMatrix(); {
			lightGreyMaterial();
			glColor3f(0.7, 0.7, 0.7);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(-0.1, 0, 0.2, -0.1, 1.4, 0.4, 0.3, 0, 0, 0.3, 1.8, 0);
			glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void calfOutlook() {

	glPushMatrix();
	{
		//--------------------------------------------------
		//The 6 things at behind
		glPushMatrix();
		{
			whiteMaterial();
			glColor3f(1, 1, 1);
			glPushMatrix(); {
				glTranslatef(-0.2, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();

			glPushMatrix(); {
				glTranslatef(-0.1, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0.1, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0.2, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0.3, 0.8, 0.3);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(0, 0, 0.1, 0, 0.6, 0.6, 0.1, 0, 0, 0.1, 1, 0.3);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//-------------------------------------------------
		//Things that at the front of the leg
		glPushMatrix(); {
			whiteMaterial();
			glColor3f(1, 1, 1);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(0, -2.3, -0.2);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawFootBone(-0.2, 0, 0.1, -0.2, 0.5, 0.5, 0.4, 0, 0, 0.4, 1.3, 0.3);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		//Two things at the back side of the leg
		glPushMatrix();
		{
			greyMaterial();
			glColor3f(0.5, 0.5, 0.5);
			glTranslatef(0.2, 1.095, 0.201);
			glRotatef(90, 0, 0, 1);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawFootBone(0, 0, 0.2, -0.1, -0.1, 0.6, 0.1, 0, 0.2, 0.1, 0.3, 0);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			greyMaterial();
			glColor3f(0.5, 0.5, 0.5);
			glTranslatef(0.2, 1.295, 0.201);
			glRotatef(90, 0, 0, 1);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawFootBone(-0.1, 0, 0.2, -0.1, -0.1, 0.7, 0.1, 0, 0.2, 0.1, 0.3, 0);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		//Two things at the leg side
		glPushMatrix();
		{
			lightGreyMaterial();
			glColor3f(0.7, 0.7, 0.7);
			glTranslatef(-0.2, 0.8, 0);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(0, 0, 0.1, 0, 0.25, 0.4, 0.1, 0, 0, 0.1, 1, 0);
			glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			lightGreyMaterial();
			glColor3f(0.7, 0.7, 0.7);
			glTranslatef(0.3, 0.8, 0);
			if (textureOn) {
				armorTexture = loadTexture("textures/armor_texture.bmp");
			}
			drawFootBone(0, 0, 0.1, 0, 0.25, 0.4, 0.1, 0, 0, 0.1, 1, 0);
			glDeleteTextures(1, &armorTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void jointLeg() { // the knee
	glPushMatrix();
	{

		glPushMatrix();
		{
			whiteMaterial();
			glColor3f(1, 1, 1);
			glRotatef(90, -1, 0, 0);
			glRotatef(90, 0, 1, 0);
			glTranslatef(-0.3, -0.1, -0.16);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawCone(0.15, 0.15, 0.6, 15, 5);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			whiteMaterial();
			glColor3f(1, 1, 1);
			glTranslatef(-0.1, 0.3, 0.1);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawSphere(0.15, 20, 10);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
		glPushMatrix();
		{
			whiteMaterial();
			glColor3f(1, 1, 1);
			glTranslatef(0.4, 0.3, 0.1);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawSphere(0.15, 20, 10);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void foot() {
	glPushMatrix();
	{
		/*	glColor3f(1, 1, 1);*/
		glPushMatrix();
		{
			glPushMatrix(); //Bottom Layer #Last 
			{
				whiteMaterial();
				glColor3f(1, 1, 1);
				glPushMatrix();
				{
					glRotatef(180, 1, 0, 0);
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
					}
					drawFootBone(-0.2, 0, -0.3, 0, 0, 0, 0.2, 0, 0, 0.4, 0.05, 0);
					glDeleteTextures(1, &galaxyTexture);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glRotatef(180, 1, 0, 0);
					glTranslatef(0, 0, -0.5);
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
					}
					drawFootBone(-0.2, 0, -0.3, -0.2, 0, 0, 0.4, 0, 0, 0.4, 0.05, 0);
					glDeleteTextures(1, &galaxyTexture);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glRotatef(180, 1, 0, 0);
					glTranslatef(0, 0, -1);
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
					}
					drawFootBone(-0.2, 0, -0.3, -0.2, 0, 0, 0.4, 0, 0, 0.4, 0.05, 0);
					glDeleteTextures(1, &galaxyTexture);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glRotatef(180, 1, 0, 0);
					glTranslatef(0, 0, -1.5);
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
					}
					drawFootBone(-0.1, 0, -0.3, -0.2, 0, 0, 0.4, 0, 0, 0.3, 0.05, 0);
					glDeleteTextures(1, &galaxyTexture);
				}

				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #1
			{
				greyMaterial();
				glColor3f(0.4, 0.4, 0.4);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.05, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/armor_texture.bmp");
				}
				drawFootBone(-0.1, 0, -1.8, 0, 0, 0, 0.2, 0, 0, 0.3, 0.05, 0);
				glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #2
			{
				whiteMaterial();
				glColor3f(1, 1, 1);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.1, 0);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.2, 0, -1.8, -0.1, 0, 0, 0.3, 0, 0, 0.4, 0.2, 0.2);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #3
			{
				greyMaterial();
				glColor3f(0.4, 0.4, 0.4);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.25, -0.8);
				if (textureOn) {
					armorTexture = loadTexture("textures/armor_texture.bmp");
				}
				drawFootBone(-0.2, 0, -1, -0.13, 0, 0, 0.33, 0, 0, 0.4, 0.1, 0);
				glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #3
			{
				whiteMaterial();
				glColor3f(1, 1, 1);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.25, -0.2);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.14, 0, -0.5, -0.1, 0, 0, 0.3, 0, 0, 0.34, 0.1, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #4
			{
				greyMaterial();
				glColor3f(0.4, 0.4, 0.4);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.3, -0.2);
				if (textureOn) {
					armorTexture = loadTexture("textures/armor_texture.bmp");
				}
				drawFootBone(-0.14, 0, -1.6, -0.1, 0, -0.5, 0.3, 0, 0, 0.34, 0.1, 0);
				glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #5
			{
				whiteMaterial();
				glColor3f(1, 1, 1);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.4, -0.2);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.14, 0, -1.6, -0.1, 0, -0.8, 0.3, 0, 0, 0.34, 0.1, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #6
			{
				whiteMaterial();
				glColor3f(1, 1, 1);
				glRotatef(180, 1, 0, 0);
				glTranslatef(0, 0.4, -0.2);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.14, 0, -1.6, -0.1, 0, -0.9, 0.3, 0, 0, 0.34, 0.2, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix(); // Scrow out the leg
		{
			glPushMatrix(); //Bottom Layer #3
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(-0.2, 0.25, -0.2);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.1, 0, -0.8, -0.1, 0, -0.5, 0.1, 0, 0, 0.1, 0.1, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #2
			{
				glTranslatef(-0.3, -0.2, 1.5);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.1, 0.2, -0.8, -0.1, -0.05, -0.5, 0.1, 0, 0, 0.1, 0.15, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #2
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(-0.3, 0.2, -0.2);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.1, 0, -0.8, -0.1, -0.05, -0.5, 0.1, 0.1, 0, 0.1, 0.05, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
			glPushMatrix(); //Bottom Layer #Last
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(-0.5, 0, -0.7);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawFootBone(-0.1, 0, -0.3, -0.1, 0, 0, 0.1, 0, 0, 0.1, 0.05, 0);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); // Leg circle
		{
			glPushMatrix();
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(0.38, 0.2, -1.5);
				if (textureOn) {
					armorTexture = loadTexture("textures/armor_texture.bmp");
				}
				drawSphere(0.1, 15, 10);
				glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(0.36, 0.2, -1.3);
				if (textureOn) {
					armorTexture = loadTexture("textures/armor_texture.bmp");
				}
				drawSphere(0.1, 15, 10);
				glDeleteTextures(1, &armorTexture);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotatef(180, 1, 0, 0);
				glTranslatef(0.34, 0.2, -1.1);
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
				}
				drawSphere(0.1, 15, 10);
				glDeleteTextures(1, &galaxyTexture);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix(); // The big cube at the back
		{
			glRotatef(180, 1, 0, 0);
			glTranslatef(0, 0.4, -0.2);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
			}
			drawFootBone(-0.2, 0, -1.7, -0.2, -0.3, -1.6, 0.4, 0, 0, 0.4, 0.2, 0);
			glDeleteTextures(1, &galaxyTexture);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void drawRightLeg() {
	glPushMatrix();
	{
		//glRotatef(90, 1, 0, 0);
		glPushMatrix();
		{

			glPushMatrix();
			{

				glPushMatrix();
				{
					thighBone();

				}
				glPopMatrix();
				glPushMatrix();
				{
					thighOutlook();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.05, 0.6, 0.2);
				jointLeg();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.4, 1.0, 0.1); //Switch origin to prefered rotate point.
			glRotatef(rightkneeAngle, rightLegAxis[1][0], rightLegAxis[1][1], rightLegAxis[1][2]); //Rotating joint.

			glRotatef(180, 1, 0, 0);
			glTranslatef(-0.4, -1.0, -0.1);
			//glTranslatef(0.4, 1.0, 0.1);
			//glRotatef(rightkneeAngle, rightLegAxis[1][0], rightLegAxis[1][1], rightLegAxis[1][2]); //Rotating joint.
			//glRotatef(rightkneeAngle, 1, 0, 0);
			//glTranslatef(-0.4, -1.0, -0.1);
			glPushMatrix();
			{
				glPushMatrix();
				{
					calfBone();
				}
				glPopMatrix();
				glPushMatrix();
				{
					calfOutlook();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, 2.4, -1.4);
				foot();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
//Need to use scalef
void drawLeftLeg() {
	glPushMatrix();
	{
		glColor3f(0, 0, 0);
		glPushMatrix();
		{
			glPushMatrix();
			{
				glPushMatrix();
				{
					glScalef(-1, 1, 1);
					thighBone();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(-1, 1, 1);
					thighOutlook();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1, 1, 1);
				glTranslatef(-0.05, 0.6, 0.2);
				jointLeg();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.4, 1.0, 0.1); //Switch origin to prefered rotate point.
			glRotatef(leftkneeAngle, leftLegAxis[1][0], leftLegAxis[1][1], leftLegAxis[1][2]); //Rotating joint.

			glRotatef(180, 1, 0, 0);
			glTranslatef(-0.4, -1.0, -0.1); //Switch origin to prefered rotate point.
			//glTranslatef(0.4, 1.0, 0.1);
			//glRotatef(leftkneeAngle, 1, 0, 0);
			//glTranslatef(-0.4, -1.0, -0.1);
			glPushMatrix();
			{
				glPushMatrix();
				{
					glScalef(-1, 1, 1);
					calfBone();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(-1, 1, 1);
					calfOutlook();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1, 1, 1);
				glTranslatef(0, 2.4, -1.4);
				foot();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}



#pragma endregion
#pragma region BODY
void energyCore() {
	blackMaterial();

	glColor3f(0.3, 0.3, 0.3);
	//outer frame
	glPushMatrix(); {
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
		}
		glTranslatef(0, 0.4, -0.285);
		drawCyclinder(0.1, 0.15, 0.03);
		glDeleteTextures(1, &galaxyTexture);
		glDisable(GL_TEXTURE_2D);

		yellowMaterial();
		//outer color
		glPushMatrix();
		{
			glColor3f(0.6, 0.6, 0.6);
			if (textureOn) {
				reactorTexture = loadTexture("textures/reactor.bmp");
			}
			glRotatef(degreeReactor, 0, 0, 1);
			drawCyclinder(0.1, 0, 0.05);
			glDeleteTextures(1, &reactorTexture);
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();

		orangeMaterial();
		//inner circle
		glPushMatrix();
		{
			if (textureOn) {
				reactorTexture = loadTexture("textures/reactor.bmp");
			}
			glTranslatef(0, 0, 0.04);
			glRotatef(-degreeReactor, 0, 0, 1);
			drawSphere(0.04,50,50);
			glDeleteTextures(1, &reactorTexture);
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void jet() {
	greyMaterial();
	glColor3f(0.8, 0.8, 0.8);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	glPushMatrix();
	{
		glTranslatef(-0.38, 0.9, 0.28);
		glRotatef(23, 0, 0, 1);
		glPushMatrix();
		{
			glRotatef(100, 1, 0, 0);
			drawCyclinder(0.17, 0.05, 0.6);
		}
		glPopMatrix();
	}
	glPopMatrix();

	//to make the end of jet curved
	glPushMatrix();
	{
		glTranslatef(-0.147, 0.36, 0.18);
		drawSphere(0.05,50,50);
	}
	glPopMatrix();

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	if (textureOn) {
		glassTexture = loadTexture("textures/glass_texture.bmp");
	}

	//make an circle/light in openning jet
	glPushMatrix();
	{
		glTranslatef(-0.34, 0.8, 0.27);
		drawSphere(0.135,50,50);
	}
	glPopMatrix();

	glDeleteTextures(1, &glassTexture);
	glDisable(GL_TEXTURE_2D);
}
void body() {

	whiteMaterial();

	glColor3f(1, 1, 1);
	energyCore();
	glPushMatrix();
	glTranslatef(-0.2, 0.55, 0.3);
	glRotatef(jetDegree, 0, 0, 1);
	glTranslatef(0.2, -0.55, -0.3);	//back to origin
	jet();
	glPopMatrix();

	//tiny piece

	greyMaterial();
	glColor3f(0.4, 0.4, 0.4);

	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	drawTexturedQuads(-0.05, 0.7, -0.16, -0.001, 0.7, -0.16, -0.001, 0.55, -0.26, -0.05, 0.55, -0.26);			//front
	drawTexturedQuads(-0.00, 0.7, -0.10, -0.00, 0.7, -0.10, -0.00, 0.535, -0.20, -0.0, 0.535, -0.20);	//back
	drawTexturedQuads(-0.05, 0.7, -0.16, -0.00, 0.7, -0.10, -0.00, 0.7, -0.10, -0.001, 0.7, -0.16);		//top
	drawTexturedQuads(-0.001, 0.55, -0.26, -0.05, 0.55, -0.26, -0.0, 0.535, -0.20, -0.00, 0.535, -0.20);	//btm
	drawTexturedQuads(-0.05, 0.55, -0.26, -0.05, 0.7, -0.16, -0.00, 0.7, -0.10, -0.0, 0.535, -0.20);		//left
	drawTexturedQuads(-0.001, 0.7, -0.16, -0.001, 0.55, -0.26, -0.00, 0.535, -0.20, -0.00, 0.7, -0.10);	//right

	//support head part -> neck
	drawTexturedQuads(-0.1, 0.75, -0.0, -0.0, 0.75, -0.0, -0.0, 0.7, -0.0, -0.15, 0.7, -0.0);	//neck
	drawTexturedTriangles(-0.1, 0.75, -0.0, -0.15, 0.7, -0.15, -0.15, 0.7, -0.0);				//neck - left side
	drawTexturedQuads(-0.1, 0.75, -0.0, -0.0, 0.75, -0.0, -0.0, 0.7, -0.15, -0.15, 0.7, -0.15);	//neck - back

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	greyMaterial();

	glColor3f(0.8, 0.8, 0.8);
	if (textureOn) {
		armorTexture = loadTexture(textureArray[0][textureOption]);
	}
	drawTexturedQuads(-0.3, 0.82, 0.05, -0.2, 0.85, 0.05, -0, 0.7, -0.05, -0.4, 0.7, -0.05);	//another neck
	drawTexturedQuads(-0.3, 0.82, 0.05, -0.3, 0.82, 0.12, -0.4, 0.7, 0.12, -0.4, 0.7, -0.05);	//another neck left
	drawTexturedTriangles(-0.3, 0.82, 0.12, -0.2, 0.85, 0.05, -0.3, 0.82, 0.05);	//another neck- top
	drawTexturedQuads(-0.3, 0.82, 0.12, -0.2, 0.85, 0.05, -0.2, 0.7, 0.05, -0.3, 0.7, 0.12);//another neck  - back
	drawTexturedTriangles(-0.2, 0.85, 0.05, -0, 0.7, -0.05, -0.2, 0.7, 0.05);

	//glDeleteTextures(1, &armorTexture);
	//glDisable(GL_TEXTURE_2D);

	//whiteMaterial();

	//glColor3f(1, 1, 1);
	//if (textureOn) {
	//	armorTexture = loadTexture("textures/galaxy_texture.bmp");
	//}
	//front armor 1st piece
	drawTexturedTriangles(-0.4, 0.7, -0.1, -0.05, 0.7, -0.2, -0.05, 0.55, -0.25);		//front
	drawTexturedTriangles(-0.4, 0.68, -0.08, -0.05, 0.68, -0.18, -0.05, 0.53, -0.23);	//back
	drawTexturedQuads(-0.4, 0.7, -0.1, -0.05, 0.7, -0.2, -0.05, 0.68, -0.18, -0.4, 0.68, -0.08);	//top
	drawTexturedQuads(-0.05, 0.7, -0.2, -0.05, 0.55, -0.25, -0.05, 0.53, -0.23, -0.05, 0.68, -0.18);	//btm1
	drawTexturedQuads(-0.4, 0.7, -0.1, -0.05, 0.55, -0.25, -0.05, 0.53, -0.23, -0.05, 0.68, -0.18);	//btm2

	drawTexturedQuads(-0.4, 0.7, -0.1, -0.05, 0.7, -0.2, -0.05, 0.7, 0, -0.4, 0.7, 0);	//cover
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);

	blackMaterial();

	glColor3f(0.4, 0.4, 0.4);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	//2nd PIECE
	drawTexturedQuads(-0.35, 0.7, -0.05, -0.05, 0.55, -0.24, -0.15, 0.35, -0.26, -0.45, 0.5, -0.07);	//front
	drawTexturedQuads(-0.35, 0.68, 0.00, -0.05, 0.53, -0.19, -0.15, 0.33, -0.21, -0.45, 0.48, -0.02);	//back
	drawTexturedQuads(-0.35, 0.7, -0.05, -0.05, 0.55, -0.24, -0.05, 0.53, -0.19, -0.35, 0.68, 0.00);	//top
	drawTexturedQuads(-0.15, 0.35, -0.26, -0.45, 0.5, -0.07, -0.45, 0.48, -0.02, -0.15, 0.33, -0.21);	//btm
	drawTexturedQuads(-0.35, 0.7, -0.05, -0.45, 0.5, -0.07, -0.45, 0.48, -0.02, -0.35, 0.68, 0.00);	//left
	drawTexturedQuads(-0.05, 0.55, -0.24, -0.15, 0.35, -0.26, -0.15, 0.33, -0.21, -0.05, 0.53, -0.19);	//right

	//2nd PIECE - side
	drawTexturedQuads(-0.35, 0.7, 0.15, -0.35, 0.7, -0.03, -0.46, 0.49, -0.03, -0.46, 0.49, 0.15);	//right
	drawTexturedQuads(-0.37, 0.7, 0.15, -0.37, 0.7, -0.03, -0.48, 0.49, -0.03, -0.48, 0.49, 0.15);	//left
	drawTexturedQuads(-0.35, 0.7, 0.15, -0.35, 0.7, -0.03, -0.37, 0.7, -0.03, -0.37, 0.7, 0.15);	//top
	drawTexturedQuads(-0.46, 0.49, -0.03, -0.46, 0.49, 0.15, -0.48, 0.49, 0.15, -0.48, 0.49, -0.03);	//btm
	drawTexturedQuads(-0.35, 0.7, -0.03, -0.46, 0.49, -0.03, -0.48, 0.49, -0.03, -0.37, 0.7, -0.03);	//front
	drawTexturedQuads(-0.35, 0.7, 0.15, -0.46, 0.49, 0.15, -0.48, 0.49, 0.15, -0.37, 0.7, 0.15);	//right

	//2nd PIECE - below side
	drawTexturedQuads(-0.47, 0.49, -0.03, -0.47, 0.49, 0.15, -0.0, 0.44, 0.15, -0.0, 0.44, -0.09);	//top
	drawTexturedQuads(-0.47, 0.47, -0.03, -0.47, 0.47, 0.15, -0.0, 0.42, 0.15, -0.0, 0.42, -0.09);	//bottom
	drawTexturedQuads(-0.47, 0.49, -0.03, -0.0, 0.44, -0.09, -0.0, 0.42, -0.09, -0.47, 0.47, -0.03);	//front
	drawTexturedQuads(-0.47, 0.49, 0.15, -0.0, 0.44, 0.15, -0.0, 0.42, 0.15, -0.47, 0.47, 0.15);	//back
	drawTexturedQuads(-0.47, 0.49, -0.03, -0.47, 0.49, 0.15, -0.47, 0.47, 0.15, -0.47, 0.47, -0.03);	//left
	drawTexturedQuads(-0.0, 0.44, 0.15, -0.0, 0.44, -0.09, -0.0, 0.42, -0.09, -0.0, 0.42, 0.15);	//right

	//2nd PIECE - back
	drawTexturedQuads(-0.38, 0.68, 0.13, -0.48, 0.48, 0.15, -0.0, 0.42, 0.16, -0.0, 0.68, 0.14);	//back
	drawTexturedQuads(-0.38, 0.68, 0.15, -0.48, 0.48, 0.17, -0.0, 0.42, 0.18, -0.0, 0.68, 0.16);	//front
	drawTexturedQuads(-0.38, 0.68, 0.13, -0.0, 0.68, 0.14, -0.0, 0.68, 0.16, -0.38, 0.68, 0.15);	//top
	drawTexturedQuads(-0.48, 0.48, 0.15, -0.0, 0.42, 0.16, -0.0, 0.42, 0.18, -0.48, 0.48, 0.17);	//btm
	drawTexturedQuads(-0.38, 0.68, 0.13, -0.48, 0.48, 0.15, -0.48, 0.48, 0.17, -0.38, 0.68, 0.15);	//left
	drawTexturedQuads(-0.0, 0.42, 0.16, -0.0, 0.68, 0.14, -0.0, 0.68, 0.16, -0.0, 0.42, 0.18);	//right

	//2nd piece - top cover
	drawTexturedQuads(-0.0, 0.68, 0.16, -0.38, 0.68, 0.15, -0.35, 0.7, -0.03, -0.0, 0.7, -0.03);

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	//3rd PIECE 
	//front
	greyMaterial();

	glColor3f(0.8, 0.8, 0.8);
	if (textureOn) {
		armorTexture = loadTexture("textures/armor_texture.bmp");
	}
	drawTexturedQuads(-0.37, 0.45, -0.06, -0.0, 0.45, -0.23, -0.0, 0.25, -0.25, -0.35, 0.25, -0.1);	//front
	drawTexturedQuads(-0.37, 0.45, -0.06, -0.37, 0.45, 0.10, -0.28, 0.25, 0.10, -0.35, 0.25, -0.1);	//left
	drawTexturedQuads(-0.0, 0.45, 0.15, -0.37, 0.45, 0.10, -0.28, 0.25, 0.10, -0.0, 0.25, 0.15);	//back
	drawTexturedQuads(-0.0, 0.45, -0.23, -0.35, 0.45, -0.06, -0.37, 0.45, 0.10, -0.0, 0.45, 0.15);	//top
	drawTexturedQuads(-0.0, 0.25, -0.25, -0.35, 0.25, -0.1, -0.28, 0.25, 0.10, -0.0, 0.25, 0.15);	//btm
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);
	//end of 3rd piece

	//sp energy core //strip
	blackMaterial();
	glColor3f(0.4, 0.4, 0.4);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	drawTexturedQuads(-0.35, 0.27, -0.13, -0.14, 0.35, -0.27, -0.12, 0.31, -0.27, -0.33, 0.23, -0.15);	//front
	drawTexturedQuads(-0.35, 0.27, -0.08, -0.14, 0.35, -0.22, -0.12, 0.31, -0.22, -0.33, 0.23, -0.10);	//back
	drawTexturedQuads(-0.35, 0.27, -0.13, -0.14, 0.35, -0.27, -0.14, 0.35, -0.22, -0.35, 0.27, -0.08);	//top
	drawTexturedQuads(-0.12, 0.31, -0.27, -0.33, 0.23, -0.15, -0.33, 0.23, -0.10, -0.12, 0.31, -0.22);	//btm
	drawTexturedQuads(-0.35, 0.27, -0.13, -0.33, 0.23, -0.15, -0.33, 0.23, -0.10, -0.35, 0.27, -0.08);	//left
	drawTexturedQuads(-0.14, 0.35, -0.27, -0.12, 0.31, -0.27, -0.12, 0.31, -0.22, -0.14, 0.35, -0.22);	//right

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);
	//end of front armor

	//under energy core 
	greyMaterial();

	glColor3f(0.8, 0.8, 0.8);
	if (textureOn) {
		armorTexture = loadTexture("textures/armor_texture.bmp");
	}
	drawTexturedQuads(-0.07, 0.4, -0.2, 0, 0.4, -0.24, 0, -0.05, -0.2, -0.07, -0.05, -0.2);	//front
	drawTexturedQuads(-0.07, 0.4, -0.15, 0, 0.4, -0.21, 0, -0.05, -0.15, -0.07, -0.05, -0.15);	//back
	drawTexturedQuads(-0.07, 0.4, -0.2, -0.07, -0.05, -0.2, -0.07, -0.05, -0.15, -0.07, 0.4, -0.15);	//left
	drawTexturedQuads(0, 0.4, -0.24, 0, -0.05, -0.2, 0, -0.05, -0.15, 0, 0.4, -0.21);	//right
	drawTexturedQuads(-0.07, 0.4, -0.2, 0, 0.4, -0.24, 0, 0.4, -0.21, -0.07, 0.4, -0.15);	//top
	drawTexturedQuads(0, -0.05, -0.2, -0.07, -0.05, -0.2, -0.07, -0.05, -0.15, 0, -0.05, -0.15);	//back
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);


	//under energy core - deco
	blackMaterial();

	glColor3f(0.4, 0.4, 0.4);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	drawTexturedQuads(-0.08, 0.25, -0.22, -0.05, 0.25, -0.22, -0.05, -0.05, -0.22, -0.08, -0.05, -0.22);	//front
	drawTexturedQuads(-0.08, 0.25, -0.17, -0.05, 0.25, -0.17, -0.05, -0.05, -0.17, -0.08, -0.05, -0.17);	//back
	drawTexturedQuads(-0.08, 0.25, -0.22, -0.08, -0.05, -0.22, -0.08, -0.05, -0.17, -0.08, 0.25, -0.17);	//left
	drawTexturedQuads(-0.05, 0.25, -0.22, -0.05, -0.05, -0.22, -0.05, -0.05, -0.17, -0.05, 0.25, -0.17);	//right
	drawTexturedQuads(-0.08, 0.25, -0.22, -0.05, 0.25, -0.22, -0.05, 0.25, -0.17, -0.08, 0.25, -0.17);	//top
	drawTexturedQuads(-0.05, -0.05, -0.22, -0.08, -0.05, -0.22, -0.08, -0.05, -0.17, -0.05, -0.05, -0.17);	//btm
	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	greyMaterial();

	glColor3f(0.6, 0.6, 0.6);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[1][textureOption]);
	}

	//beside the sp under energy core
	for (float i = 0; i >= -0.18; i -= 0.06) {
		glPushMatrix();
		glTranslatef(0, i, 0);

		drawTexturedQuads(-0.07, 0.25, -0.18, -0.28, 0.27, -0.10, -0.30, 0.17, -0.15, -0.09, 0.15, -0.20);	//front
		drawTexturedQuads(-0.07, 0.25, -0.16, -0.28, 0.27, -0.08, -0.30, 0.17, -0.13, -0.09, 0.15, -0.18);	//back
		drawTexturedQuads(-0.07, 0.25, -0.18, -0.28, 0.27, -0.10, -0.28, 0.27, -0.08, -0.07, 0.25, -0.16);	//top
		drawTexturedQuads(-0.30, 0.17, -0.15, -0.09, 0.15, -0.20, -0.09, 0.15, -0.18, -0.30, 0.17, -0.13);	//btm
		drawTexturedQuads(-0.28, 0.27, -0.10, -0.30, 0.17, -0.15, -0.30, 0.17, -0.13, -0.28, 0.27, -0.08);	//left
		drawTexturedQuads(-0.07, 0.25, -0.18, -0.09, 0.15, -0.20, -0.09, 0.15, -0.18, -0.07, 0.25, -0.16);	//right

		glPopMatrix();
	}
	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);

	blackMaterial();

	glColor3f(0.4, 0.4, 0.4);
	if (textureOn) {
		galaxyTexture = loadTexture(textureArray[0][textureOption]);
	}
	//front the piecesss
	drawTexturedQuads(-0.0, 0.27, -0.15, -0.27, 0.27, -0.10, -0.27, -0.04, -0.10, -0.0, -0.04, -0.15);

	//beside the piecesss
	drawTexturedQuads(-0.30, 0.27, 0, -0.27, 0.27, -0.10, -0.27, -0.04, -0.10, -0.30, -0.04, 0);

	//beside the piecesss 2
	drawTexturedQuads(-0.27, 0.27, 0.10, -0.30, 0.27, 0, -0.30, -0.04, 0, -0.27, -0.04, 0.10);

	//behind the piecesss
	drawTexturedQuads(-0.27, 0.27, 0.10, -0, 0.27, 0.12, -0, -0.04, 0.11, -0.27, -0.04, 0.09);

	//below the piecesss
	drawTexturedQuads(-0.27, -0.04, 0.10, -0, -0.04, 0.12, -0, -0.04, -0.0, -0.30, -0.04, -0.0);
	drawTexturedQuads(-0, -0.04, -0.0, -0.30, -0.04, -0.0, -0.27, -0.04, -0.1, -0.0, -0.04, -0.15);

	glDeleteTextures(1, &galaxyTexture);
	glDisable(GL_TEXTURE_2D);
}
void createLaserBall() {
	orangeMaterial();
	glColor3f(1, 1, 0);
	if (textureOn) {
		reactorTexture = loadTexture("textures/eyeglass.bmp");
	}

	drawSphere(0.01,50,50);
	glDeleteTextures(1, &reactorTexture);
	glDisable(GL_TEXTURE_2D);
}

#pragma endregion 
void displayFire() {

	orangeMaterial();

	if (textureOn) {
		flameTexture = loadTexture("textures/boostFlame.bmp");
	}
	lightGreyMaterial();
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix(); {
		glTranslatef(-0.2, -0.3, 0.4);

		glPushMatrix();
		{
			glRotatef(260, 1, 0, 0);
			drawCyclinder(0.12, 0.05, 0.5);
		}
		glPopMatrix();
	}
	glPopMatrix();

	if (textureOn) {
		flameTexture = loadTexture("textures/invertedBoostFlame.bmp");
	}

	//little fire
	glPushMatrix();
	{
		glTranslatef(-0.24, -0.22, 0.42);
		glRotatef(90, 1, 0, 0);
		drawCyclinder(0.06, 0.01, 0.22);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.16, -0.22, 0.42);
		glRotatef(90, 1, 0, 0);
		drawCyclinder(0.06, 0.01, 0.22);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.24, -0.22, 0.32);
		glRotatef(90, 1, 0, 0);
		drawCyclinder(0.06, 0.01, 0.22);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.16, -0.22, 0.32);
		glRotatef(90, 1, 0, 0);
		drawCyclinder(0.06, 0.01, 0.22);
	}
	glPopMatrix();

	glDeleteTextures(1, &flameTexture);
	glDisable(GL_TEXTURE_2D);
}
#pragma region HAND
void fin() { //14 
	GLUquadric* obj = gluNewQuadric();


	glPushMatrix();
	{
		glRotatef(315, 0, 0, 1);
		whiteMaterial();
		glColor3f(1, 1, 1);

		//front part
		//back Finger
		//Base
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.075, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.075, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
		}



		//Front
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0.0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0.0);
			glEnd();
		}



		//back
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0);
		}



		//below
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.1, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
		}



		//---------------------------------------------
		//front finger
		//Front
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0.0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0.0);
			glEnd();
		}



		//back
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);

		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.075, 0);
			glEnd();
		}



		//below
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);

		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.15, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
		}

	}
	glPopMatrix();

	//-------------------------
	//backPart
	//back Finger
	//Base
	glPushMatrix();
	{
		whiteMaterial();
		glColor3f(1, 1, 1);
		glTranslatef(0.01, -0.025, 0);
		glRotatef(290, 0, 0, 1);

		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.045, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.045, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
		}



		//Front
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0.0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0.0);
			glEnd();
		}



		//back
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0);
			glEnd();
		}



		//below
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
		}




		//---------------------------------------------
		//front finger
		//Front
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0.0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0.0);
			glEnd();
		}



		//back
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.045, 0);
			glEnd();

		}


		//below
		if (textureOn) {
			galaxyTexture = loadTexture(textureArray[0][textureOption]);
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();
			glDeleteTextures(1, &galaxyTexture);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.025);
			glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.075, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.025);
			glEnd();

		}

	}
	glPopMatrix();

	gluDeleteQuadric(obj);
}
void drawCurveCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
	bend_angle = bend_radius * height;
	bend_ang0 = -bend_angle / 0.30f;
	bend_ang1 = bend_angle / 0.30f;
	for (i = 0; i < slice; i++)
	{
		w0 = (float)i / (float)slice;
		w1 = (float)(i + 1) / (float)slice;

		ang0 = bend_ang0 + (bend_ang1 - bend_ang0) * w0;
		ang1 = bend_ang0 + (bend_ang1 - bend_ang0) * w1;

		glPushMatrix();
		glTranslatef(-0.8175, 0.15, 0.1);
		glRotatef(120, 1, 1, 1);
		lightGreyMaterial();
		glColor3f(0.7, 0.7, 0.7);
		if (textureOn) {
			armorTexture = loadTexture("textures/metal_texture.bmp");
		}
		glBegin(GL_QUAD_STRIP);

		for (j = 0; j <= 360; ++j)
		{
			angle = PI * (float)j * PI / 180.0f;
			x = radius * cos(angle) + bend_radius;
			y = radius * sin(angle);

			xb = sin(ang0) * x;
			yb = y;
			zb = cos(ang0) * x;
			glTexCoord2f(0.0f, 0.0f); glVertex3f(xb, yb, zb);

			xb = sin(ang1) * x;
			yb = y;
			zb = cos(ang1) * x;
			glTexCoord2f(0.0f, 0.1f); glVertex3f(xb, yb, zb);
		}
		glEnd();
		glDeleteTextures(1, &armorTexture);
		glPopMatrix();
	}
}
void bullet() {

	if (gunFire) {
		glPushMatrix();
		glPushMatrix();
		redMaterial();
		glColor3f(1, 0, 0);
		glTranslatef(0, -0.1, 0.2);
		glPushMatrix();
		//glRotatef(-90,0,1,0);
		//drawSphereLine(0.03, 1, 1, 0);
		drawSphere(0.1, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
	}


}
void bulletSpam() {
	if (textureOn == false) {
		if (gunX > -3.0) {
			glTranslatef(0, 0, -gunX);
			gunX -= 0.005;
		}
		else if (gunX < -3.0) {
			gunFire = true;
			gunX = 0.0;
		}
	}
	if (textureOn) {
		if (gunX > -3.0) {
			glTranslatef(0, 0, -gunX);
			gunX -= 0.1;
		}
		else if (gunX < -3.0) {
			gunFire = true;
			gunX = 0.0;
		}
	}
	bullet();

}
void gun() {
	if (textureOn) {
		armorTexture = loadTexture("textures/metal_texture.bmp");
		drawCyclinder2(0.3, 0.3, 0.7, 20, 20);
		glDeleteTextures(1, &armorTexture);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		drawCyclinder2(0.3, 0.3, 0.7, 20, 20);
	}

	if (gunFire) {
		bulletSpam();
	}
}

void lefthand() {
	GLUquadricObj* obj = NULL;
	obj = gluNewQuadric();
	glPushMatrix();
	{
		glTranslatef(0.125, 0.5, 0.1);
		glRotatef(leftShoulderAngle, 1, 0, 0);
		glTranslatef(-0.125, -0.5, -0.1);

		glPushMatrix();
		{
			//Shoulder
			glPushMatrix();
			{
				whiteMaterial();
				glColor3f(1.0f, 1.0, 1);
				//top 
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.125, 0.55, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.125, 0.55, 0.225);
					glEnd();
				}

				//bottom
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.4, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.4, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();

				}


				//left
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);

				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.4, -0.025);
					glEnd();

				}


				//right
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.225, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.225, 0.4, -0.025);
					glEnd();

				}


				//front 
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();

				}


				//back
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);            //6
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);            //6
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, -0.025);
					glEnd();

				}

			}
			glPopMatrix();

			//---------------------------------
			//joint #1
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.1, 0.40, 0.1);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawSphere(0.1, 50, 50);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}

				else {
					drawSphere(0.1, 50, 50);
				}
			}
			glPopMatrix();

			//--------------------------------
			//middle Arm
			glPushMatrix();
			{
				glTranslatef(0.2, 0.425, 0.15);
				glRotatef(leftUpperArmAngle, 1, 0, 1);
				glTranslatef(-0.2, -0.425, -0.15);

				glPushMatrix();
				{
					whiteMaterial();
					glColor3f(1, 1, 1);
					glTranslatef(0.1, 0.18, 0.05);
					glRotatef(25, 0, 0, 1);

					//front
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.1);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();
						glDeleteTextures(1, &galaxyTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.1);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();

					}


					//back
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.0);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.0);
						glEnd();
						glDeleteTextures(1, &galaxyTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.0);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.0);
						glEnd();

					}


					//left
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();
						glDeleteTextures(1, &galaxyTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();

					}


					//right
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.15, 0.15, 0.1);     //5
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.15, 0.0, 0.1);
						glEnd();
						glDeleteTextures(1, &galaxyTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.15, 0.15, 0.1);     //5
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.15, 0.0, 0.1);
						glEnd();

					}


					//bottom
					if (textureOn) {
						galaxyTexture = loadTexture(textureArray[0][textureOption]);
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();
						glDeleteTextures(1, &galaxyTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
						glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
						glEnd();

					}


				}
				glPopMatrix();
				//------------------------------

				//joint #2
				//First screw
				glPushMatrix();
				{
					greyMaterial();
					glColor3f(0.4, 0.4, 0.4);
					glTranslatef(0.1, 0.17, 0.025);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawCyclinder2(0.06, 0.06, 0.15, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);
					}

					else {
						drawCyclinder2(0.06, 0.06, 0.15, 8, 10);
					}

				}glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.1, 0.17, 0.175);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawDisk2(0.0, 0.06, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);

					}
					else {
						drawDisk2(0.0, 0.06, 8, 10);
					}




				}
				glPopMatrix();

				glPushMatrix();
				{
					greyMaterial();
					glColor3f(0.4, 0.4, 0.4);
					glTranslatef(0.1, 0.17, 0.025);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawDisk2(0.0, 0.06, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						drawDisk2(0.0, 0.06, 8, 10);
					}


				}
				glPopMatrix();

				//sec Screw
				glPushMatrix();
				{
					greyMaterial();
					glColor3f(0.4, 0.4, 0.4);
					glTranslatef(0.11, 0.08, 0.025);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawCyclinder2(0.045, 0.045, 0.15, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						drawCyclinder2(0.045, 0.045, 0.15, 8, 10);
					}
				}
				glPopMatrix();

				glPushMatrix();
				{
					greyMaterial();
					glColor3f(0.4, 0.4, 0.4);
					glTranslatef(0.11, 0.08, 0.175);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawDisk2(0.0, 0.045, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						drawDisk2(0.0, 0.045, 8, 10);
					}

				}
				glPopMatrix();

				glPushMatrix();
				{
					greyMaterial();
					glColor3f(0.4, 0.4, 0.4);
					glTranslatef(0.11, 0.08, 0.025);
					if (textureOn) {
						armorTexture = loadTexture("textures/metal_texture.bmp");
						gluQuadricTexture(obj, true);
						drawDisk2(0.0, 0.045, 8, 10);
						glDeleteTextures(1, &armorTexture);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						drawDisk2(0.0, 0.045, 8, 10);
					}

				}
				glPopMatrix();

				glPushMatrix();
				{
					drawCurveCylinder(0.05, 0.03, 255, 160, 100);   //1
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.145, 0.05, 0.075);
					glRotatef(leftElbowAngle1, 1, 0.2, 0);
					glTranslatef(-0.145, -0.05, -0.075);
					glPushMatrix(); //arm rotation
					{
						if (gunFire) {
							glPushMatrix();

							glTranslatef(0.15, 0.05, 0.15);

							glPushMatrix();
							glRotatef(90, 1, 0, 0);
							glPushMatrix();
							glRotatef(-10, 1, 0, 0);
							glPushMatrix();
							glScalef(0.2, 0.2, 1);

							gun();
							glPopMatrix();
							glPopMatrix();
							glPopMatrix();
							glPopMatrix();
						}
						glTranslatef(0.145, 0.05, 0.1);
						glRotatef(leftElbowAngle, 0, 1, 0);
						glTranslatef(-0.145, -0.05, -0.1);
						glPushMatrix();
						{
							whiteMaterial();
							glColor3f(1, 1, 1);
							glTranslatef(0.145, 0.05, 0.1);
							glRotatef(90, 1, 0, 0);
							if (textureOn) {
								galaxyTexture = loadTexture(textureArray[0][textureOption]);
								gluQuadricTexture(obj, true);
								drawCyclinder2(0.115, 0.05, 0.4, 8, 10);
								glDeleteTextures(1, &galaxyTexture);
								glDisable(GL_TEXTURE_2D);
							}
							else {
								drawCyclinder2(0.115, 0.05, 0.4, 8, 10);
							}
						}
						glPopMatrix();

						glPushMatrix();
						{
							glTranslatef(0.145, 0.05, 0.1);
							glRotatef(90, 1, 0, 0);
							if (textureOn) {
								galaxyTexture = loadTexture(textureArray[0][textureOption]);
								gluQuadricTexture(obj, true);
								drawDisk2(0.0, 0.115, 8, 10);
								glDeleteTextures(1, &galaxyTexture);
								glDisable(GL_TEXTURE_2D);
							}
							else {
								drawDisk2(0.0, 0.115, 8, 10);
							}
						}
						glPopMatrix();

						glPushMatrix();
						{
							glTranslatef(0.145, -0.35, 0.1);
							glRotatef(90, 1, 0, 0);
							if (textureOn) {
								galaxyTexture = loadTexture(textureArray[0][textureOption]);
								gluQuadricTexture(obj, true);
								drawDisk2(0.0, 0.05, 8, 10);
								glDeleteTextures(1, &galaxyTexture);
								glDisable(GL_TEXTURE_2D);
							}
							else {
								drawDisk2(0.0, 0.05, 8, 10);
							}
						}
						glPopMatrix();




						//------------------------------------------
						//Palm
						glPushMatrix();
						{
							greyMaterial();
							glColor3f(0.4, 0.4, 0.4);
							glTranslatef(0.110, -0.5, 0.19);
							glRotatef(90, 0, 1, 0);

							//top
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0);            //6
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}
							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0);            //6
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
								glEnd();
							}


							//bottom
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.065);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}
							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.065);
								glEnd();
							}

							//front
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.0);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}

							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.0);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.0);
								glEnd();
							}

							//back
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.065);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.056);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}

							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.065);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.056);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
								glEnd();
							}

							//left
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0, 0.15, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.0);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}

							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0, 0.15, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.0);
								glEnd();
							}

							//right
							if (textureOn) {
								armorTexture = loadTexture("textures/metal_texture.bmp");
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0.175, 0, 0.0);
								glEnd();
								glDeleteTextures(1, &armorTexture);
								glDisable(GL_TEXTURE_2D);
							}

							else {
								glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
								glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0.065);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0.175, 0, 0.0);
								glEnd();
							}
						}
						glPopMatrix();

						//Fingers
						//thumb
						glPushMatrix();
						{
							glTranslatef(0.15, -0.5, 0.025);
							glRotatef(lThumbAngle, 0, 1, 0);//010
							glTranslatef(-0.15, 0.5, -0.025);
							glPushMatrix();
							{
								lightGreyMaterial();
								glColor3f(0.7, 0.7, 0.7);
								glTranslatef(0.148, -0.4, 0.025);
								glRotatef(150, 1, 0, 0);
								if (textureOn) {
									armorTexture = loadTexture("textures/metal_texture.bmp");
									gluQuadricTexture(obj, true);          //5
									drawCyclinder2(0.02, 0.02, 0.0525, 8, 10);
									glDeleteTextures(1, &armorTexture);
									glDisable(GL_TEXTURE_2D);

								}
								else {
									drawCyclinder2(0.02, 0.02, 0.0525, 8, 10);
								}

							}
							glPopMatrix();
							glPushMatrix();
							{
								glTranslatef(0.15, -0.42, -0.01);
								glRotatef(235, 1, 0, 0);
								fin();
							}
							glPopMatrix();
						}
						glPopMatrix();


						//index finger
						glPushMatrix();
						{
							glTranslatef(0.15, -0.5, -0.045);
							glRotatef(-lIndexAngle, 0, 0, 1);//001
							glTranslatef(-0.15, 0.5, 0.045);
							glPushMatrix();
							{
								lightGreyMaterial();
								glColor3f(0.7, 0.7, 0.7);
								glTranslatef(0.15, -0.475, 0.045);
								glRotatef(90, 1, 0, 0);
								if (textureOn) {
									armorTexture = loadTexture("textures/metal_texture.bmp");
									gluQuadricTexture(obj, true);
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
									glDeleteTextures(1, &armorTexture);
									glDisable(GL_TEXTURE_2D);
								}
								else {
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
								}
							}
							glPopMatrix();
							glPushMatrix();
							{
								glTranslatef(0.15, -0.54, 0.045);
								glRotatef(180, 1, 0, 0);
								fin();
							}
							glPopMatrix();
						}
						glPopMatrix();

						//middle finger

						glPushMatrix();
						{
							glTranslatef(0.15, -0.5, -0.55);
							glRotatef(-lMiddleAngle, 0, 0, 1);
							glTranslatef(-0.15, 0.5, 0.55);
							glPushMatrix();
							{
								lightGreyMaterial();
								glColor3f(0.7, 0.7, 0.7);
								glTranslatef(0.15, -0.475, 0.1);
								glRotatef(90, 1, 0, 0);
								if (textureOn) {
									armorTexture = loadTexture("textures/metal_texture.bmp");
									gluQuadricTexture(obj, true);
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
									glDeleteTextures(1, &armorTexture);
									glDisable(GL_TEXTURE_2D);
								}
								else {
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
								}
							}
							glPopMatrix();
							glPushMatrix();
							{
								glTranslatef(0.15, -0.54, 0.1);
								glRotatef(180, 1, 0, 0);
								fin();
							}
							glPopMatrix();
						}
						glPopMatrix();

						//Ring finger
						glPushMatrix();
						{
							glTranslatef(0.15, -0.5, -0.55);
							glRotatef(-lRingAngle, 0, 0, 1);
							glTranslatef(-0.15, 0.5, 0.55);
							glPushMatrix();
							{
								lightGreyMaterial();
								glColor3f(0.7, 0.7, 0.7);
								glTranslatef(0.15, -0.475, 0.16);
								glRotatef(90, 1, 0, 0);

								if (textureOn) {
									armorTexture = loadTexture("textures/metal_texture.bmp");
									gluQuadricTexture(obj, true);
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
									glDeleteTextures(1, &armorTexture);
									glDisable(GL_TEXTURE_2D);
								}
								else {
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
								}
							}
							glPopMatrix();
							glPushMatrix();
							{
								glTranslatef(0.15, -0.54, 0.16);
								glRotatef(180, 1, 0, 0);
								fin();
							}
							glPopMatrix();
						}
						glPopMatrix();

						//pinky finger
						glPushMatrix();
						{
							glTranslatef(0.15, -0.6, 0.175);
							glRotatef(-lPinkyAngle, 0, 1, 0);//010
							glTranslatef(-0.15, 0.6, -0.175);
							glPushMatrix();
							{
								lightGreyMaterial();
								glColor3f(0.7, 0.7, 0.7);
								glTranslatef(0.15, -0.4, 0.175);
								glRotatef(45, 1, 0, 0);
								if (textureOn) {
									armorTexture = loadTexture("textures/metal_texture.bmp");
									gluQuadricTexture(obj, true);
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
									glDeleteTextures(1, &armorTexture);
									glDisable(GL_TEXTURE_2D);
								}
								else {
									drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
								}
							}
							glPopMatrix();

							glPushMatrix();
							{
								glTranslatef(0.15, -0.45, 0.225);
								glRotatef(145, 1, 0, 0);
								fin();
							}
							glPopMatrix();
						}glPopMatrix();
					}
					glPopMatrix();
				}glPopMatrix();
			}
			glPopMatrix();
		}glPopMatrix();
	}glPopMatrix();
	gluDeleteQuadric(obj);
}

void frontRightHand() {
	GLUquadricObj* obj = gluNewQuadric();
	if (punch) {
		glRotatef(-rightElbowAngle1, 1, 0, 0);
	}
	glPushMatrix();
	{
		glTranslatef(0.145, 0.05, 0.1);
		glRotatef(rightElbowAngle, 0, 1, 0);
		glTranslatef(-0.145, -0.05, -0.1);
		glPushMatrix();
		{
			whiteMaterial();
			glColor3f(1, 1, 1);
			glTranslatef(0.145, 0.05, 0.1);
			glRotatef(90, 1, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
				gluQuadricTexture(obj, true);
				drawCyclinder2(0.115, 0.05, 0.4, 8, 10);
				glDeleteTextures(1, &galaxyTexture);
				glDisable(GL_TEXTURE_2D);
			}
			else {
				drawCyclinder2(0.115, 0.05, 0.4, 8, 10);
			}

		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.145, 0.05, 0.1);
			glRotatef(90, 1, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
				gluQuadricTexture(obj, true);
				drawDisk2(0.0, 0.115, 8, 10);
				glDeleteTextures(1, &galaxyTexture);
				glDisable(GL_TEXTURE_2D);
			}
			else {
				drawDisk2(0.0, 0.115, 8, 10);
			}
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.145, -0.35, 0.1);
			glRotatef(90, 1, 0, 0);
			if (textureOn) {
				galaxyTexture = loadTexture(textureArray[0][textureOption]);
				gluQuadricTexture(obj, true);
				drawDisk2(0.0, 0.05, 8, 10);
				glDeleteTextures(1, &galaxyTexture);
				glDisable(GL_TEXTURE_2D);
			}
			else {
				drawDisk2(0.0, 0.05, 8, 10);
			}
		}
		glPopMatrix();




		//------------------------------------------
		//Palm
		glPushMatrix();
		{
			greyMaterial();
			glColor3f(0.4, 0.4, 0.4);
			glTranslatef(0.110, -0.5, 0.19);
			glRotatef(90, 0, 1, 0);

			//top
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0);            //6
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}
			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0);            //6
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
				glEnd();
			}


			//bottom
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.065);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}
			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.065);
				glEnd();
			}

			//front
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.0);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}

			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.0);
				glEnd();
			}

			//back
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.065);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.056);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}

			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0.065);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0.15, 0.056);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.15, 0.065);
				glEnd();
			}

			//left
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0, 0.15, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.0);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}

			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.15, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0, 0.15, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0, 0.0);
				glEnd();
			}

			//right
			if (textureOn) {
				armorTexture = loadTexture("textures/metal_texture.bmp");
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.175, 0, 0.0);
				glEnd();
				glDeleteTextures(1, &armorTexture);
				glDisable(GL_TEXTURE_2D);
			}

			else {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.175, 0.15, 0.0);
				glTexCoord2f(0.0f, 0.1f); glVertex3f(0.175, 0.15, 0.065);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.175, 0, 0.065);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.175, 0, 0.0);
				glEnd();
			}
		}
		glPopMatrix();

		//Fingers
		//thumb
		glPushMatrix();
		{
			glTranslatef(0.15, -0.5, 0.025);
			glRotatef(rThumbAngle, 0, 1, 0);
			glTranslatef(-0.15, 0.5, -0.025);
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.148, -0.4, 0.025);
				glRotatef(150, 1, 0, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);          //5
					drawCyclinder2(0.02, 0.02, 0.0525, 8, 10);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);

				}
				else {
					drawCyclinder2(0.02, 0.02, 0.0525, 8, 10);
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.15, -0.42, -0.01);
				glRotatef(235, 1, 0, 0);
				fin();
			}
			glPopMatrix();
		}
		glPopMatrix();


		//index finger
		glPushMatrix();
		{
			glTranslatef(0.15, -0.5, -0.045);
			glRotatef(-rIndexAngle, 0, 0, 1);
			glTranslatef(-0.15, 0.5, 0.045);
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.15, -0.475, 0.045);
				glRotatef(90, 1, 0, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.15, -0.54, 0.045);
				glRotatef(180, 1, 0, 0);
				fin();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//middle finger

		glPushMatrix();
		{
			glTranslatef(0.15, -0.5, -0.55);
			glRotatef(-rMiddleAngle, 0, 0, 1);
			glTranslatef(-0.15, 0.5, 0.55);
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.15, -0.475, 0.1);
				glRotatef(90, 1, 0, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.15, -0.54, 0.1);
				glRotatef(180, 1, 0, 0);
				fin();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//Ring finger
		glPushMatrix();
		{
			glTranslatef(0.15, -0.5, -0.55);
			glRotatef(-rRingAngle, 0, 0, 1);
			glTranslatef(-0.15, 0.5, 0.55);
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.15, -0.475, 0.16);
				glRotatef(90, 1, 0, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.15, -0.54, 0.16);
				glRotatef(180, 1, 0, 0);
				fin();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//pinky finger
		glPushMatrix();
		{
			glTranslatef(0.15, -0.6, 0.175);
			glRotatef(-rPinkyAngle, 0, 1, 0);
			glTranslatef(-0.15, 0.6, -0.175);
			glPushMatrix();
			{
				lightGreyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.15, -0.4, 0.175);
				glRotatef(45, 1, 0, 0);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					drawCyclinder2(0.0175, 0.0175, 0.085, 8, 10);
				}
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.15, -0.45, 0.225);
				glRotatef(145, 1, 0, 0);
				fin();
			}
			glPopMatrix();
		}glPopMatrix();
	}glPopMatrix();


}
void righthand() {
	GLUquadricObj* obj = gluNewQuadric();

	glPushMatrix();
	{
		glTranslatef(0.125, 0.5, 0.1);

		glRotatef(rightShoulderAngle, 1, 0, 0);
		glTranslatef(-0.125, -0.5, -0.1);

		glPushMatrix();
		{

			//Shoulder
			glPushMatrix();
			{
				greyMaterial();
				glColor3f(1, 1, 1);
				//TOP
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.125, 0.55, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.125, 0.55, 0.225);
					glEnd();
				}

				//bottom
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.4, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.4, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();

				}


				//left
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);

				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.4, -0.025);
					glEnd();

				}


				//right
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.225, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0.225, 0.4, -0.025);
					glEnd();

				}


				//front 
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, 0.225);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, 0.225);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, 0.225);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, 0.225);
					glEnd();

				}


				//back
				if (textureOn) {
					galaxyTexture = loadTexture(textureArray[0][textureOption]);
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);            //6
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, -0.025);
					glEnd();
					glDeleteTextures(1, &galaxyTexture);
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125, 0.55, -0.025);
					glTexCoord2f(0.0f, 0.1f); glVertex3f(0.125, 0.55, -0.025);            //6
					glTexCoord2f(1.0f, 0.0f); glVertex3f(0.225, 0.4, -0.025);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.4, -0.025);
					glEnd();
				}

			}
			glPopMatrix();

			//---------------------------------
			//joint #1
			glPushMatrix();
			{
				greyMaterial();
				glColor3f(0.7, 0.7, 0.7);
				glTranslatef(0.1, 0.40, 0.1);
				if (textureOn) {
					armorTexture = loadTexture("textures/metal_texture.bmp");
					gluQuadricTexture(obj, true);
					drawSphere(0.1, 50, 50);
					glDeleteTextures(1, &armorTexture);
					glDisable(GL_TEXTURE_2D);
				}

				else {
					drawSphere(0.1, 50, 50);
				}
			}
			glPopMatrix();

			//--------------------------------
			//middle Arm
			glPushMatrix();
			{
				glTranslatef(0.0, 0.15, 0.1);
				glRotatef(punchAngle, 1, 1, 1);
				glTranslatef(-0.0, -0.15, -0.1);
				glPushMatrix();
				{
					glTranslatef(0.15, 0.25, 0.1);
					glRotatef(rightUpperArmAngle, 0, 0, 1);
					glTranslatef(-0.15, -0.25, -0.1);
					glPushMatrix();
					{
						whiteMaterial();
						glColor3f(1, 1, 1);
						glTranslatef(0.1, 0.18, 0.05);
						glRotatef(25, 0, 0, 1);

						//front
						if (textureOn) {
							galaxyTexture = loadTexture(textureArray[0][textureOption]);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.1);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();
							glDeleteTextures(1, &galaxyTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.1);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();

						}


						//back
						if (textureOn) {
							galaxyTexture = loadTexture(textureArray[0][textureOption]);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.0);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.0);
							glEnd();
							glDeleteTextures(1, &galaxyTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.0);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.0);
							glEnd();

						}


						//left
						if (textureOn) {
							galaxyTexture = loadTexture(textureArray[0][textureOption]);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();
							glDeleteTextures(1, &galaxyTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.15, 0.1);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.0, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();

						}


						//right
						if (textureOn) {
							galaxyTexture = loadTexture(textureArray[0][textureOption]);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.15, 0.15, 0.1);     //5
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.15, 0.0, 0.1);
							glEnd();
							glDeleteTextures(1, &galaxyTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.15, 0.15, 0.1);     //5
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.15, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.15, 0.0, 0.1);
							glEnd();

						}


						//bottom
						if (textureOn) {
							galaxyTexture = loadTexture(textureArray[0][textureOption]);
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();
							glDeleteTextures(1, &galaxyTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0, 0.0);
							glTexCoord2f(0.0f, 0.1f); glVertex3f(0.15, 0.0, 0.0);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(0.15, 0.0, 0.1);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0, 0.1);
							glEnd();

						}

					}
					glPopMatrix();
					//------------------------------

					//joint #2
					//First screw
					glPushMatrix();
					{
						greyMaterial();
						glColor3f(0.4, 0.4, 0.4);
						glTranslatef(0.1, 0.17, 0.025);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawCyclinder2(0.06, 0.06, 0.15, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							drawCyclinder2(0.06, 0.06, 0.15, 8, 10);
						}
					}
					glPopMatrix();

					glPushMatrix();
					{
						glTranslatef(0.1, 0.17, 0.175);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawDisk2(0.0, 0.06, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);

						}
						else {
							drawDisk2(0.0, 0.06, 8, 10);
						}
					}
					glPopMatrix();

					glPushMatrix();
					{
						greyMaterial();
						glColor3f(0.4, 0.4, 0.4);
						glTranslatef(0.1, 0.17, 0.025);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawDisk2(0.0, 0.06, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							drawDisk2(0.0, 0.06, 8, 10);
						}
					}
					glPopMatrix();

					//sec Screw
					glPushMatrix();
					{
						greyMaterial();
						glColor3f(0.4, 0.4, 0.4);
						glTranslatef(0.11, 0.08, 0.025);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawCyclinder2(0.045, 0.045, 0.15, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							drawCyclinder2(0.045, 0.045, 0.15, 8, 10);
						}
					}
					glPopMatrix();

					glPushMatrix();
					{
						greyMaterial();
						glColor3f(0.4, 0.4, 0.4);
						glTranslatef(0.11, 0.08, 0.175);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawDisk2(0.0, 0.045, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							drawDisk2(0.0, 0.045, 8, 10);
						}
					}
					glPopMatrix();

					glPushMatrix();
					{
						greyMaterial();
						glColor3f(0.4, 0.4, 0.4);
						glTranslatef(0.11, 0.08, 0.025);
						if (textureOn) {
							armorTexture = loadTexture("textures/metal_texture.bmp");
							gluQuadricTexture(obj, true);
							drawDisk2(0.0, 0.045, 8, 10);
							glDeleteTextures(1, &armorTexture);
							glDisable(GL_TEXTURE_2D);
						}
						else {
							drawDisk2(0.0, 0.045, 8, 10);
						}
					}
					glPopMatrix();

					glPushMatrix();
					{
						drawCurveCylinder(0.05, 0.03, 255, 160, 100);   //1
					}
					glPopMatrix();
					glPushMatrix();
					frontRightHand();
					glPopMatrix();

				}
				glPopMatrix();
			}glPopMatrix();
		}
		glPopMatrix();
	}glPopMatrix();
	gluDeleteQuadric(obj);
}
#pragma endregion
void background() {
	yellowMaterial();
	glColor3f(1, 1, 0);
	if (textureOn) {
		armorTexture = loadTexture("textures/galaxy_background2.bmp");
	}

	glPushMatrix();
	{
		glRotatef(backgroundDegree, 0, 1, 0);
		glPushMatrix();
		{
			glTranslatef(0, 25.0f, 0);

			glRotatef(90, 1, 0, 0);
			drawCyclinder(10, 10, 50);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);

	if (textureOn) {
		armorTexture = loadTexture("textures/galaxy_background.bmp");
	}

	glPushMatrix();
	{
		glTranslatef(0, 25.0f, 0);

		glRotatef(90, 1, 0, 0);
		drawDisk(0, 5);
	}
	glPopMatrix();

	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);

//	glColor3f(0, 0.5, 0.5);
	if (textureOn) {
		armorTexture = loadTexture("textures/moon_texture.bmp");
	}

	glPushMatrix();
	{
		glTranslatef(-0.3, -5.0f, 0);

		drawSphere(3,50,50);
	}
	glPopMatrix();
	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);
}
#pragma region LIGHTING MATERIAL
//Lighting Material
void greyMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grey);
}
void lightGreyMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightGrey);
}
void redMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red);
}
void blackMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, darkGrey);
}
void yellowMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellow);
}
void whiteMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
}
void orangeMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, orange);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, orange);
}
#pragma endregion

void lightning() {


	if (lightningOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}



	if (isDiffuse) {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);			//assign diffuse 
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightClose);
	}
	if (isAmbient) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);			//assign ambient 
	}
	else {
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightClose);
	}
	if (isSpecular) {
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);			//assign ambient 
	}
	else {
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightClose);
	}

	GLfloat lightPosition[4] = { positionX, positionY, positionZ, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);		//assign position of the light
}
void setupView() {

	if (isPerspective) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(80.0, 1.0, 0.5, 21.0);
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 11.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void drawWholeMachine() {
	glPushMatrix();
	{
		//glTranslatef(xPosition, yPosition, -zPosition);
		glRotatef(bodyAngle, 0, 1, 0);
		glTranslatef(xPosition, yPosition, -zPosition);
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(-0.2, -1.5, 3.5);
				glScalef(4.0, 3, 3);
				glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

				glPushMatrix();
				{
					glTranslatef(0, 0.9, 0);
					glRotatef(headDegree, 0, 1, 0);
					glTranslatef(0, -0.9, 0);
					head();
					neck();
				}
				glPopMatrix();

				glPushMatrix();
				{
					body();		//Right
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(-1, 1, 1);
					body();		//Left
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(1.7, -1.8, 4);
				glScalef(3, 3, 3);
				glRotatef(180, 1, 0, 0);
				lefthand(); //left hand
			}
			glPopMatrix();
			glPushMatrix(); {
				if (!laserBall) {
					glTranslatef(0, 0, -shootBall);
				}


				if (laserBall) {
					glPushMatrix();
					{
						glTranslatef(0, 0, shootBall);
						/*
									glPushMatrix();
									{*/
						glTranslatef(-0.2, -2.7, 2.6);// -0.18
						glScalef(size, size, size);
						createLaserBall();
						/*	}
							glPopMatrix();*/
					}
					glPopMatrix();

					if (size < 30) {
						size += 0.1f;
					}

					if (size >= 30) {
						shootBall -= 0.1f;
					}

					if (shootBall < -5.0f) {
						laserBall = false;
						shootBall = 0;
						size = 0;
					}

				}

			}
			glPopMatrix();
			glPushMatrix();
			{

				if (jetDegree >= 150) {
					glRotatef(180, 0, 0, 1);
					glTranslatef(0.215, 2, 3.3);
					glPushMatrix(); {
						glTranslatef(-0.215, 0, 0);
						glScalef(3, 3, 3);
						displayFire();
					}
					glPopMatrix();
					glPushMatrix();
					{
						glTranslatef(0.2, 0, 0);
						glScalef(-3, 3, 3);
						displayFire();
					}
					glPopMatrix();
				}
			}
			glPopMatrix();

			glPushMatrix();
			{
				glScalef(-1, 1, 1);
				glTranslatef(2.1, -1.8, 4);
				glScalef(3, 3, 3);
				glRotatef(180, 1, 0, 0);


				righthand(); //right hand

			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0, -1.2, 3.4);
				glScalef(1.5, 1.2, 1.5);
				waist();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, -0.7, 3.1);
				glPushMatrix();
				{
					glTranslatef(-1, 0, 0);
					glPushMatrix();
					{
						glTranslatef(0.08, -0.5, 0.3); //Switch origin to prefered rotate point.
						glRotatef(rightLegAngle, rightLegAxis[0][0], rightLegAxis[0][1], rightLegAxis[0][2]); //Rotating joint.

						glRotatef(180, 1, 0, 0);
						glTranslatef(-0.08, 0.5, -0.3); //Switch origin to prefered rotate point.
						//glTranslatef(0.08, -0.5, 0.3);
						//glRotatef(-rightLegAngle, 1, 0, 0);
						//glRotatef(rightLegAngle, rightLegAxis[0][0], rightLegAxis[0][1], rightLegAxis[0][2]); //Rotating joint.
						//glTranslatef(-0.08, 0.5, -0.3);

						drawRightLeg();		//Right
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.55, 0, 0);
					glPushMatrix();
					{
						glTranslatef(0.08, -0.5, 0.3); //Switch origin to prefered rotate point.
						glRotatef(leftLegAngle, leftLegAxis[0][0], leftLegAxis[0][1], leftLegAxis[0][2]);  //Rotating joint.

						glRotatef(180, 1, 0, 0);
						glTranslatef(-0.08, 0.5, -0.3); //Switch origin to prefered rotate point.

						//glTranslatef(0.08, -0.5, 0.3);
						//glRotatef(-leftLegAngle, 1, 0, 0);
						//glRotatef(leftLegAngle, leftLegAxis[0][0], leftLegAxis[0][1], leftLegAxis[0][2]); //Rotating joint.
						//glTranslatef(-0.08, 0.5, -0.3);
						drawLeftLeg();		//Left
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void display()														// to display
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0, 1, 250 / 255, 0.0f);							// to change the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupView();

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, zoomLevel);
	//texture
	glEnable(GL_TEXTURE_2D);
	lightning();
	glEnable(GL_LIGHT0);
	
	//background
	if (!onBackground) {
		background();
	}
	//-----------------------------------------------
	//Control the view
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	//-----------------------------------------------


	drawWholeMachine();







	glPopMatrix();
	glFlush();	//Empty all GL buffers.

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)   //WinMain is same as the main in C
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);                                // The window size

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------
	//
	glEnable(GL_DEPTH_TEST);		//To tell the compiler we need to do the 3d.
	ShowWindow(hWnd, nCmdShow);


	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)											//Important part(the code)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		display();

		if (jetWeapon == true) {
			if (jetDegree <= 150)
				jetDegree += 0.5f;

			if (jetDegree >= 179) {
				smokeTranslate -= 0.0001f;		//let the smoke go down

				if (smokeTranslate > 0.01) {}
				//disable the smoke
			}
		}
		else {
			if (jetDegree >= 0)
				jetDegree -= 0.5f;
		}

		//rotating the energy core
		degreeReactor += 3.0f;
		//rotating the background
		backgroundDegree += 0.8f;
		//rotating the energy core
		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
