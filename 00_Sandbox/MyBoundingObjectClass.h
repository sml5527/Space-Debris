/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOUNDINGOBJECTCLASS_H_
#define __MYBOUNDINGOBJECTCLASS_H_

#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include <SFML\Graphics.hpp>


//System Class
class MyBoundingObjectClass
{
	float m_fRadius = 0.0f; //Radius of the Bounding Object
	vector3 m_v3Size = vector3(0.0f);
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Object Class
	
	vector3 color = vector3(0.0f, 1.0f, 0.0f);
	MeshManagerSingleton* m_pMeshMngr = MeshManagerSingleton::GetInstance();

public:
	bool visibility = true;
	/*
	MyBoundingObjectClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyBoundingObjectClass(std::vector<vector3> a_lVectorList);
	/*
	MyBoundingObjectClass
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyBoundingObjectClass(MyBoundingObjectClass const& other);
	/*
	operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyBoundingObjectClass& operator=(MyBoundingObjectClass const& other);
	/*
	~MyBoundingObjectClass
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyBoundingObjectClass(void);

	/*
	Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyBoundingObjectClass& other);

	/*
	SetToWorldMatrix
	USAGE: Sets the Bounding Object into world coordinates
	ARGUMENTS:
	matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	GetCenter
	USAGE: Gets the Bounding Object's center in world coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the Object in world coordinates
	*/
	vector3 GetCenterG(void);

	/*
	GetRadius
	USAGE: Gets the Bounding Object's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Object
	*/
	float GetRadius(void);

	/*
	IsColliding
	USAGE: Asks if there is a collision with another Bounding Object Object
	ARGUMENTS:
	MyBoundingObjectClass* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingObjectClass* const a_pOther);

	vector3 GetSize(void);
	matrix4 GetModelMatrix(void);

	void setVisibility(bool value);
	void setColor(vector3 value);

	void setModelMatrix(matrix4 value);
	void draw(void);
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

#endif //__MYBOUNDINGObjectCLASS_H__