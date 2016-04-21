#include "MyBoundingCubeClass.h"
//  MyBoundingCubeClass
void MyBoundingCubeClass::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void MyBoundingCubeClass::Swap(MyBoundingCubeClass& other)
{
	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
}
void MyBoundingCubeClass::Release(void)
{

}
//The big 3
MyBoundingCubeClass::MyBoundingCubeClass(std::vector<vector3> a_lVectorList)
{
	uint nVertexCount = a_lVectorList.size();

	if (nVertexCount > 0)
	{
		m_v3Min = a_lVectorList[0];
		m_v3Max = a_lVectorList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (a_lVectorList[i].x > m_v3Max.x)
			m_v3Max.x = a_lVectorList[i].x;
		else if (a_lVectorList[i].x < m_v3Min.x)
			m_v3Min.x = a_lVectorList[i].x;

		if (a_lVectorList[i].y > m_v3Max.y)
			m_v3Max.y = a_lVectorList[i].y;
		else if (a_lVectorList[i].y < m_v3Min.y)
			m_v3Min.y = a_lVectorList[i].y;

		if (a_lVectorList[i].z > m_v3Max.z)
			m_v3Max.z = a_lVectorList[i].z;
		else if (a_lVectorList[i].z < m_v3Min.z)
			m_v3Min.z = a_lVectorList[i].z;
	}

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3Max);
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0f, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}
MyBoundingCubeClass::MyBoundingCubeClass(MyBoundingCubeClass const& other)
{
	m_fRadius = other.m_fRadius;
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
}
MyBoundingCubeClass& MyBoundingCubeClass::operator=(MyBoundingCubeClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyBoundingCubeClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingCubeClass::~MyBoundingCubeClass(){Release();};
//Accessors
void MyBoundingCubeClass::SetModelMatrix(matrix4 a_m4ToWorld){ m_m4ToWorld = a_m4ToWorld; }
vector3 MyBoundingCubeClass::GetCenterG(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
float MyBoundingCubeClass::GetRadius(void) { return m_fRadius; }
vector3 MyBoundingCubeClass::GetSize(void) { return m_v3Size; };
//--- Non Standard Singleton Methods
bool MyBoundingCubeClass::IsColliding(MyBoundingCubeClass* const a_pOther)
{
	//Collision check goes here
	vector3 v3Temp = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
	vector3 v3Temp1 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Center, 1.0f));
	
	bool bAreColliding = true;
	vector3 vMin1 = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 vMax1 = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
	vector3 vMin2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 vMax2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	//Check for X
	if (vMax1.x < vMin2.x)
		bAreColliding = false;
	if (vMin1.x > vMax2.x)
		bAreColliding = false;

	//Check for Y
	if (vMax1.y < vMin2.y)
		bAreColliding = false;
	if (vMin1.y > vMax2.y)
		bAreColliding = false;

	//Check for Z
	if (vMax1.z < vMin2.z)
		bAreColliding = false;
	if (vMin1.z > vMax2.z)
		bAreColliding = false;

	return bAreColliding;
}
matrix4 MyBoundingCubeClass::GetModelMatrix(void) { return m_m4ToWorld; }