//
//  drawingUtilities.cpp
//  Version1
//
//  Created by Jean-Yves Hervé on 2023-10-30.
//

#include "drawingUtilities.h"
// using namespace graphics3d;
extern bool drawReferenceFrames;


//	 Allows to define the reflectance properties of the current object's material
void setCurrentMaterial(GLfloat ambRed, GLfloat ambGreen, GLfloat ambBlue, GLfloat difRed,
	GLfloat difGreen, GLfloat difBlue, GLfloat specRed, GLfloat specGreen,
	GLfloat specBlue, GLfloat shine)
{
	GLfloat ambient[4] = {ambRed, ambGreen, ambBlue, 1.f};
	GLfloat diffuse[4] = {difRed, difGreen, difBlue, 1.f};
	GLfloat specular[4] = {specRed, specGreen, specBlue, 1.f};
	GLfloat emission[4] = {0.f, 0.f, 0.f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.f);
}

void setCurrentMaterial(MaterialData material)
{
	RGB ambientRGB = material.Ka_;
	RGB diffuseRGB = material.Kd_;
	RGB specularRGB = material.Ks_;
	RGB emissionRGB = material.Ke_;
	GLfloat shiny = material.Ns_; 
	GLfloat illum = material.illum_;
	GLfloat opaqueness = material.d_;
	GLfloat opticalDensity = material.Ni_;
	//Leaving illum and optical Density if needed later. 
	GLfloat ambient[4] = {ambientRGB.rgb.R, ambientRGB.rgb.G, ambientRGB.rgb.B, opaqueness};
	GLfloat diffuse[4] = {diffuseRGB.rgb.R, diffuseRGB.rgb.G, diffuseRGB.rgb.B, opaqueness};
	GLfloat specular[4] = {specularRGB.rgb.R, specularRGB.rgb.G, specularRGB.rgb.B, opaqueness};
	GLfloat emission[4] = {emissionRGB.rgb.R, emissionRGB.rgb.G, emissionRGB.rgb.B, opaqueness};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shiny * 128.f);
	if(material.texture_ != 0){
		// std::cout << "here" << std::endl;
		glBindTexture(GL_TEXTURE_2D, material.texture_);
	}
}

void setCurrentMaterial(const Material& mat)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.aMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.aMaterial+4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.aMaterial+8);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat.aMaterial+12);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.aMaterial[16] * 128.f);
}

//void saveAndSetMaterial(Material& currentMat, const Material& newMat)
//{
//	glGetMaterialfv(GL_FRONT,  GL_AMBIENT,  currentMat.sMaterial.ambient);
//	glGetMaterialfv(GL_FRONT,  GL_DIFFUSE,  currentMat.sMaterial.diffuse);
//	glGetMaterialfv(GL_FRONT,  GL_SPECULAR,  currentMat.sMaterial.specular);
//	glGetMaterialfv(GL_FRONT,  GL_EMISSION,  currentMat.sMaterial.emission);
//	glGetMaterialfv(GL_FRONT,  GL_SPECULAR,  &(currentMat.sMaterial.shiny));
//
//	setMaterial(newMat);
//}

void updateRenderingMode(RenderingMode renderingMode)
{
	switch(renderingMode)
	{
		//	If we were in wireframe mode, we switch to flat shading
		case RenderingMode::WireframeRender:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glShadeModel(GL_FLAT);
 			break;
		//	Else we switch to wireframe
		case RenderingMode::FlatShadingRender:
			glPolygonMode(GL_FRONT, GL_FILL);
			glShadeModel(GL_FLAT);
			break;

		case RenderingMode::SmoothShadingRender:
			glPolygonMode(GL_FRONT, GL_FILL);
			glShadeModel(GL_SMOOTH);
			break;
	}
}

//	Draws the three axes of the local reference frame
void drawReferenceFrame(void)
{
	if (drawReferenceFrames)
		glBegin(GL_LINES);
			//	X --> red.
			setCurrentMaterial(1.0, 0., 0., 1., 0., 0., 0., 0., 0., 0.);
			glVertex3f(-0.1, 0., 0.);
			glVertex3f(0.5, 0., 0.);
			//	Y --> green
			setCurrentMaterial(0., 0., 1.0, 0., 0., 1., 0., 0., 0., 0.);
			glVertex3f(0., -0.1, 0.);
			glVertex3f(0., 0.5, 0.);
			//	Z --> blue
			setCurrentMaterial(0., 1.0, 0., 0., 1., 0., 0., 0., 0., 0.);
			glVertex3f(0., 0., -0.1);
			glVertex3f(0., 0., 0.5);
		glEnd();
}

