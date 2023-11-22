//
//  Cone3D.h
//
//
//  Created by Michael Sayers from Jean Herve's Cylinder.
//

#ifndef CONE_3D_H
#define CONE_3D_H

#include <memory>
#include "GraphicObject3D.h"

// namespace graphics3d
// {
	/**	I define my cylinders as elliptic rings (radiusX, radiusZY)
	 *	stacked along the local Z axis.
	 *	I also define a static "unit" cylinder that can be used
	 *	as ready-made part for any complex object.
	 */
	class Cone3D : public GraphicObject3D
	{
		private:
		
			float radiusX_;
			float radiusY_;
			float height_;
			unsigned int numCirclePts_;
			unsigned int numRings_;
			bool isClosed_;
			//	Switching back to a pointer, but I make it a 3D array
			//	numCirclePts_ x (numRings_+1) x 3
			GLfloat*** XYZ_;
			GLfloat** normals_;
			GLfloat* topNormal_;
			GLfloat* bottomNormal_;
			
			const static std::shared_ptr<Cone3D> UNIT_CYLINDER_OPEN;
			const static std::shared_ptr<Cone3D> UNIT_CYLINDER_CLOSED;

			void initMeshAndNormals_();
			
		public:
		
			Cone3D(float radiusX, float radiusY, float height,
						unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			Cone3D(float radius, unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~Cone3D();
			
			Cone3D(const Cone3D& obj) = delete;
			Cone3D& operator =(const Cone3D& obj) = delete;
			Cone3D(Cone3D&& obj) = delete;
			Cone3D& operator =(Cone3D&& obj) = delete;
			Cone3D() = delete;

			void draw() const;
			
			inline float getRadiusX()
			{
				return radiusX_;
			}
			
			inline float getRadiusY()
			{
				return radiusY_;
			}
			inline float getHeight()
			{
				return height_;
			}			
			static const std::shared_ptr<Cone3D> getOpenUnitCylinder()
			{
				return UNIT_CYLINDER_OPEN;
			}
			static const std::shared_ptr<Cone3D> getClosedUnitCylinder()
			{
				return UNIT_CYLINDER_CLOSED;
			}
			
//			void displaceVertex(unsigned int row, unsigned int col, float dZ);

	};
// }

#endif //	CONE_3D_H
