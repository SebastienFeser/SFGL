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

#include <extensions/aabb_test.h>
#include <engine/engine.h>
#include <graphics/graphics2d.h>
#include <physics/body2d.h>
#include <physics/physics2d.h>

#include <iostream>


namespace sfge::ext
{
	AABBTest::AABBTest(Engine& engine):
		System(engine)
	{
	}

	void AABBTest::OnEngineInit()
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
	}

	void AABBTest::OnUpdate(float dt)
	{
		(void)dt;
	}


	void AABBTest::OnFixedUpdate()
	{
		rmt_ScopedCPUSample(PlanetSystemFixedUpdate,0);
	}

	void AABBTest::OnDraw()
	{
		rmt_ScopedCPUSample(PlanetSystemDraw,0);

		for (auto& body : m_Bodies)
		{
			DrawAABB(body->GetColliders(), sf::Color::Cyan);

			std::cout << "Top Right: (" << body->GetColliders()[0].GetAABB().topRight.x << ",";
			std::cout << body->GetColliders()[0].GetAABB().topRight.y << ") \n";

			std::cout << "Bottom Right: (" << body->GetColliders()[0].GetAABB().bottomRight.x << ",";
			std::cout << body->GetColliders()[0].GetAABB().bottomRight.y << ") \n";

			std::cout << "Top Left: (" << body->GetColliders()[0].GetAABB().topLeft.x << ",";
			std::cout << body->GetColliders()[0].GetAABB().topLeft.y << ") \n";

			std::cout << "Bottom Left: (" << body->GetColliders()[0].GetAABB().bottomLeft.x << ",";
			std::cout << body->GetColliders()[0].GetAABB().bottomLeft.y << ") \n \n";
		}

		//m_GraphicsManager->DrawLine(Vec2f(0, 0), Vec2f(400, 400), sf::Color::White);
	}

	void AABBTest::DrawAABB(std:: vector<p2Collider> colliders, sf::Color color)
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
