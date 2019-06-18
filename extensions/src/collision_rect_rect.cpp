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

#include <extensions/collision_rect_rect.h>
#include <engine/engine.h>
#include <graphics/graphics2d.h>
#include <physics/body2d.h>
#include <physics/physics2d.h>
#include <p2contact.h>

#include <iostream>

const p2Vec2 minimumPosition = p2Vec2(0, 0);
const p2Vec2 maximumPosition = p2Vec2(13, 7);

namespace sfge::ext
{
	CollisionRectRect::CollisionRectRect(Engine& engine):
		System(engine)
	{
	}

	void CollisionRectRect::OnEngineInit()
	{
		m_GraphicsManager = m_Engine.GetGraphics2dManager();
		m_BodyManager = m_Engine.GetPhysicsManager()->GetBodyManager();

		auto* entityManager = m_Engine.GetEntityManager();

		m_Entities = entityManager->GetEntitiesWithType(ComponentType::BODY2D);
		for (auto& entity : m_Entities)
		{
			const auto body = m_BodyManager->GetComponentPtr(entity);
			m_Bodies.push_back(body->GetBody());
		}

		m_Bodies[0]->SetLinearVelocity(p2Vec2(0.2, 0.2));
		m_Bodies[1]->SetLinearVelocity(p2Vec2(0.2, 0.1));

		/*for (auto& body : m_Bodies)
		{
			for (auto& collider : *body->GetColliders())
			{
				collider.RebuildAABB(body->GetPosition());
			}
		}*/

		
	}

	void CollisionRectRect::OnUpdate(float dt)
	{
		(void)dt;
	}


	void CollisionRectRect::OnFixedUpdate()
	{
		for (auto& element : m_Bodies)
		{
			if (element->GetPosition().x > maximumPosition.x)
			{
				element->SetLinearVelocity(p2Vec2(-element->GetLinearVelocity().x, element->GetLinearVelocity().y));
			};
			if(element->GetPosition().x < minimumPosition.x)
			{
				element->SetLinearVelocity(p2Vec2(-element->GetLinearVelocity().x, element->GetLinearVelocity().y));
			}
			if(element->GetPosition().y > maximumPosition.y)
			{
				element->SetLinearVelocity(p2Vec2(element->GetLinearVelocity().x, -element->GetLinearVelocity().y));
			}
			if(element->GetPosition().y < minimumPosition.y)
			{
				element->SetLinearVelocity(p2Vec2(element->GetLinearVelocity().x, -element->GetLinearVelocity().y));
			}

		}
		p2ContactManager contactManager;
		/*isContact = false;
			for (auto& body : m_Bodies)
			{
				for (auto& body2 : m_Bodies)
				{
					contactManager;
					if (contactManager.CheckAABBContact(*body, *body2))
					{
						isContact = true;
					}

				}
			}
			std::cout << isContact;*/
		rmt_ScopedCPUSample(PlanetSystemFixedUpdate,0);
	}

	void CollisionRectRect::OnDraw()
	{
		rmt_ScopedCPUSample(PlanetSystemDraw,0);

		for (auto& body : m_Bodies)
		{
			DrawAABB(*body->GetColliders(), sf::Color::Cyan);
			/*for (p2Collider &element : *body->GetColliders())
			{

				std::cout << "Top Right: (" << element.GetAABB().topRight.x << ",";
				std::cout << element.GetAABB().topRight.y << ") \n";

				std::cout << "Bottom Right: (" << element.GetAABB().bottomRight.x << ",";
				std::cout << element.GetAABB().bottomRight.y << ") \n";

				std::cout << "Top Left: (" << element.GetAABB().topLeft.x << ",";
				std::cout << element.GetAABB().topLeft.y << ") \n";

				std::cout << "Bottom Left: (" << element.GetAABB().bottomLeft.x << ",";
				std::cout << element.GetAABB().bottomLeft.y << ") \n \n";

				//std::cout << contact << "\n \n";
			}*/
			
		}

		/*if (contact)
		{
			m_GraphicsManager->DrawLine(Vec2f(0, 0), Vec2f(400, 400), sf::Color::White);
			contact = false;
		}*/
	}

	void CollisionRectRect::DrawAABB(std:: vector<p2Collider> colliders, sf::Color color)
	{
		for (p2Collider& element : colliders)
		{
			m_GraphicsManager->DrawLine(meter2pixel(element.GetAABB().topRight), meter2pixel(element.GetAABB().topLeft), color);
			m_GraphicsManager->DrawLine(meter2pixel(element.GetAABB().bottomLeft), meter2pixel(element.GetAABB().topLeft), color);
			m_GraphicsManager->DrawLine(meter2pixel(element.GetAABB().bottomLeft), meter2pixel(element.GetAABB().bottomRight), color);
			m_GraphicsManager->DrawLine(meter2pixel(element.GetAABB().bottomRight), meter2pixel(element.GetAABB().topRight), color);
		}
		/*m_GraphicsManager->DrawLine(meter2pixel(aabb.topRight), meter2pixel(aabb.topLeft), color);
		m_GraphicsManager->DrawLine(meter2pixel(aabb.bottomLeft), meter2pixel(aabb.topLeft), color);
		m_GraphicsManager->DrawLine(meter2pixel(aabb.bottomLeft), meter2pixel(aabb.bottomRight), color);
		m_GraphicsManager->DrawLine(meter2pixel(aabb.bottomRight), meter2pixel(aabb.topRight), color);*/

	}
}
