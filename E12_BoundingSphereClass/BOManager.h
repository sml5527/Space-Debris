#pragma once


#include "RE\ReEngAppClass.h"
#include "RE\ReEng.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingObjectClass.h"

using namespace std;

class BOManager
{
	static BOManager* instance;
	vector<MyBoundingObjectClass> list;

public:
	static BOManager* getInstance() 
	{
		if (instance == nullptr)
			instance = new BOManager();
		return instance;
	};

	static void releaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	};

	void addObject(vector<vector3> a_lVectorList)
	{
		list.push_back( MyBoundingObjectClass(a_lVectorList));
	};

	void setObjectVisibility(int i, bool value)
	{
		list[i].setVisibility(value);
	};

	void setObjectModelMatrix(int i, matrix4 value)
	{
		list[i].setModelMatrix(value);
	};

	void setObjectColor(int i, vector3 value)
	{
		list[i].setColor(value);
	};
	void render(int i)
	{
		if (list[i].visibility)
		list[i].draw();
	};
	void renderAll()
	{
		for (int i = 0; i < list.size(); i++)
		{
			if(list[i].visibility)
			list[i].draw();
		}
	};

	void checkCollisons()
	{
		if (list.size() > 1)
		{
			for (int i = 0; i < list.size(); i++)
			{
				for (int j = 0; j < list.size(); j++)
				{
					if (i != j)
					{
						list[i].IsColliding(&list[j]);
					}

				}
			}
		}
	}
private:
	BOManager() {};
};

