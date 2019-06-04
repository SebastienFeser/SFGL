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
#include <p2world.h>
#include "p2quadtree.h"


p2World::p2World(p2Vec2 gravity): m_Gravity(gravity)
{
	this->m_Gravity = gravity;
	//this->m_QuadTree = p2QuadTree();
	m_Bodies.resize(MAX_BODY_LEN);
}

void p2World::Step(float dt)
{
	for (p2Body &body : m_Bodies)
	{
		// Calculate forces
		
		//Gravity
		if (body.GetType() == p2BodyType::STATIC)
		{
		}
		else if (body.GetType() == p2BodyType::KINEMATIC)
		{
			p2Vec2 bodyLinearVelocity = body.GetLinearVelocity();
			body.SetPosition(body.GetPosition() + body.GetLinearVelocity());
		}
		else if (body.GetType() == p2BodyType::DYNAMIC)
		{

			p2Vec2 bodyLinearVelocity = body.GetLinearVelocity();
			body.SetLinearVelocity(bodyLinearVelocity + (this->m_Gravity * dt *body.GetGravityMultiplier()));
			body.SetPosition(body.GetPosition() + body.GetLinearVelocity());
		}
		
		if (body.GetColliders()->size() < 1)
		{
			//BUG: The Colliders are cleared
		}
		else
		{
			for (p2Collider &element2 : *body.GetColliders())
			{

				element2.RebuildAABB(body.GetPosition());
			}
		}


		// TODO: Apply angular velocity
		//body.SetLinearVelocity(body.GetLinearVelocity());

		// Apply acceleration
		//body.SetLinearVelocity(body.GetLinearVelocity() + m_Gravity * dt);

		// Apply movement
		//body.SetPosition(body.GetPosition() + body.GetLinearVelocity() * dt);		
	}

	// Quadtree
	//m_QuadTree.Clear(); //TODO

	for (int i = 0; i < m_Bodies.size(); i++)
	{
		//m_QuadTree.Insert(m_Bodies[i]); //TODO: To correct & write code
	}
	//Retrieve

	// Check for collision
}

p2Body * p2World::CreateBody(p2BodyDef* bodyDef)
{
	p2Body& body = m_Bodies[m_BodyIndex];
	body.Init(bodyDef);
	m_BodyIndex++;
	return &body;
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
}
