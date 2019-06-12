#include "..\include\p2collider.h"

p2Collider::p2Collider()
{
}
p2Collider::p2Collider(p2ColliderDef colDef)
{
	p2Collider::Init(&colDef);
	colliderDefinition = colDef;
}

void p2Collider::Init(p2ColliderDef* colDef) //values taken from the json
{
	//Initialisation of all values
	colliderDefinition = *colDef; //colliderDefinition = values used on init
	userData = colDef->userData;
	m_ColliderType = colDef->colliderType;
	//m_Shape = colDef->shape;
	
	//aabb = 

	switch (m_ColliderType) //Switch for each type of collider
	{
	case p2ColliderType::CIRCLE:
	{
		const auto circleShape = new p2CircleShape(*static_cast<p2CircleShape*>(colDef->shape)); //To take p2Circle shape
		halfExtend = p2Vec2(circleShape->GetRadius(), circleShape->GetRadius());
		m_Shape = circleShape;
		break;
	}
	case p2ColliderType::RECT:
	{
		const auto rectShape = new p2RectShape(*static_cast<p2RectShape*>(colDef->shape)); //To take p2Circle shape
		halfExtend = rectShape->GetSize()/2.f;
		m_Shape = rectShape;
		break;
	}
	/*case p2ColliderType::POLY:
	{
		halfExtend = p2Vec2(0, 0);
		break;
	}*/
	default:
	{
		halfExtend = p2Vec2(0, 0);
		break;
	}
	}
}


bool p2Collider::IsSensor() const
{
	return colliderDefinition.isSensor;
}

void * p2Collider::GetUserData() const
{
	return userData;
}

p2Shape* p2Collider::GetShape()
{
	return m_Shape;
}

void p2Collider::SetUserData(void* colliderData)
{
	userData = colliderData;
}

void p2Collider::RebuildAABB(p2Vec2 position) //This will be called at every frame to correct the AABB position
{
	aabb.bottomLeft = position - halfExtend;
	aabb.bottomRight = position + p2Vec2(halfExtend.x, -halfExtend.y);
	aabb.topLeft = position + p2Vec2(-halfExtend.x, halfExtend.y);
	aabb.topRight = position + halfExtend;

}

p2AABB p2Collider::GetAABB()
{
	return aabb;
}

p2ColliderType p2Collider::GetColliderType()
{
	return m_ColliderType;
}

