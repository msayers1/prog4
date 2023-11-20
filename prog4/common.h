/*==================================================================================+
#	File:		common.h															#
#																					#
#	Contains a few constant and type definitions									#
#																					#
+==================================================================================*/

#ifndef COMMON_H
#define COMMON_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <map>
#include <string>
#include "glPlatform.h"
// #include "filemanagement.h"
// namespace graphics3d
// {
	
	//----------------------------------------------------------------------------------
	//------------------------------------- Constants ----------------------------------
	//
	//	Classical numerical constants
	#ifndef M_PI
	#define M_PI	3.14159265358979   // M_PI is not a part of standard C++ anymore [???]
	#endif
	#ifndef	PI
	#define	PI		M_PI
	#endif
	#define	TWO_PI			6.28318530717858
	#define PI_DIV_2		1.5707963267949
	#define ONE_DIV_PI		0.31830988618379
	#define ONE_DIV_2PI		0.1591549430919
	//
	#define RAD_TO_DEG		57.29577951308232
	#define DEG_TO_RAD		 0.017453292519943
	//
	#define ASCII_BELL      0x07
	#define ASCII_BS        0x08
	#define ASCII_LF        0x0A
	#define ASCII_CR        0x0D
	#define ASCII_XON       0x11
	#define ASCII_XOFF      0x13


	//----------------------------------------------------------------------------------
	//------------------------------------- Macros ----------------------------------
	//
	#define		MOD(a, b)	((a) >= 0 ? (a)%(b) : (a)%(b) + (b))

	//----------------------------------------------------------------------------------
	//----------------------------------- Custom Types ---------------------------------

	typedef unsigned char byte;



	//	Object (incl. camera) 6D pose data structure
	//
	struct Pose
	{
		float	tX, tY, tZ,				//	position
				roll, pitch, yaw;		//	Yaw-Pitch-Roll angles
	};
	using PosePtr = Pose*;

	struct Motion
	{
		float	vX, vY, vZ,				//	velocity vector
				spinX, spinY, spinZ;	//	Yaw-Pitch-Roll angles

		static const Motion NULL_MOTION;
	};


	//	Point 3D coordinates
	//
	union Point3D
	{
		struct sPoint3D
		{
			GLfloat	X,
					Y,
					Z;
		}point3D;
		
		GLfloat aPoint3D[3];

		Point3D():aPoint3D{0.f,0.f,0.f}{};
		Point3D(GLfloat x,GLfloat y,GLfloat z ):aPoint3D{x,y,z}{};
	};





	//	Point using homogeneous coordinates
	//
	union Point4D
	{
		struct sPoint4D
		{
			GLfloat	X,
					Y,
					Z,
					w;
		};
		
		GLfloat aPoint4D[4];
	};

// }
#endif
