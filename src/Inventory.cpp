//
// Created by nunwan on 04/09/2020.
//

#include "Inventory.hpp"
#include "Engine.hpp"


Inventory::Inventory(Entity &entity, Engine *engine, std::string &title)
{
    mEngine = engine;
    mEntity = entity;
    mInventory_UI = mEngine->mUI.create_list(title);
}


Inventory::~Inventory()
{
    mEngine->mUI.destroy_list(mInventory_UI);
}


void Inventory::display()
{
    mInventory_UI->createList(mItems);
    mEngine->mUI.push_list(mInventory_UI);
}


void Inventory::refresh_list()
{
    // Surety Check but usually not necessary if correctly use
    if (mEngine->HasComponent<Container>(mEntity)) {
        auto& list_items = mEngine->GetComponent<Container>(mEntity);
        for (auto const& pair : list_items.contains) {
            if (mItems.count(pair.first)) {
                mItems[pair.first] = pair.second.size();
            } else {
                mItems.insert({pair.first, pair.second.size()});
            }
        }
    }
}


void OpenInventoryCommand::execute(Engine *engine)
{
    engine->getMInventoryPlayerSystem()->refresh_list();
    engine->getMInventoryPlayerSystem()->display();
}
