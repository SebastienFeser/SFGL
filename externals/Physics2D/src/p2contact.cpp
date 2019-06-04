/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2contact.h>

p2Contact::p2Contact(p2Collider* colliderA, p2Collider* colliderB)
{
	this->colliderA = colliderA;
	this->colliderB = colliderB;
}

p2Collider * p2Contact::GetColliderA()
{
	return colliderA;
}

p2Collider * p2Contact::GetColliderB()
{
	return colliderB;
}

p2ContactManager::p2ContactManager(p2Contact* contact)
{
	this->contact = contact;
}
p2ContactManager::p2ContactManager()
{
	
}


bool p2ContactManager::CheckAABBContact(p2Body &bodyA, p2Body &bodyB)
{
	bool isContact = false;

	for (p2Collider bodyBElement : *bodyB.GetColliders())
	{
		for (p2Collider bodyAElement : *bodyA.GetColliders())
		{
			//Check bodyA aabb
			if (


				//topRight
				bodyBElement.GetAABB().topRight.x < bodyAElement.GetAABB().topRight.x &&
				bodyBElement.GetAABB().topRight.y < bodyAElement.GetAABB().topRight.y &&
				bodyBElement.GetAABB().topRight.x > bodyAElement.GetAABB().bottomLeft.x &&
				bodyBElement.GetAABB().topRight.y > bodyAElement.GetAABB().bottomLeft.y ||
				//topLeft
				bodyBElement.GetAABB().topLeft.x < bodyAElement.GetAABB().topRight.x &&
				bodyBElement.GetAABB().topLeft.y < bodyAElement.GetAABB().topRight.y &&
				bodyBElement.GetAABB().topLeft.x > bodyAElement.GetAABB().bottomLeft.x &&
				bodyBElement.GetAABB().topLeft.y > bodyAElement.GetAABB().bottomLeft.y ||
				//bottomRight
				bodyBElement.GetAABB().bottomRight.x < bodyAElement.GetAABB().topRight.x &&
				bodyBElement.GetAABB().bottomRight.y < bodyAElement.GetAABB().topRight.y &&
				bodyBElement.GetAABB().bottomRight.x > bodyAElement.GetAABB().bottomLeft.x &&
				bodyBElement.GetAABB().bottomRight.y > bodyAElement.GetAABB().bottomLeft.y ||
				//bottomLeft
				bodyBElement.GetAABB().bottomLeft.x < bodyAElement.GetAABB().topRight.x &&
				bodyBElement.GetAABB().bottomLeft.y < bodyAElement.GetAABB().topRight.y &&
				bodyBElement.GetAABB().bottomLeft.x > bodyAElement.GetAABB().bottomLeft.x &&
				bodyBElement.GetAABB().bottomLeft.y > bodyAElement.GetAABB().bottomLeft.y
				)

			{
				isContact = true;
			}

			//Check bodyB aabb
			if (
				//Check ifContact for optimisation
				isContact ||
				//topRight
				bodyAElement.GetAABB().topRight.x < bodyBElement.GetAABB().topRight.x &&
				bodyAElement.GetAABB().topRight.y < bodyBElement.GetAABB().topRight.y &&
				bodyAElement.GetAABB().topRight.x > bodyBElement.GetAABB().bottomLeft.x &&
				bodyAElement.GetAABB().topRight.y > bodyBElement.GetAABB().bottomLeft.y ||
				//topLeft
				bodyAElement.GetAABB().topLeft.x < bodyBElement.GetAABB().topRight.x &&
				bodyAElement.GetAABB().topLeft.y < bodyBElement.GetAABB().topRight.y &&
				bodyAElement.GetAABB().topLeft.x > bodyBElement.GetAABB().bottomLeft.x &&
				bodyAElement.GetAABB().topLeft.y > bodyBElement.GetAABB().bottomLeft.y ||
				//bottomRight
				bodyAElement.GetAABB().bottomRight.x < bodyBElement.GetAABB().topRight.x &&
				bodyAElement.GetAABB().bottomRight.y < bodyBElement.GetAABB().topRight.y &&
				bodyAElement.GetAABB().bottomRight.x > bodyBElement.GetAABB().bottomLeft.x &&
				bodyAElement.GetAABB().bottomRight.y > bodyBElement.GetAABB().bottomLeft.y ||
				//bottomLeft
				bodyAElement.GetAABB().bottomLeft.x < bodyBElement.GetAABB().topRight.x &&
				bodyAElement.GetAABB().bottomLeft.y < bodyBElement.GetAABB().topRight.y &&
				bodyAElement.GetAABB().bottomLeft.x > bodyBElement.GetAABB().bottomLeft.x &&
				bodyAElement.GetAABB().bottomLeft.y > bodyBElement.GetAABB().bottomLeft.y
				)
			{
				isContact = true;
			}
			return  isContact;
			/*if (isContact)
			{
				CheckCollision(bodyA, bodyB, bodyAElement, bodyBElement);
				break;
			}*/
		}
	}


	//if(contact->GetColliderA()->GetAABB().topRight.x < contact->GetColliderB()->GetAABB().topRight.x ||)
	
}

void p2ContactManager::CheckCollision(p2Body bodyA, p2Body bodyB, p2Collider colliderA, p2Collider colliderB)
{
	/*// CIRCLE : CIRCLE
	if (colliderA.GetShape() == p2ColliderType::CIRCLE && colliderB.GetShape() == p2ColliderType::CIRCLE)
	{
		
	}
	//CIRCLE : RECT
	else if(colliderA.GetShape() == p2ColliderType::CIRCLE && colliderB.GetShape() == p2ColliderType::RECT)
	{
		
	}
	//RECT : CIRCLE
	else if(colliderA.GetShape() == p2ColliderType::RECT && colliderB.GetShape() == p2ColliderType::CIRCLE)
	{
		
	}
	//RECT : RECT
	else if(colliderA.GetShape() == p2ColliderType::RECT && colliderB.GetShape() == p2ColliderType::RECT)
	{
		
	}*/
}

void p2ContactManager::CollisionSquareSquare(p2Body bodyA, p2Body bodyB)
{
	
}

void p2ContactManager::CollisionCircleSquare(p2Body bodyCircle, p2Body bodySquare)
{

}

void p2ContactManager::CollisionCircleCircle(p2Body bodyA, p2Body bodyB)
{
	float distanceCenterCenter;
	float additionTwoRadius;

	for (auto& element : *bodyA.GetColliders())
	{
		element.GetShape();
	}
	if (distanceCenterCenter < additionTwoRadius)
	{
		//There's Collision
	}
	else
	{
		//Not Collision
	}
}
