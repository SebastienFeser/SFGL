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
#include <engine/engine.h>
#include <engine/scene.h>
#include <gtest/gtest.h>
#include "graphics/shape2d.h"
#include "physics/collider2d.h"

TEST(Physics, TestBallFallingToGround)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->devMode = false;
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Ball Falling To Ground";

	json entityBody1;
	entityBody1["name"] = "Body1";

	json transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 300,300 };
	transformJson1["scale"] = { 1.0,1.0 };
	transformJson1["angle"] = 0.0;

	json circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 50;

	json rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	json circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 50;
	circleColliderJson["bouncing"] = 0.5;
	circleColliderJson["sensor"] = false;

	entityBody1["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };

	json entityBody2;
	entityBody2["name"] = "Ground";

	json transformJson2;
	transformJson2["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson2["position"] = { 400,600 };
	transformJson2["scale"] = { 1.0,1.0 };
	transformJson2["angle"] = 0.0;

	json rectShapeJson;
	rectShapeJson["name"] = "Rect Shape Component";
	rectShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	rectShapeJson["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShapeJson["size"] = {800,200};

	json rigidBodyJson2;
	rigidBodyJson2["name"] = "Rigidbody";
	rigidBodyJson2["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson2["body_type"] = p2BodyType::STATIC;

	json rectColliderJson;
	rectColliderJson["name"] = "Rect Collider";
	rectColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	rectColliderJson["collider_type"] = sfge::ColliderType::BOX;
	rectColliderJson["size"] = {800,200};
	rectColliderJson["sensor"] = false;

	entityBody2["components"] = { transformJson2, rectShapeJson, rigidBodyJson2, rectColliderJson };

	sceneJson["entities"] = { entityBody1, entityBody2 };
	json contactDebugSystem = {
		{ "script_path", "scripts/contact_debug_system.py" }
	};
	json raycastDebugJson =
	{
		{ "script_path", 
			//"scripts/mouse_raycast_system.py" 
			"nothing"
		}
	};
	sceneJson["systems"] = json::array({ contactDebugSystem, raycastDebugJson });
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();

}

TEST(Physics, TestShapeContact)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Contacts";

	const int entitiesNmb = 10;
	json entities[entitiesNmb];

	json shapes[] =
	{
		{
			{"name","Rect Shape Component"},
			{"type",sfge::ComponentType::SHAPE2D},
			{"shape_type", sfge::ShapeType::RECTANGLE},
			{"size",{100,100}}
		},
		{
			{"name","Rect Shape Component"},
			{"type",sfge::ComponentType::SHAPE2D},
			{"shape_type", sfge::ShapeType::CIRCLE},
			{"radius",100}
		}
	};
	json colliders[] =
	{
		{
			{"name","Rect Collider"},
			{"type", sfge::ComponentType::COLLIDER2D},
			{"collider_type",sfge::ColliderType::BOX},
			{"size",{100,100}},
			{"sensor",true}
		},
		{
			{"name","Circle Collider"},
			{"type", sfge::ComponentType::COLLIDER2D},
			{"collider_type",sfge::ColliderType::CIRCLE},
			{"radius",100},
			{"sensor",true}
		}
	};

	for (int i = 0; i < entitiesNmb; i++)
	{
		json& entityJson = entities[i];

		json transformJson =
		{
			{"position",{ rand() % 800,rand() % 600 }},
			{"type", sfge::ComponentType::TRANSFORM2D}
		};

		json rigidbody =
		{
			{"name", "Rigidbody"},
			{"type", sfge::ComponentType::BODY2D},
			{"body_type",  p2BodyType::DYNAMIC},
			{"velocity", {rand() % 400, rand() % 400}}
		};

		int randShapeIndex = rand() % 2;
		entityJson["components"] = { transformJson, shapes[randShapeIndex], rigidbody, colliders[randShapeIndex] };

		
	}
	sceneJson["entities"] = entities;
	sceneJson["systems"] = json::array({
		{
			{ "script_path", "scripts/contact_debug_system.py" }
		},
		{
			{ "script_path", "scripts/stay_onscreen_system.py" }
		},
		{
			{ "script_path", 
			//"scripts/mouse_raycast_system.py" 
			"nothing" }
		}
	}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(Sebastien, TestFallingObject)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 9.81f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Test Falling Object";

	const int entitiesNmb = 2;
	json entities[entitiesNmb];

	/*json shapes[] =
	{
		{
			{"name","Rect Shape Component"},
			{"type",sfge::ComponentType::SHAPE2D},
			{"shape_type", sfge::ShapeType::RECTANGLE},
			{"size",{1000,100}}
		},
		{
			{"name","Rect Shape Component"},
			{"type",sfge::ComponentType::SHAPE2D},
			{"shape_type", sfge::ShapeType::CIRCLE},
			{"radius",100}
		}
	};
	json colliders[] =
	{
		{
			{"name","Rect Collider"},
			{"type", sfge::ComponentType::COLLIDER2D},
			{"collider_type",sfge::ColliderType::BOX},
			{"size",{1000,100}},
			{"sensor",true}
		},
		{
			{"name","Circle Collider"},
			{"type", sfge::ComponentType::COLLIDER2D},
			{"collider_type",sfge::ColliderType::CIRCLE},
			{"radius",100},
			{"sensor",true}
		}
	};*/

	//Spécifier transform, rigidBody et shape
	json shapeGround =
	{
		{"name","Ground"},
		{"type",sfge::ComponentType::SHAPE2D},
		{"shape_type", sfge::ShapeType::RECTANGLE},
		{"size",{1280, 100}}
	};

	json shapeBall =
	{
		{"name","Ball"},
		{"type",sfge::ComponentType::SHAPE2D},
		{"shape_type", sfge::ShapeType::CIRCLE},
		{"radius",50}
	};
	//rect
	json& entityJson1 = entities[0];

	entityJson1["name"] = "Ground";

	json transformJson =
	{
		{"position",{ 640, 700 }},
		{"type", sfge::ComponentType::TRANSFORM2D},
		{"size", {1,1}}
	};

	json rigidbody =
	{
		{"name", "Rigidbody"},
		{"type", sfge::ComponentType::BODY2D},
		{"body_type",  p2BodyType::STATIC},
		{"velocity", {0, 0}}
	};

	//int randShapeIndex = rand() % 2;
	entityJson1["components"] = { transformJson, shapeGround, rigidbody/*, colliders[randShapeIndex]*/ };

	//cercle

	json& entityJson2 = entities[1];
	entityJson2["name"] = "Ball";

	transformJson =
	{
		{"position",{ 640, 300 }},
		{"type", sfge::ComponentType::TRANSFORM2D},
		{"size", {1,1}}
	};

	rigidbody =
	{
		{"name", "Rigidbody"},
		{"type", sfge::ComponentType::BODY2D},
		{"body_type",  p2BodyType::DYNAMIC},
		{"velocity", {0, 0}}
	};

	//randShapeIndex = rand() % 2;
	entityJson2["components"] = { transformJson, shapeBall, rigidbody/*, colliders[randShapeIndex]*/ };


	//Fin

	sceneJson["entities"] = entities;
	sceneJson["systems"] = json::array({
		{
			{ "script_path", "scripts/test_falling_object.py" }
		},
		{
			{ "script_path",
			//"scripts/mouse_raycast_system.py" 
			"nothing" }
		}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
};

TEST(Final, ShowAABB)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "Testaabb";

	const int entitiesNmb = 1;
	json entities[entitiesNmb];

	json entityBody1;
	entityBody1["name"] = "Body1";

	json transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 300,300 };

	json circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 70;

	json rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	json circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 70;
	circleColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody1["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };

	json entityBody2;

	entityBody2["name"] = "Body1";

	transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 400,500 };

	circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 70;

	rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 70;
	circleColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody2["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };



	//sceneJson["entities"] = entities;
	sceneJson["entities"] = { entityBody1, entityBody2 };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "AABBTest"}
			},
			{
				{ "script_path", "scripts/contact_debug_system.py" }
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();

}

TEST(Final, CollisionSquareSquare)
{
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "CollisionRectRect";

	const int entitiesNmb = 1;
	json entities[entitiesNmb];

	json entityBody1;
	entityBody1["name"] = "Body1";

	json transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 100,300 };

	json rectShapeJson;
	rectShapeJson["name"] = "Circle Shape Component";
	rectShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	rectShapeJson["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShapeJson["size"] = {100,100};

	json rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	json rectColliderJson;
	rectColliderJson["name"] = "Circle Collider";
	rectColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	rectColliderJson["collider_type"] = sfge::ColliderType::BOX;
	rectColliderJson["size"] = {100,100};
	rectColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody1["components"] = { transformJson1, rectShapeJson, rigidBodyJson1, rectColliderJson };

	json entityBody2;

	entityBody2["name"] = "Body1";

	transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 1200,300 };

	rectShapeJson;
	rectShapeJson["name"] = "Circle Shape Component";
	rectShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	rectShapeJson["shape_type"] = sfge::ShapeType::RECTANGLE;
	rectShapeJson["size"] = {100,150};

	rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	rectColliderJson;
	rectColliderJson["name"] = "Circle Collider";
	rectColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	rectColliderJson["collider_type"] = sfge::ColliderType::BOX;
	rectColliderJson["size"] = {100,150};
	rectColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody2["components"] = { transformJson1, rectShapeJson, rigidBodyJson1, rectColliderJson };



	//sceneJson["entities"] = entities;
	sceneJson["entities"] = { entityBody1, entityBody2 };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "CollisionSquareSquare"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(Final, BodyGravity)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.981f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "FallingBodies";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };



	json entityBody1;
	entityBody1["name"] = "Body1";

	json transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 300,300 };

	json circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 70;

	json rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	json circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 70;
	circleColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody1["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };



	json entityBody2;
	entityBody2["name"] = "Body2";

	transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 600,300 };

	circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 70;

	rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 70;
	circleColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody2["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };



	json entityBody3;
	entityBody1["name"] = "Body3";

	transformJson1;
	transformJson1["type"] = sfge::ComponentType::TRANSFORM2D;
	transformJson1["position"] = { 900,300 };

	circleShapeJson;
	circleShapeJson["name"] = "Circle Shape Component";
	circleShapeJson["type"] = sfge::ComponentType::SHAPE2D;
	circleShapeJson["shape_type"] = sfge::ShapeType::CIRCLE;
	circleShapeJson["radius"] = 70;

	rigidBodyJson1;
	rigidBodyJson1["name"] = "Rigidbody";
	rigidBodyJson1["type"] = sfge::ComponentType::BODY2D;
	rigidBodyJson1["body_type"] = p2BodyType::DYNAMIC;

	circleColliderJson;
	circleColliderJson["name"] = "Circle Collider";
	circleColliderJson["type"] = sfge::ComponentType::COLLIDER2D;
	circleColliderJson["collider_type"] = sfge::ColliderType::CIRCLE;
	circleColliderJson["radius"] = 70;
	circleColliderJson["sensor"] = false;

	//entities[0]["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson};
	entityBody3["components"] = { transformJson1, circleShapeJson, rigidBodyJson1, circleColliderJson };

	sceneJson["entities"] = { entityBody1, entityBody2, entityBody3 };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "GravityTest"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(FinalNotWorking, AABBContact)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "AABBContact";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "ContactAABB"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(FinalNotWorking, QuadTree)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "QuadTree";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "QuadTreeTest"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(FinalNotWorking, CollisionDetection)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "CollisionDetection";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "ContactCirclesTest"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(FinalNotWorking, CollisionCirclePlan)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "CollisionCirclePlan";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "BallFallingTest"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

TEST(FinalNotWorking, CollisionCircleCircle)
{
	// 4 body with different gravity
	sfge::Engine engine;
	auto config = std::make_unique<sfge::Configuration>();
	config->gravity = p2Vec2(0.0f, 0.0f);
	engine.Init(std::move(config));

	auto* sceneManager = engine.GetSceneManager();

	json sceneJson;
	sceneJson["name"] = "CollisionCircleCircle";

	sceneJson["entities"] = { /*entityBody1, entityBody2*/ };
	sceneJson["systems"] = json::array({
			{
				{"systemClassName", "CollisionCircleTest"}
			}
		}
	);
	sceneManager->LoadSceneFromJson(sceneJson);
	engine.Start();
}

