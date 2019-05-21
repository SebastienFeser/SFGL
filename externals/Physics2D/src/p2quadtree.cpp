#include "..\include\p2quadtree.h"

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
	}

	return 0;*/


}

void p2QuadTree::Insert(p2Body * obj)
{
	m_Objects.push_back(obj); //Pushing every objects in the QuadTree list
	if (m_NodeLevel > MAX_LEVELS)
	{
		Split();
	}

}

void p2QuadTree::Retrieve()
{


}
