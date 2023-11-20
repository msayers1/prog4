//
//  drawingUtilities.h.h
//  Version1
//
//  Created by Jean-Yves Hervé on 2023-10-30.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "glPlatform.h"
#include "common.h"
#include "filemanagement.h"
// namespace graphics3d
// {
	//	Rendering modes
	//
	enum class RenderingMode
	{
			WireframeRender,
			FlatShadingRender,
			SmoothShadingRender
	};

	union Material
	{
		GLfloat aMaterial[17];

		struct SMaterial{
			GLfloat ambient[4];
			GLfloat diffuse[4];
			GLfloat specular[4];
			GLfloat emission[4];
			GLfloat shiny;
		}sMaterial;
		
		Material(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat emission[4], GLfloat shiny ):sMaterial{*ambient, *diffuse, *specular, *emission, shiny}{}
		Material():aMaterial{0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f}{}
		Material(float ambientR,float ambientG,float ambientB,float ambientD,float diffuseR,float diffuseG,
					float diffuseB,float diffuseD,float specularR,float specularG,float specularB,float specularD,float emissionR,
					float emissionG,float emissionB, float emissionD,float Shiny):aMaterial{ambientR, ambientG, ambientB, ambientD,
					diffuseR, diffuseG, diffuseB, diffuseD, specularR, specularG, specularB, specularD, emissionR,
					emissionG, emissionB, emissionD, Shiny}{}
	};
	
	void setCurrentMaterial(MaterialData material);
	// void setCurrentMaterial(GLfloat ambRed, GLfloat ambGreen, GLfloat ambBlue, GLfloat difRed,
	// 	GLfloat difGreen, GLfloat difBlue, GLfloat specRed, GLfloat specGreen,
	// 	GLfloat specBlue, GLfloat shine);
	void setCurrentMaterial(RGB ambientRGB, RGB diffuseRGB, RGB specularRGB, RGB emissionRGB, GLfloat shiny, GLfloat illum, GLfloat opaqueness, GLfloat opticalDensity);

	void setCurrentMaterial(const Material& mat);

	//void saveAndSetMaterial(Material& currentMat, const Material& newMat);

	void updateRenderingMode(RenderingMode renderingMode);

	void drawReferenceFrame(void);
// }

#endif //	UTILITIES_H
