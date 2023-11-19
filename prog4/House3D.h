//
//  House3D.h
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#ifndef HOUSE_3D_H
#define HOUSE_3D_H

#include <memory>
#include "GraphicObject3D.h"

namespace graphics3d
{
	/**	I define my cylinders as elliptic rings (radiusX, radiusZY)
	 *	stacked along the local Z axis.
	 *	I also define a static "unit" cylinder that can be used
	 *	as ready-made part for any complex object.
	 */
	class House3D : public GraphicObject3D
	{
		private:
		
			float width_;
            float height_;
			
            void initMeshAndNormals_(ObjectFile mesh);

			std::vector<FaceLiteral> faceList_;
			
		public:
		
			House3D(std::string filename, float width, float height,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~House3D();
			
			House3D(const House3D& obj) = delete;
			House3D& operator =(const House3D& obj) = delete;
			House3D(House3D&& obj) = delete;
			House3D& operator =(House3D&& obj) = delete;
			House3D() = delete;

			void draw() const;
			
			inline float getWidth()
			{
				return width_;
			}
			inline float getHeight()
			{
				return height_;
			}
				
	};
}

#endif //	HOUSE_3D_H
