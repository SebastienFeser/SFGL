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
#include <engine/config.h>
#include <engine/scene.h>
#include <utility/json_utility.h>
#include <gtest/gtest.h>

TEST(Physics, TestVector) //TEST = Structure de donnée qui définit un test
{
    sfge::Engine engine; //Creation d'une instance engine
    std::unique_ptr<sfge::Configuration> initConfig = std::make_unique<sfge::Configuration>(); //Création d'un unique pointer initConfig (qui est un nouvel objet)
    initConfig->gravity = p2Vec2(0,0); //On set les données du pointeur
    initConfig->devMode = false;
    initConfig->maxFramerate = 0;
    engine.Init(std::move(initConfig)); //Appel une fonction init pour l'engine
    json sceneJson = {
            { "name", "Test Vector" }
    }; //Création d'un nouvel object json, comme value "name", il a "Test Vector"
    json systemJson = {
            {"script_path", "scripts/vector_system.py"}
    }; //Création d'un nouveau json, il donne à "script_path", la valeur scripts/vector_system.py qui link au fichier python 
    sceneJson["systems"] = json::array({ systemJson }); //Création d'un array de json pour lui donner toutes les données de system Json (en gros tous les scripts python)
    auto* sceneManager = engine.GetSceneManager(); //Création d'un pointeur qui garde la valeur de engine.GetSceneManager
    sceneManager->LoadSceneFromJson(sceneJson); //Donne la valeur de sceneJson à sceneManager

    engine.Start();
}