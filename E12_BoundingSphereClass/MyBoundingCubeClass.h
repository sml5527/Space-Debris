/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOUNDINGCubeCLASS_H_
#define __MYBOUNDINGCubeCLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingCubeClass
{
	float m_fRadius = 0.0f; //Radius of the Bounding Cube
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Cube Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Cube Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Cube Class

public:
	/*
	 MyBoundingCubeClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyBoundingCubeClass(std::vector<vector3> a_lVectorList);
	/*
	 MyBoundingCubeClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyBoundingCubeClass(MyBoundingCubeClass const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyBoundingCubeClass& operator=(MyBoundingCubeClass const& other);
	/*
	 ~MyBoundingCubeClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyBoundingCubeClass(void);

	/*
	 Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
		other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyBoundingCubeClass& other);

	/*
	 SetToWorldMatrix
	USAGE: Sets the Bounding Cube into world coordinates
	ARGUMENTS:
		matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	
	/*
	 GetCenter
	USAGE: Gets the Bounding Cube's center in world coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the Cube in world coordinates
	*/
	vector3 GetCenterG(void);

	/*
	 GetRadius
	USAGE: Gets the Bounding Cube's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Cube
	*/
	float GetRadius(void);

	/*
	 IsColliding
	USAGE: Asks if there is a collision with another Bounding Cube Object
	ARGUMENTS: 
		MyBoundingCubeClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingCubeClass* const a_pOther);

	vector3 GetSize(void);
	matrix4 GetModelMatrix(void);
	
private:
	/*
	 Release
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	 Init
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MYBOUNDINGCubeCLASS_H__