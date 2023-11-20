//
//  House3D.h
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#ifndef HOUSE_3D_H
#define HOUSE_3D_H

#include <memory>
#include <string>
#include <vector>
#include <map>
// #include "common.h"
// #include "filemanagement.h"
#include "GraphicObject3D.h"

// namespace graphics3d
// {
	/**	I define my cylinders as elliptic rings (radiusX, radiusZY)
	 *	stacked along the local Z axis.
	 *	I also define a static "unit" cylinder that can be used
	 *	as ready-made part for any complex object.
	 */
	class House3D : public GraphicObject3D
	{
		private:
		
			float scaleX_, scaleY_, scaleZ_;
			
            void initHouseMeshAndNormals_(ObjectFile mesh);

			std::vector<GroupLiteral> groupList_;		
			// Commented out since I moved it to the MaterialData Structure
			// GLuint texture_;
			// Each Group will have its Material Data. 
			// std::map<std::string, MaterialData>* materialData_;
			
		public:
		
			House3D(std::string filename, std::string directory, float scaleX, float scaleY, float scaleZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			House3D(std::string filename, float scaleX, float scaleY, float scaleZ,
						const Pose& pose, const Motion& motion = Motion::NULL_MOTION);

			~House3D();
			
			House3D(const House3D& obj) = delete;
			House3D& operator =(const House3D& obj) = delete;
			House3D(House3D&& obj) = delete;
			House3D& operator =(House3D&& obj) = delete;
			House3D() = delete;

			void draw() const;
			
			inline float getScaleX()
			{
				return scaleX_;
			}
			inline float getScalY()
			{
				return scaleY_;
			}
			inline float getScaleZ()
			{
				return scaleZ_;
			}
				
	};

// }

#endif //	HOUSE_3D_H
