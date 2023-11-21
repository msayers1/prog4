//
//  Sphere3D.h
//
//
//  Created by Michael Sayers from Jean Herve's Cylinder.
//

#ifndef SPHERE_3D_H
#define SPHERE_3D_H

#include <memory>
#include "GraphicObject3D.h"

// namespace graphics3d
// {
	/**	I define my cylinders as elliptic rings (radiusX, radiusZY)
	 *	stacked along the local Z axis.
	 *	I also define a static "unit" cylinder that can be used
	 *	as ready-made part for any complex object.
	 */
	class Sphere3D : public GraphicObject3D
	{
		private:
		
			float radiusX_;
			float radiusY_;
			float radiusZ_;
			unsigned int numRingsXY_;
			unsigned int numRingsYZ_;
			//	Switching back to a pointer, but I make it a 3D array
			//	numCirclePts_ x (numRings_+1) x 3
			GLfloat*** XYZ_;
			GLfloat*** normals_;

			void initMeshAndNormals_();
			
		public:
		
			Sphere3D(float radiusX, float radiusY, float radiusZ,
						unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			Sphere3D(float radius, unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~Sphere3D();
			
			Sphere3D(const Sphere3D& obj) = delete;
			Sphere3D& operator =(const Sphere3D& obj) = delete;
			Sphere3D(Sphere3D&& obj) = delete;
			Sphere3D& operator =(Sphere3D&& obj) = delete;
			Sphere3D() = delete;

			void draw() const;
			
			inline float getRadiusX()
			{
				return radiusX_;
			}
			
			inline float getRadiusY()
			{
				return radiusY_;
			}
			inline float getRadiusZ()
			{
				return radiusZ_;
			}			
			
//			void displaceVertex(unsigned int row, unsigned int col, float dZ);

	};
// }

#endif //	SPHERE_3D_H
