#include "..\include\p2quadtree.h"
#include "SFML/Window/Keyboard.hpp"
#include "p2contact.h"

p2QuadTree::p2QuadTree(int nodeLevel, p2AABB bounds)
{
	
	// Set base values
	m_NodeLevel = nodeLevel;
	m_Bounds = bounds;


}

p2QuadTree::~p2QuadTree()
{
}

void p2QuadTree::Clear()
{


		for (p2QuadTree* quad : nodes)
		{
			//Delete Sub QuadTrees
			quad->Clear();

			//Delete Bodies in the QuadTree
			for (p2Body* body : quad->m_Objects)
			{
				m_Objects.push_back(body);
			}

			delete(quad);
		}

}



void p2QuadTree::Split()
{
	//Check if the max Node level is achieved
	if (m_NodeLevel > MAX_LEVELS)
		return;

	//Define the corners of the current QuadTree
	const p2Vec2 extends = m_Bounds.GetExtends();

	//Set the current QuadTree position
	p2Vec2 currentPosition = m_Bounds.bottomLeft;


	// Define the size of the child quadTree in function of the number of child the trees have
	const float childSideSize = (m_Bounds.topRight.y - currentPosition.y) / sqrt(CHILD_TREE_NMB);

	
	//Set the child QuadTrees
	p2AABB childAABB;

	// AABB 1
	childAABB.bottomLeft = currentPosition;
	childAABB.topRight = { currentPosition.x + childSideSize, currentPosition.y + childSideSize };
	nodes[0] = new  p2QuadTree(m_NodeLevel + 1, childAABB);

	//AABB 2
	childAABB.bottomLeft = { currentPosition.x + childSideSize, currentPosition.y };
	childAABB.topRight = { currentPosition.x + childSideSize * 2, currentPosition.y + childSideSize };
	nodes[1] = new  p2QuadTree(m_NodeLevel + 1, childAABB);

	//AABB 3
	childAABB.bottomLeft = { currentPosition.x, currentPosition.y + childSideSize };
	childAABB.topRight = { currentPosition.x + childSideSize, currentPosition.y + childSideSize*2 };
	nodes[2] = new  p2QuadTree(m_NodeLevel + 1, childAABB);

	//AABB 4
	childAABB.bottomLeft = { currentPosition.x + childSideSize, currentPosition.y + childSideSize };
	childAABB.topRight = { currentPosition.x + childSideSize*2, currentPosition.y + childSideSize*2 };
	nodes[3] = new  p2QuadTree(m_NodeLevel + 1, childAABB);

}

int p2QuadTree::GetIndex(p2Body * rect)
{
	/*for (int i = 0; i < CHILD_TREE_NMB; i++)
	{
		for(p2Body* body : nodes[i]->m_Objects)
		{
			if (body == rect)
				return i;
		}
	}*/

	return 0;


}

void p2QuadTree::Insert(p2Body * obj)
{
	//Test if the quadTree has children
	if (nodes == nullptr)
	{
		if (m_Objects.size() >= MAX_OBJECTS && m_NodeLevel <= MAX_LEVELS)
		{
			Split();
			//Dispatch the gameObjects in the children
			std::vector<p2Body*> m_Objects_Copy = m_Objects;
			m_Objects.clear();
			for (p2Body* element : m_Objects_Copy)
			{
				Insert(element);
			}
		}
		else
		{
			//Add Object to the actual QuadTree
			m_Objects.push_back(obj);
		}
	}
	else
	{
		p2QuadTree* childQuadTree;

		//Check the position of the body to dispatch to the child
		for (int i= 0;  i < CHILD_TREE_NMB; i++)
		{
			if (obj->GetPosition().x >= nodes[i]->GetAABB().bottomLeft.x && 
				obj->GetPosition().y >= nodes[i]->GetAABB().bottomLeft.y &&
				obj->GetPosition().x <= nodes[i]->GetAABB().topRight.x &&
				obj->GetPosition().y <= nodes[i]->GetAABB().topRight.y)
			{

				childQuadTree = nodes[i];

				return;
			}
		}
		
		//Check if Body AABB is in the QuadTree AABB
		/*if ((obj->GetAABB().bottomLeft.x < childQuadTree->GetAABB().bottomLeft.x ||
			obj->GetAABB().bottomLeft.y < childQuadTree->GetAABB().bottomLeft.y || 
			obj->GetAABB().topRight.x > childQuadTree->GetAABB().topRight.x || 
			obj->GetAABB().topRight.x > childQuadTree->GetAABB().topRight.x))
		{
			m_Objects.push_back(obj);
		}
		else
		{
			childQuadTree->Insert(obj);
		}*/
	}






}

void p2QuadTree::Retrieve(p2ContactManager contact_manager)			//Create a list of the lists of the objects that could collide
{
	if (nodes == nullptr)
	{
		for (int i = 0; i < m_Objects.size(); i++)
		{
			for (int j = i; i < m_Objects.size(); i++)
			{
				contact_manager.CheckAABBContact(*m_Objects[i], *m_Objects[j]);
			}
		}
	}
	else
	{
		for (auto& element1 : m_Objects)
		{
			for (auto& element2 : nodes)
			{
				element2->AddExternalObject(element1);
			}
		}
	}

}

void p2QuadTree::AddExternalObject(p2Body * obj)
{
	m_Objects.push_back(obj);
}

p2AABB p2QuadTree::GetAABB() const
{
	return  m_Bounds;
}
