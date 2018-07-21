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
#include <sstream>

#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <python/python_engine.h>
#include <engine/log.h>
#include <engine/scene.h>
#include <input/input.h>
#include <audio/audio.h>
#include <graphics/shape.h>
#include <physics/physics.h>
#include <python/pycomponent.h>

#include <utility/file_utility.h>
#include <utility/time_utility.h>






namespace sfge
{

PYBIND11_EMBEDDED_MODULE(SFGE, m)
{


	py::class_<Engine> engine(m, "Engine");

	py::class_<Module> module(m, "Module");

	py::class_<SceneManager> sceneManager(m, "SceneManager");
	sceneManager
		.def("load_scene", &SceneManager::LoadSceneFromName)
		.def("get_scenes", &SceneManager::GetAllScenes);

	py::class_<InputManager> inputManager(m, "InputManager");
	inputManager
		.def_property_readonly("keyboard", &InputManager::GetKeyboardManager, py::return_value_policy::reference);

	py::class_<KeyboardManager> keyboardManager(m, "KeyboardManager");
	keyboardManager
		.def("is_key_held", &KeyboardManager::IsKeyHeld)
		.def("is_key_down", &KeyboardManager::IsKeyDown)
		.def("is_key_up", &KeyboardManager::IsKeyUp);

	py::enum_<sf::Keyboard::Key>(keyboardManager, "Key")
		.value("Space", sf::Keyboard::Space)
		.value("Up", sf::Keyboard::Up)
		.value("Down", sf::Keyboard::Down)
		.value("Left", sf::Keyboard::Left)
		.value("Right", sf::Keyboard::Right)
		.export_values();

	py::class_<PythonEngine> pythonEngine(m, "PythonEngine");

	py::class_<Component, PyComponent> component(m, "Component");
	component
		.def(py::init<PythonEngine*, Entity>(), py::return_value_policy::reference)
		.def("init", &Component::Init)
		.def("update", &Component::Update)
		.def_property_readonly("entity", &Component::GetEntity)
		.def("get_component", &Component::GetComponent)
	
		.def("on_trigger_enter", &Component::OnTriggerEnter)
		.def("on_collision_enter", &Component::OnCollisionEnter)
		.def("on_trigger_exit", &Component::OnTriggerExit)
		.def("on_collision_exit", &Component::OnCollisionExit)
	;

	py::enum_<ComponentType>(component, "ComponentType")
		.value("PyComponent", ComponentType::PYCOMPONENT)
		.value("Shape", ComponentType::SHAPE)
		.value("Body", ComponentType::BODY2D)
		.value("Sprite", ComponentType::SPRITE)
		.value("Sound", ComponentType::SOUND)
		.export_values();

	py::class_<Transform2d> transform(m, "Transform");
	transform
		.def_readwrite("euler_angle", &Transform2d::EulerAngle)
		.def_readwrite("position", &Transform2d::Position)
		.def_readwrite("scale", &Transform2d::Scale);

	py::class_<ColliderData> collider(m, "Collider");
	collider
		.def_readonly("body", &ColliderData::body)
		.def_readonly("entity", &ColliderData::entity);
	
	py::class_<Body2d> body2d(m, "Body2d");
	body2d
		.def_property("velocity", &Body2d::GetLinearVelocity, &Body2d::SetLinearVelocity)
		.def("apply_force", &Body2d::ApplyForce)
		.def_property_readonly("body_type", &Body2d::GetType)
		.def_property_readonly("mass", &Body2d::GetMass);

	py::class_<b2Body,std::unique_ptr<b2Body, py::nodelete>> body(m, "Body");
	body
		.def_property("velocity", &b2Body::GetLinearVelocity, &b2Body::SetLinearVelocity)
		.def("apply_force", &b2Body::ApplyForce)
		.def_property_readonly("body_type", &b2Body::GetType)
		.def_property_readonly("mass", &b2Body::GetMass);
		
	py::enum_<b2BodyType>(body, "BodyType")
		.value("STATIC_BODY", b2_staticBody)
		.value("KINEMATIC_BODY", b2_kinematicBody)
		.value("DYNAMIC_BODY", b2_dynamicBody)
		.export_values();
		
	py::class_<Sound> sound(m, "Sound");
	sound
		.def("play", &Sound::Play)
		.def("stop", &Sound::Stop);
	
	py::class_<Shape, std::unique_ptr<Shape, py::nodelete>> shape(m, "Shape");
	shape
		.def("set_fill_color", &Shape::SetFillColor);

	//Utility
	py::class_<sf::Color> color(m, "Color");
	color
		.def_readwrite("r", &sf::Color::r)
		.def_readwrite("g", &sf::Color::g)
		.def_readwrite("b", &sf::Color::b)
		.def_readwrite("a", &sf::Color::a)
		.def_readonly_static("Black", &sf::Color::Black)
		.def_readonly_static("White", &sf::Color::White)
		.def_readonly_static("Red", &sf::Color::Red)
		.def_readonly_static("Green", &sf::Color::Green)
		.def_readonly_static("Blue", &sf::Color::Blue)
		.def_readonly_static("Yellow", &sf::Color::Yellow)
		.def_readonly_static("Magenta", &sf::Color::Magenta)
		.def_readonly_static("Cyan", &sf::Color::Cyan)
		.def_readonly_static("Transparent", &sf::Color::Transparent);

	py::class_<Timer> timer(m, "Timer");
	timer
		.def(py::init<float, float>())
		.def("update", &Timer::Update)
		.def("reset", &Timer::Reset)
		.def("get_current", &Timer::GetCurrent)
		.def("get_current_time", &Timer::GetCurrentTime)
		.def("is_over", &Timer::IsOver);

	py::class_<sf::Vector2f> vector2f(m, "Vector2f");
	vector2f
		.def(py::init<float, float>())
		.def(py::init<>())
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self - py::self)
		.def(py::self -= py::self)
		.def(py::self * float())
		.def_readwrite("x", &sf::Vector2f::x)
		.def_readwrite("y", &sf::Vector2f::y);

	py::class_<b2Vec2> b2vec2(m, "b2Vec2");
	b2vec2
		.def(py::init<>())
		.def(py::init<float, float>())
		.def_readwrite("x", &b2Vec2::x)
		.def_readwrite("y", &b2Vec2::y)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= float());
		
}





PythonEngine::PythonEngine(Engine & engine) :
	Module(engine)
{
	m_PyComponents.reserve(INIT_ENTITY_NMB * 4);
}

void PythonEngine::Init()
{
	Log::GetInstance()->Msg("Initialise the python embed interpretor");
	py::initialize_interpreter();
	//Adding refecrence to c++ engine modules

	py::module sfgeModule = py::module::import("SFGE");
	sfgeModule.attr("engine")=  py::cast(&m_Engine);

	if(auto sceneManagerPtr = m_Engine.GetSceneManager().lock())
		sfgeModule.attr("scene_manager") = py::cast(sceneManagerPtr.get(), py::return_value_policy::reference);
	if(auto inputManagerPtr = m_Engine.GetInputManager().lock())
		sfgeModule.attr("input_manager") = py::cast(inputManagerPtr.get(), py::return_value_policy::reference);
		
	LoadScripts();
}


void PythonEngine::Update(sf::Time dt)
{
	for (auto pyComponent : m_PyComponents)
	{
		pyComponent->Update(dt.asSeconds());
	}
}


void PythonEngine::Destroy()
{
	m_PythonInstanceMap.clear();
	Log::GetInstance()->Msg("Finalize the python embed interpretor");
	py::finalize_interpreter();
}

void PythonEngine::Clear()
{
	m_PythonInstanceMap.clear();
}

ModuleId PythonEngine::LoadPyModule(std::string& moduleFilename)
{
	const auto folderLastIndex = moduleFilename.find_last_of('/');
	std::string filename = moduleFilename.substr(folderLastIndex + 1, moduleFilename.size());
	const std::string::size_type filenameExtensionIndex = filename.find_last_of('.');
	std::string moduleName = filename.substr(0, filenameExtensionIndex);
	const std::string extension = filename.substr(filenameExtensionIndex);
	const std::string className = module2class(moduleName);
	if (IsRegularFile(moduleFilename) && extension == ".py")
	{
		if (m_PythonModuleIdMap.find(moduleFilename) != m_PythonModuleIdMap.end())
		{
			const ModuleId moduleId = m_PythonModuleIdMap[moduleFilename];
			if (moduleId == 0U)
			{
				std::ostringstream oss;
				oss << "Python script: " << moduleFilename << " has id 0";
				Log::GetInstance()->Error(oss.str());
			}
			return moduleId;
		}
		else
		{
			try
			{

				
				py::object globals = py::globals();

				globals[moduleName.c_str()] = import(moduleName, moduleFilename, globals);
				m_PyModuleNameMap[m_IncrementalModuleId] = moduleName;
				m_PythonModuleIdMap[moduleFilename] = m_IncrementalModuleId;
				m_PyComponentClassNameMap[m_IncrementalModuleId] = className;
				{
					std::ostringstream oss;
					oss << "Loading module: " << moduleName << " with Component: " << className << ",\n";
					Log::GetInstance()->Msg(oss.str());
				}
			}
			catch (const std::runtime_error& e)
			{
				std::stringstream oss;
				oss << "[PYTHON ERROR] on script file: " << moduleFilename << "\n" << e.what();
				Log::GetInstance()->Error(oss.str());
				return 0U;
			}
			m_IncrementalModuleId++;
			return m_IncrementalModuleId - 1;
		}
	}
	return 0U;
}


InstanceId PythonEngine::LoadPyComponent(ModuleId moduleId, Entity entity)
{
	std::string className = m_PyComponentClassNameMap[moduleId];
	if(m_PyComponentClassNameMap.find(moduleId) != m_PyComponentClassNameMap.end())
	{
		
		try
		{
			auto moduleObj = py::globals()[m_PyModuleNameMap[moduleId].c_str()];
			m_PythonInstanceMap[m_IncrementalInstanceId] = 
				moduleObj.attr(className.c_str())(this, entity);
			//Adding the important components

			if (auto entityManager = m_Engine.GetEntityManager().lock())
			{
				//First the transform
				if (entityManager->HasComponent(entity, ComponentType::TRANSFORM))
				{
					if (auto transformManager = m_Engine.GetTransform2dManager().lock())
					{
						m_PythonInstanceMap[m_IncrementalInstanceId].attr("transform") = transformManager->GetComponent(entity);
					}
				}
			}
			auto pyComponent = GetPyComponent(m_IncrementalInstanceId);
			if (pyComponent)
			{
				m_PyComponents.push_back(pyComponent);
			}
			else
			{
				std::ostringstream oss;
				oss << "[Python Error] Could not load the PyComponent* out of the instance";
				Log::GetInstance()->Error(oss.str());
                return INVALID_INSTANCE;
			}
			m_IncrementalInstanceId++;
			return m_IncrementalInstanceId - 1;
		}
		catch(std::runtime_error& e)
		{
			std::stringstream oss;
			oss << "[PYTHON ERROR] trying to instantiate class: " << className << "\n" << e.what();
			Log::GetInstance()->Error(oss.str());
		}
	}
	return 0U;
	
}
void PythonEngine::Collect()
{
}

void PythonEngine::LoadScripts(std::string dirname)
{
	std::function<void(std::string)> LoadAllPyModules;
 	LoadAllPyModules = [&LoadAllPyModules, this](std::string entry)
	{
		if (IsRegularFile(entry))
		{
			
			if(LoadPyModule(entry))
			{
				std::ostringstream oss;
				oss << "Loading script: " << entry << "\n";
				Log::GetInstance()->Msg(oss.str());
			}
		}

		if (IsDirectory(entry))
		{
			IterateDirectory(entry, LoadAllPyModules);
		}
	};
	IterateDirectory(dirname, LoadAllPyModules);
	//Spread the class name in all the scripts
	for(auto& pyModuleObjPair : m_PyModuleNameMap)
	{
		const auto pyModuleId = pyModuleObjPair.first;
		auto pyModuleName = pyModuleObjPair.second;
		for(auto& importedClassNamePair : m_PyComponentClassNameMap)
		{
			auto importedModuleId = importedClassNamePair.first;
			auto importedClassName = importedClassNamePair.second;
			if(importedModuleId != pyModuleId)
			{
				try
				{
					auto moduleObj = py::globals()[pyModuleName.c_str()];
					auto importedModuleObj = py::globals()[m_PyModuleNameMap[importedModuleId].c_str()];
					moduleObj.attr(importedClassName.c_str()) = importedModuleObj.attr(importedClassName.c_str());
				}
				catch(std::runtime_error& e)
				{
					std::ostringstream oss;
					oss << "[PYTHON ERROR] Could not import class: " << importedClassName << " into module: " << pyModuleId << " with error: " << e.what();
					Log::GetInstance()->Error(oss.str());
				}
			}
		}
	}
}


PyComponent* PythonEngine::GetPyComponent(InstanceId instanceId)
{
	if(m_PythonInstanceMap.find(instanceId) != m_PythonInstanceMap.end())
	{
		return m_PythonInstanceMap[instanceId].cast<PyComponent*>();
	}
	else
	{
		std::ostringstream oss;
		oss << "[Python Error] Could not find instance Id: " << instanceId << " in the pythonInstanceMap";
		Log::GetInstance()->Error(oss.str());
	}
	return nullptr;
}

void PythonEngine::OnTriggerEnter(Entity entity, ColliderData * colliderData)
{
	for (auto& pyComponent : m_PyComponents)
	{
		if (pyComponent->GetEntity() == entity)
		{
			pyComponent->OnTriggerEnter(colliderData);
		}
	}
}

void PythonEngine::OnTriggerExit(Entity entity, ColliderData * colliderData)
{
	for (auto& pyComponent : m_PyComponents)
	{
		if (pyComponent->GetEntity() == entity)
		{
			pyComponent->OnTriggerExit(colliderData);
		}
	}
}

void PythonEngine::OnCollisionEnter(Entity entity, ColliderData * colliderData)
{
	for (auto& pyComponent : m_PyComponents)
	{
		if (pyComponent->GetEntity() == entity)
		{
			pyComponent->OnCollisionEnter(colliderData);
		}
	}
}

void PythonEngine::OnCollisionExit(Entity entity, ColliderData * colliderData)
{
	for (auto& pyComponent : m_PyComponents)
	{
		if (pyComponent->GetEntity() == entity)
		{
			pyComponent->OnCollisionExit(colliderData);
		}
	}
}



}
