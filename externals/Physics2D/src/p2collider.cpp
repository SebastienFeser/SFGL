#include "..\include\p2collider.h"

p2Collider::p2Collider()
{
}
p2Collider::p2Collider(p2ColliderDef colDef)
{
	colliderDefinition = colDef;
}

void p2Collider::Init(p2ColliderDef* colDef) //values taken from the json
{
	//Initialisation of all values
	colliderDefinition = *colDef; //colliderDefinition = values used on init
	userData = colDef->userData;
	m_ColliderType = colDef->colliderType;
	m_Shape = colDef->shape;

	switch (m_ColliderType) //Switch for each type of collider
	{
	case p2ColliderType::CIRCLE:
	{
		const auto circleShape = static_cast<p2CircleShape*>(m_Shape); //To take p2Circle shape
		halfExtend = p2Vec2(circleShape->GetRadius(), circleShape->GetRadius());
		break;
	}
	case p2ColliderType::RECT:
	{
		const auto rectShape = static_cast<p2RectShape*>(m_Shape);
		halfExtend = rectShape->GetSize();
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

p2Shape* p2Collider::GetShape() const
{
	return colliderDefinition.shape;
}

void p2Collider::SetUserData(void* colliderData)
{
	userData = colliderData;
}

void p2Collider::RebuildAABB(p2Vec2 position) const //This will be called at every frame to correct the AABB position
{
	p2Vec2 bottomLeft = position - halfExtend;
	p2Vec2 bottomRight = position + p2Vec2(halfExtend.x, -halfExtend.y);
	p2Vec2 topLeft = position + p2Vec2(-halfExtend.x, halfExtend.y);
	p2Vec2 topRight = position + halfExtend;
}
