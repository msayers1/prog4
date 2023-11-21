//
//  main.cpp
//  Week 10 - 3D Objects
//
//	This one does the standard computer graphics setup of
//	a 3D scene.
//
//  Created by Jean-Yves Hervé on 2023-10-30.
//

#include <vector>
#include <memory>
#include <iostream>
#include "drawingUtilities.h"
#include "filemanagement.h"
#include "common.h"
#include "Quad3D.h"
#include "QuadMesh3D.h"
#include "Cylinder3D.h"
#include "Sphere3D.h"
#include "House3D.h"

using namespace std;
// using namespace graphics3d;

void drawOrbit(void);
void cameraToWorld(void);
void setupCamera(void);
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseFunc(int b, int s, int x, int y);
void myKeyboardFunc(unsigned char c, int x, int y);
void mySpecialKeyHandler(int key, int x, int y);
void myTimerFunc(int dt);
void myInit(void);


//	Camera intrinsic parameters
// float		gFoV = 45.f,			//	vertical field of view in degree
// 			gNearZ = 1.0f,			//	Position of the clipping planes along the camera's
// 			gFarZ = 50.0f;			//		optical axis (Z axis)
float		gFoV = 45.f,			//	vertical field of view in degree
			gNearZ = 1.0f,			//	Position of the clipping planes along the camera's
			gFarZ = 50.0f;			//		optical axis (Z axis)
			

//	Camera to world transformation (extrinsic parameters)
// float		gTx = 0.25f,
// 			gTy = -0.2f,
// 			gTz = -2.f,
// 			gRoll = 0.0f,
// 			gPitch =-60.f,
// 			gYaw = 10.f;
// float		gTx = 0.0f,
// 			gTy = 1.f,
// 			gTz = -3.f,
// 			gRoll = 15.0f,
// 			gPitch =-80.f,
// 			gYaw = 120.f;
// Sphere Translation
float		gTx = 1.0f,
			gTy = 1.0f,
			gTz = -3.f,
			gRoll = 10.0f,
			gPitch =-80.f,
			gYaw = 105.f;


RenderingMode renderingMode = RenderingMode::SmoothShadingRender;

bool		drawReferenceFrames = false;

int			winWidth = 1200, winHeight = 900;

		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat emission[4];
		GLfloat shiny;


//	ambient, diffuse, specular, emission

Material gray1{0.7f, 0.7f, 0.7f, 1.f, 0.7f, 0.7f, 0.7f, 1.f, 0.7f, 0.7f, 0.7f, 1.f,
				0.7f, 0.7f, 0.7f, 1.f, 0.3f};
Material gray2{0.3f, 0.3f, 0.3f, 1.f, 0.3f, 0.3f, 0.3f, 1.f, 0.3f, 0.3f, 0.3f, 1.f,
				0.2f, 0.2f, 0.2f, 1.f, 0.3f};
				
Material red1{0.9f, 0.1f, 0.1f, 1.f, 0.9f, 0.1f, 0.1f, 1.f, 0.9f, 0.1f, 0.1f, 1.f,
				0.2f, 0.1f, 0.1f, 1.f, 0.3f};
Material specRed1{0.9f, 0.1f, 0.1f, 1.f, 0.4f, 0.05f, 0.05f, 1.f, 0.9f, 0.2f, 0.2f, 1.f,
				0.2f, 0.0f, 0.0f, 1.f, 0.6f};
vector<shared_ptr<GraphicObject3D> > objList;


//	Move from the camera to the world reference frame:  Start from the camera and apply
//	a series of transformations to end up in the world reference frame, where the drawing
//	will take place
void cameraToWorld(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//	Move to the origin of the world reference frame
	glTranslatef(gTx, gTy, gTz);
	//	Apply rotations.  Here Roll, Yaw, Pitch
	glRotatef(gRoll, 0.0, 0.0, 1.0);
	glRotatef(gYaw, 0.0, 1.0, 0.0);
	glRotatef(gPitch, 1.0, 0.0, 0.0);
}


void myDisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Move from the camera to the world reference frame
	cameraToWorld();
	
	glPushMatrix();

	//	Now I am in the world reference frame.
	//	I draw axes so that we can see what the local frame looks like.
	if (drawReferenceFrames)
		drawReferenceFrame();
	
	for (auto obj : objList)
		obj->draw();
		
	//	back to camera reference frame
	glPopMatrix();

	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}

//	This callback function is called when the window is resized
//	(generally by the user of the application).
//
void myResizeFunc(int w, int h)
{
	winWidth = w;
	winHeight = h;
	
	//	update projection transformations
	glViewport(0, 0, w, h);
	
	// the aspect ratio probably changed, so we need to update
	//	the camera
	setupCamera();
	
	//	When it's done, request a refresh of the display
	glutPostRedisplay();
}


//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseFunc(int b, int s, int x, int y)
{
	switch (b)
	{
		case GLUT_LEFT_BUTTON:
			if (s == GLUT_DOWN)
			{
				//	do something
			}
			else if (s == GLUT_UP)
			{
				// do something else
			}
			break;


		default:
			break;
	}
}

//	This callback function is called when a keyboard event occurs
//
void myKeyboardFunc(unsigned char c, int x, int y)
{
	std::cout << "regular key" <<  c << std::endl;
	switch (c)
	{
		case 'q':
		case 27:
			exit(0);
			break;

		//	Toggles on/off rendering the reference frames
		case 'r':
		case 'R':
			drawReferenceFrames = !drawReferenceFrames;
			break;
			
		//	Toggles on/off wireframe mode
		// case 'w':
		case 'W':
			switch(renderingMode)
			{
				//	If we were in wireframe mode, we switch to flat shading
				case RenderingMode::WireframeRender:
					renderingMode = RenderingMode::FlatShadingRender;
					break;
				//	Else we switch to wireframe
				case RenderingMode::FlatShadingRender:
				case RenderingMode::SmoothShadingRender:
					renderingMode = RenderingMode::WireframeRender;
					break;
			}
			updateRenderingMode(renderingMode);
			glutPostRedisplay();
			break;
			

		//	Toggles on/off the Flat shading model
		case 'f':
		case 'F':
			switch(renderingMode)
			{
				//	If we were in wireframe mode or smooth shading mode,
				//	we switch to flat shading
				case RenderingMode::WireframeRender:
				case RenderingMode::SmoothShadingRender:
					renderingMode = RenderingMode::FlatShadingRender;
					break;

				//	Else, we switch from flat to smooth shading
				case RenderingMode::FlatShadingRender:
					renderingMode = RenderingMode::SmoothShadingRender;
					break;
			}				
			updateRenderingMode(renderingMode);
			glutPostRedisplay();
			break;

		//	Toggles on/off the Smooth shading model
		case 's':
		case 'S':
			switch(renderingMode)
			{
				//	If we were in wireframe mode or flat shading mode,
				//	we switch to smooth shading
				case RenderingMode::WireframeRender:
				case RenderingMode::FlatShadingRender:
					renderingMode = RenderingMode::SmoothShadingRender;
					break;

				//	else we switch from smooth to flat shading
				case RenderingMode::SmoothShadingRender:
					renderingMode = RenderingMode::FlatShadingRender;
					break;
			}				
			updateRenderingMode(renderingMode);
			glutPostRedisplay();
			break;
	
		case '8':
			gPitch += 5.f;
			cout << "gPitch = " << gPitch << endl;
			break;
		case '2':
			gPitch -= 5.f;
			cout << "gPitch = " << gPitch << endl;
			break;
		case '4':
			gYaw += 5.f;
			cout << "gYaw = " << gYaw << endl;
			break;
		case '6':
			gYaw -= 5.f;
			cout << "gYaw = " << gYaw << endl;
			break; 
		case '7':
			gTy += 1.f;
			cout << "gTy = " << gTy << endl;
			break;
		case '3':
			gTy -= 1.f;
			cout << "gTy = " << gTy << endl;
			break;
		case '9':
			gRoll += 5.f;
			cout << "gRoll = " << gRoll << endl;
			break;
		case '1':
			gRoll -= 5.f;
			cout << "gRoll = " << gRoll << endl;
			break;	
		case 'w':
			gTz += 1.f;
			cout << "gTz = " << gTz << endl;
			break;
		case 'x':
			gTz -= 1.f;
			cout << "gTz = " << gTz << endl;
			break;
		case 'a':
			gTx += 1.f;
			cout << "gTx = " << gTx << endl;
			break;
		case 'd':
			gTx -= 1.f;
			cout << "gTx = " << gTx << endl;
			break; 
			
			

		case 'y':
		case 'Y':
			gNearZ *= 0.9f;
			setupCamera();
			cout << "nearZ = " << gNearZ << endl;
			break;

		case 'h':
		case 'H':
			gNearZ *= 1.1f;
			setupCamera();
			cout << "nearZ = " << gNearZ << endl;
			break;
			
		case 'u':
		case 'U':
			gFarZ *= 0.9f;
			setupCamera();
			cout << "farZ = " << gFarZ << endl;
			break;

		case 'j':
		case 'J':
			gFarZ *= 1.1f;
			setupCamera();
			cout << "farZ = " << gFarZ << endl;
			break;
		// float		gFoV = 45.f,			//	vertical field of view in degree
		// gNearZ = 1.0f,			//	Position of the clipping planes along the camera's
		// gFarZ = 50.0f;			//		optical axis (Z axis)
		// float		gTx = 0.25f,
		// 			gTy = -0.2f,
		// 			gTz = -2.f,
		// 			gRoll = 0.0f,
		// 			gPitch =-60.f,
		// 			gYaw = 10.f;
		case 'p':
			cout << "gFov | gNearZ |  gFarZ | gTx | gTy | gTz | gRoll | gPitch | gYaw "  
			 << gFoV << " | " << gNearZ << " | " <<  gFarZ << " | " << gTx << " | " << gTy 
			 << " | " << gTz << " | " << gRoll << " | " << gPitch << " | " << gYaw << endl;
			break;
		default:
			break;
	}
}


void mySpecialKeyHandler(int key, int x, int y)
{
	std::cout << "special key" <<  key << std::endl;
	//Use the arrow keys to control the camera pitch is up/down and yaw is left/right.
	switch(key){
		case GLUT_KEY_UP:
			gPitch += 5.f;
			cout << "gPitch = " << gPitch << endl;
			break;
		case GLUT_KEY_DOWN:
			gPitch -= 5.f;
			cout << "gPitch = " << gPitch << endl;
			break;
		case GLUT_KEY_LEFT:
			gYaw -= 5.f;
			cout << "gYaw = " << gYaw << endl;
			break;
		case GLUT_KEY_RIGHT:
			gYaw += 5.f;
			cout << "gYaw = " << gYaw << endl;
			break; 
	}
}


//	This function is called after (at least) the specified time has ellapsed
//	since it was last "primed" (pushed back on the queue).
//
void myTimerFunc(int dt)
{
	//	Set up next timer event
	glutTimerFunc(10, myTimerFunc, 0);

	glutPostRedisplay();
}


void myInit(void)
{
	GLfloat		ambientLight[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat		diffuseLight[] = {1.0, 1.0, 1.0, 0.5};
	GLfloat		positionLight[] = {0.0, -3.0, 3.0, 0.0};

	GLfloat		lmodel_ambientLight[] = {0.2, 0.2, 0.2, 0.5};
	GLfloat		local_view[] = {0.0};

	// GLfloat		ambientLight[] = {0.5, 0.5, 0.5, 1.0};
	// GLfloat		diffuseLight[] = {1.0, 1.0, 1.0, 1.0};
	// GLfloat		positionLight[] = {0.0, -3.0, 3.0, 0.0};

	// GLfloat		lmodel_ambientLight[] = {0.2, 0.2, 0.2, 1.0};
	// GLfloat		local_view[] = {0.0};




	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, positionLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambientLight);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	updateRenderingMode(renderingMode);

	//	 replaces the gluOrtho2D call.
	setupCamera();
	
	//	create a quad object
	// objList.push_back(make_shared<Quad3D>(1.f, 1.5f, Pose{-1.f, 0.f, 0.f, 15.f, 0.f, -15.f}));
	// objList.push_back(make_shared<QuadMesh3D>(1.f, 1.5f, 6, 8, Pose{-0.25f, 0.2f, 0.f, -15.f, 0.f, 15.f}));
	// objList.push_back(make_shared<QuadMesh3D>(1.f, 1.5f, 6, 8, 0.10f, Pose{0.f, -0.f, 0.f, 0.f, 0.f, 0.f}));
	// objList.push_back(make_shared<Sphere3D>(0.5f, 0.5f, 0.5f, 16, 32, Pose{0.f, 1.f, -1.0f, 0.f, 0.f, 0.f}));
	// objList.push_back(make_shared<Cylinder3D>(0.5f, 0.5f, 1.f, 12, 8, true, Pose{0.f, 1.f, -1.0f, 0.f, 0.f, 0.f}));
	// objList.push_back(make_shared<House3D>("houseOutofBlenderWithTexture.obj", "./", 1.f, 1.f, 1.f, Pose{-0.25f, 0.2f, 0.f, -15.f, 0.f, 15.f}));
	objList.push_back(make_shared<House3D>("houseOutofBlender.obj", "./", .25f, .25f, .25f, Pose{0.f, 1.f, -1.f, 0.f, 0.f, 0.f}));
	// std::map<std::string, MaterialData> material =  processMaterialDataFile("../test.mtl");

	// for(auto& obj : objList){
	// 	obj->setMaterial(gray2);
	// }
}

void setupCamera(void)
{
	glMatrixMode(GL_PROJECTION );
	glLoadIdentity();

	float foVxy = 1.0f * winWidth / winHeight;
	
		//	vertical field   hor to vert ratio
		//	of view
	gluPerspective(gFoV, foVxy, gNearZ, gFarZ);
	glMatrixMode( GL_MODELVIEW );
}


int main(int argc, char** argv)
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 40);
	glutCreateWindow("3D Graphic objects Demo");
	
	//	set up the callbacks
	glutDisplayFunc(myDisplayFunc);
	glutReshapeFunc(myResizeFunc);
	glutMouseFunc(myMouseFunc);
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyHandler);
	glutTimerFunc(10, myTimerFunc, 0);
	
	//	Now we can do application-level
	myInit();

	//	Now we enter the main loop of the program and to a large extend
	//	"loose control" over its execution.  The callback functions that 
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();
	
	//	This will never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}
