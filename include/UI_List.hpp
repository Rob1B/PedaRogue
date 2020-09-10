//
// Created by nunwan on 03/09/2020.
//

#ifndef PEDAROGUE_UI_LIST_HPP
#define PEDAROGUE_UI_LIST_HPP

#include <memory>
#include <Window.hpp>
#include <unordered_map>
#include "Types.hpp"


class Item {
private:
    std::string mLabel;
    int mNumber;
    Color mDefaultColor, mSelectedColor;
    Color* mColor;


public:
    Item(Color default_color = {0xff, 0xff, 0xff}, Color selected_color = {0, 0, 0xff});
    Item(std::string label, int number, Color default_color = {0xff, 0xff, 0xff}, Color selected_color = {0, 0, 0xff});


    void render(std::shared_ptr<Window> window, int x, int y, int x_max);

    void selected();

    void unselected();
};

class Box {
    int h, w, x;
protected:
    int y;
public:
    Box();
    Box(int width, int height, int x_begin, int y_begin);

    virtual void render(std::shared_ptr<Window> window);

    virtual void select_next() {};
    virtual void select_previous() {};
};

class UI_List : public Box
{
public:
    UI_List(const std::string &mTitle);

    void render(std::shared_ptr<Window> window) override;
    void createList(std::unordered_map<std::string, int> list);

    void clear_item(std::shared_ptr<Window> window, int y);


    void select_next() override;

    void select_previous() override;


private:
    std::vector<Item> mItems;
    std::string mTitle;
    int mCurrentSelected;

    void select_item(int offset);
};






#endif //PEDAROGUE_UI_LIST_HPP
