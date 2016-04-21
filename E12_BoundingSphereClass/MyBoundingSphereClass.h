/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOUNDINGSPHERECLASS_H_
#define __MYBOUNDINGSPHERECLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingSphereClass
{
	float m_fRadius = 0.0f; //Radius of the Bounding Sphere
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Sphere Class

public:
	/*
	 MyBoundingSphereClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyBoundingSphereClass(std::vector<vector3> a_lVectorList);
	/*
	 MyBoundingSphereClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyBoundingSphereClass(MyBoundingSphereClass const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyBoundingSphereClass& operator=(MyBoundingSphereClass const& other);
	/*
	 ~MyBoundingSphereClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyBoundingSphereClass(void);

	/*
	 Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
		other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyBoundingSphereClass& other);

	/*
	 SetToWorldMatrix
	USAGE: Sets the Bounding Sphere into world coordinates
	ARGUMENTS:
		matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	
	/*
	 GetCenter
	USAGE: Gets the Bounding Sphere's center in world coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the sphere in world coordinates
	*/
	vector3 GetCenterG(void);

	/*
	 GetRadius
	USAGE: Gets the Bounding Sphere's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Sphere
	*/
	float GetRadius(void);

	/*
	 IsColliding
	USAGE: Asks if there is a collision with another Bounding sphere Object
	ARGUMENTS: 
		MyBoundingSphereClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingSphereClass* const a_pOther);

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

#endif //__MYBOUNDINGSPHERECLASS_H__