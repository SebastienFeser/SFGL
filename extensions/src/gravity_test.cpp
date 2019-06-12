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

#include <extensions/gravity_test.h>
#include <engine/engine.h>
//#include <graphics/graphics2d.h>
#include <physics/body2d.h>
#include <physics/physics2d.h>

#include <iostream>

const p2Vec2 minimumPosition = p2Vec2(0, 0);
const p2Vec2 maximumPosition = p2Vec2(13, 7);
//bool contact;

namespace sfge::ext
{
	GravityTest::GravityTest(Engine& engine):
		System(engine)
	{
	}

	void GravityTest::OnEngineInit()
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
		float speed = 1.0;
		for (auto& body : m_Bodies)
		{
			body->SetGravityMultiplier(speed);
			speed/= 2;
		}
		
	}

	void GravityTest::OnUpdate(float dt)
	{
		(void)dt;
	}


	void GravityTest::OnFixedUpdate()
	{
		rmt_ScopedCPUSample(PlanetSystemFixedUpdate,0);
	}

	void GravityTest::OnDraw()
	{
		rmt_ScopedCPUSample(PlanetSystemDraw,0);

	
	}

}
