//
// Created by nunwan on 14/06/2020.
//

#include "Engine.hpp"


Engine::Engine()
{
    mWindow = std::make_shared<Window>();
}


void Engine::initSystems()
{
    mRenderMapSystem = RegisterSystem<RenderMapSystem>(this);
    UseComponent<RenderMapSystem, Map>();
    UseComponent<RenderMapSystem, Transform>();
    UseComponent<RenderMapSystem, Render>();
    mRenderOthersSystem = RegisterSystem<RenderOthersSystem>(this);
    UseComponent<RenderOthersSystem, Transform>();
    UseComponent<RenderOthersSystem, Render>();
    UseComponent<RenderOthersSystem, NotMap>();
    mInputHandler = RegisterSystem<InputHandler>(this);
    mInputHandler->Init();
}


void Engine::initComponents()
{
    RegisterComponent<Render>();
    RegisterComponent<Transform>();
    RegisterComponent<Map>();
    RegisterComponent<NotMap>();
    RegisterComponent<Playable>();
    RegisterComponent<RigidBody>();
}


void Engine::render()
{
    mWindow->clear();
    mRenderMapSystem->render();
    mRenderOthersSystem->render();
    mWindow->refresh();
}


int Engine::update()
{
    mWindow->nextEvent(0, true);
    return mInputHandler->process_key(mWindow->event);
}


const std::shared_ptr<Window> &Engine::getMWindow() const
{
    return mWindow;
}


void Engine::level_enable(std::shared_ptr<Level> level)
{
    Entity** map = level->getMMap();
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            AddComponent(map[i][j], Map());
        }
    }
    for (auto const& entity : level->getMObjects()) {
        AddComponent(entity, NotMap());
    }
    for (auto const& entity : level->getMMobs()) {
        AddComponent(entity, NotMap());
    }
}


void Engine::level_disable(std::shared_ptr<Level> level)
{
    Entity** map = level->getMMap();
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            DelComponent<Map>(map[i][j]);
        }
    }
    for (auto const& entity : level->getMObjects()) {
        DelComponent<NotMap>(entity);
    }
    for (auto const& entity : level->getMMobs()) {
        DelComponent<NotMap>(entity);
    }

}
