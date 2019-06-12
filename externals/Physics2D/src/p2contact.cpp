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

p2ContactManager::p2ContactManager(p2ContactListener* contact)
{
	this->contactListener = contact;
}
p2ContactManager::p2ContactManager()
{
	
}


bool p2ContactManager::CheckAABBContact(p2Body &bodyA, p2Body &bodyB)
{
	bool isContact = false;
	bool isContactCircle = false;


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
			if (isContact)
			{
				isContactCircle = CheckCollision(bodyA, bodyB, bodyAElement, bodyBElement);
			}
			return isContactCircle;
		}
	}


	//if(contact->GetColliderA()->GetAABB().topRight.x < contact->GetColliderB()->GetAABB().topRight.x ||)
	
}

bool p2ContactManager::CheckCollision(p2Body &bodyA, p2Body &bodyB, p2Collider colliderA, p2Collider colliderB)
{
	bool contact = false;
	// CIRCLE : CIRCLE
	if (colliderA.GetColliderType() == p2ColliderType::CIRCLE && colliderB.GetColliderType() == p2ColliderType::CIRCLE)
	{
		contact = CollisionCircleCircle(bodyA, bodyB);
	}
	//CIRCLE : RECT
	else if(colliderA.GetColliderType() == p2ColliderType::CIRCLE && colliderB.GetColliderType() == p2ColliderType::RECT)
	{
		CollisionCircleRect(bodyA,bodyB);
	}
	//RECT : CIRCLE
	else if(colliderA.GetColliderType() == p2ColliderType::RECT && colliderB.GetColliderType() == p2ColliderType::CIRCLE)
	{
		CollisionCircleRect(bodyB,bodyA);
	}
	//RECT : RECT
	else if(colliderA.GetColliderType() == p2ColliderType::RECT && colliderB.GetColliderType() == p2ColliderType::RECT)
	{
		CollisionRectRect(bodyA, bodyB);
	}
	return contact;
}

void p2ContactManager::CollisionRectRect(p2Body &bodyA, p2Body &bodyB)
{
	/*p2Collider *colliderA;
	p2Collider *colliderB;

	for (p2Collider element : *bodyA.GetColliders())
	{
		if (element.GetShape() != nullptr)
		{
			colliderA = &element;
		}
	}

	for (p2Collider element : *bodyB.GetColliders())
	{
		if (element.GetShape() != nullptr)
		{
			colliderB = &element;
		}
	}

	p2Vec2 axis11;
	p2Vec2 axis12;
	p2Vec2 axis21;
	p2Vec2 axis22;*/

	CollisionCorrectionRectRect(bodyA, bodyB);
}

void p2ContactManager::CollisionCircleRect(p2Body &bodyCircle, p2Body &bodySquare)
{

}

bool p2ContactManager::CollisionCircleCircle(p2Body &bodyA, p2Body &bodyB)
{
	bool collision = false;
	float distanceCenterCenter;
	float additionTwoRadius;
	float radiusA;
	float radiusB;

	//Get the 2 radius
	for (p2Collider element : *bodyA.GetColliders())
	{
		if (element.GetShape() != nullptr)
		{
			p2CircleShape* circleshapeA = dynamic_cast<p2CircleShape*>(element.GetShape());
			if (circleshapeA != nullptr)
			{
				additionTwoRadius = circleshapeA->GetRadius();
				radiusA = circleshapeA->GetRadius();
			}
		}
	}

	for (p2Collider element : *bodyB.GetColliders())
	{
		if (element.GetShape() != nullptr)
		{
			p2CircleShape* circleshapeB = dynamic_cast<p2CircleShape*>(element.GetShape());
			if (circleshapeB != nullptr)
			{
				additionTwoRadius += circleshapeB->GetRadius();
				radiusB = circleshapeB->GetRadius();
			}
		}
	}

	//Calculate Distance A, B
	float distanceX;
	float distanceY;

	distanceX = bodyB.GetPosition().x - bodyA.GetPosition().x;
	distanceY = bodyB.GetPosition().y - bodyA.GetPosition().y;

	distanceCenterCenter = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
	



	for (auto& element : *bodyA.GetColliders())
	{
		element.GetShape();
	}
	if (distanceCenterCenter < additionTwoRadius)
	{
		collision = true;

		if (bodyA.GetType() == p2BodyType::KINEMATIC && bodyB.GetType() == p2BodyType::KINEMATIC)
		{
			//There's Collision
		}
		else
		{
			CollisionCorrectionCircleCircle(bodyA, bodyB, distanceCenterCenter, radiusA, radiusB);
		}
	}
	return collision;
}

void p2ContactManager::CollisionCorrectionRectRect(p2Body &bodyA, p2Body &bodyB)
{
	p2Vec2 axis1 = p2Vec2(1,0);
	p2Vec2 axis2 = p2Vec2(0,1);

	bodyA.SetLinearVelocity(p2Vec2(0, 0));
	bodyB.SetLinearVelocity(p2Vec2(0, 0));
}

void p2ContactManager::CollisionCorrectionCircleRect(p2Body bodyCircle, p2Body bodyRect)
{

}

void p2ContactManager::CollisionCorrectionCircleCircle(p2Body &bodyA, p2Body &bodyB, float distanceCenterCenter, float radiusA, float radiusB)
{
	//Calculate distance between 2 circles center
		//DONE
	//Calculate the distance from the first circle center to the intersection line


	
	
	float distBodyACollision;
	float distBodyBCollision;

	distBodyACollision = (pow(radiusA, 2) - pow(radiusB, 2) + pow(distanceCenterCenter, 2)) / (2 * distanceCenterCenter);
	distBodyBCollision = distanceCenterCenter - distBodyACollision;

	p2Vec2 pointIntersection = bodyA.GetPosition() + (((bodyB.GetPosition() - bodyA.GetPosition()) / distanceCenterCenter) * distBodyACollision);

	//P2 = P0 + a ( P1 - P0 ) / d
	p2Vec2 collisionCenterPoint = bodyA.GetPosition() + (bodyB.GetPosition() - bodyA.GetPosition()) * distBodyACollision / distanceCenterCenter;

	if (bodyA.GetType() == p2BodyType::DYNAMIC)
	{
		float distToRemoveA = radiusB - distBodyBCollision;
		float distToRemoveB = radiusA - distBodyACollision;
		p2Vec2 vecAB = p2Vec2(bodyB.GetPosition().x - bodyA.GetPosition().x, bodyB.GetPosition().y - bodyA.GetPosition().y) ;
		p2Vec2 vecBA = p2Vec2(bodyA.GetPosition().x - bodyB.GetPosition().x, bodyA.GetPosition().y - bodyB.GetPosition().y);

		p2Vec2 vecToRemoveA = vecAB.Normalized() * distToRemoveA;
		p2Vec2 vecToRemoveB = vecBA.Normalized() * distToRemoveB;


		if (bodyA.GetLinearVelocity() != p2Vec2(0, 0) && bodyB.GetLinearVelocity() != p2Vec2(0, 0))
		{
			bodyA.SetPosition(bodyA.GetPosition() + vecToRemoveA);
			bodyB.SetPosition(bodyB.GetPosition() + vecToRemoveB);
		}

		bodyA.SetLinearVelocity(p2Vec2(0, 0));
		bodyB.SetLinearVelocity(p2Vec2(0, 0));

		if (bodyB.GetType() == p2BodyType::DYNAMIC)
		{
			
		}
		else if (bodyB.GetType() == p2BodyType::STATIC)
		{
			
		}
	}
	else if (bodyB.GetType() == p2BodyType::DYNAMIC)
	{
		
		if (bodyA.GetType() == p2BodyType::STATIC)
		{

		}
	}
}

