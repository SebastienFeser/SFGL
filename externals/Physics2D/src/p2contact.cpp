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

void p2ContactManager::CheckAABBContact(p2Body bodyA, p2Body bodyB)
{
	bool isContact = false;

	//Check bodyA aabb
	if(
		//topRight
		bodyB.GetAABB().topRight.x < bodyA.GetAABB().topRight.x && 
		bodyB.GetAABB().topRight.y < bodyA.GetAABB().topRight.y &&
		bodyB.GetAABB().topRight.x > bodyA.GetAABB().bottomLeft.x &&
		bodyB.GetAABB().topRight.y > bodyA.GetAABB().bottomLeft.y ||
		//topLeft
		bodyB.GetAABB().topLeft.x < bodyA.GetAABB().topRight.x &&
		bodyB.GetAABB().topLeft.y < bodyA.GetAABB().topRight.y &&
		bodyB.GetAABB().topLeft.x > bodyA.GetAABB().bottomLeft.x &&
		bodyB.GetAABB().topLeft.y > bodyA.GetAABB().bottomLeft.y ||
		//bottomRight
		bodyB.GetAABB().bottomRight.x < bodyA.GetAABB().topRight.x &&
		bodyB.GetAABB().bottomRight.y < bodyA.GetAABB().topRight.y &&
		bodyB.GetAABB().bottomRight.x > bodyA.GetAABB().bottomLeft.x &&
		bodyB.GetAABB().bottomRight.y > bodyA.GetAABB().bottomLeft.y ||
		//bottomLeft
		bodyB.GetAABB().bottomLeft.x < bodyA.GetAABB().topRight.x &&
		bodyB.GetAABB().bottomLeft.y < bodyA.GetAABB().topRight.y &&
		bodyB.GetAABB().bottomLeft.x > bodyA.GetAABB().bottomLeft.x &&
		bodyB.GetAABB().bottomLeft.y > bodyA.GetAABB().bottomLeft.y
		)
	{
		isContact = true;
	}

	//Check bodyB aabb
	if (
		//Check ifContact for optimisation
		isContact ||
		//topRight
		bodyA.GetAABB().topRight.x < bodyB.GetAABB().topRight.x &&
		bodyA.GetAABB().topRight.y < bodyB.GetAABB().topRight.y &&
		bodyA.GetAABB().topRight.x > bodyB.GetAABB().bottomLeft.x &&
		bodyA.GetAABB().topRight.y > bodyB.GetAABB().bottomLeft.y ||
		//topLeft
		bodyA.GetAABB().topLeft.x < bodyB.GetAABB().topRight.x &&
		bodyA.GetAABB().topLeft.y < bodyB.GetAABB().topRight.y &&
		bodyA.GetAABB().topLeft.x > bodyB.GetAABB().bottomLeft.x &&
		bodyA.GetAABB().topLeft.y > bodyB.GetAABB().bottomLeft.y ||
		//bottomRight
		bodyA.GetAABB().bottomRight.x < bodyB.GetAABB().topRight.x &&
		bodyA.GetAABB().bottomRight.y < bodyB.GetAABB().topRight.y &&
		bodyA.GetAABB().bottomRight.x > bodyB.GetAABB().bottomLeft.x &&
		bodyA.GetAABB().bottomRight.y > bodyB.GetAABB().bottomLeft.y ||
		//bottomLeft
		bodyA.GetAABB().bottomLeft.x < bodyB.GetAABB().topRight.x &&
		bodyA.GetAABB().bottomLeft.y < bodyB.GetAABB().topRight.y &&
		bodyA.GetAABB().bottomLeft.x > bodyB.GetAABB().bottomLeft.x &&
		bodyA.GetAABB().bottomLeft.y > bodyB.GetAABB().bottomLeft.y
		)
	{
		isContact = true;
	}

	if (isContact)
	{
		CheckCollision(bodyA, bodyB);
	}
	//if(contact->GetColliderA()->GetAABB().topRight.x < contact->GetColliderB()->GetAABB().topRight.x ||)
}

void p2ContactManager::CheckCollision(p2Body bodyA, p2Body bodyB)
{

}

void p2ContactManager::CollisionSquareSquare()
{

}

void p2ContactManager::CollisionCircleSquare()
{

}

void p2ContactManager::CollisionCircleCircle()
{

}
