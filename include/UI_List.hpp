//
// Created by nunwan on 03/09/2020.
//

#ifndef PEDAROGUE_UI_LIST_HPP
#define PEDAROGUE_UI_LIST_HPP

#include <memory>
#include <Window.hpp>
#include <unordered_map>
#include "Types.hpp"
#include "CommandProcessor.hpp"


/**
 * Class describing an item of a list
 */
class Item {
private:
    /**
     * Name/Label of the item
     */
    std::string mLabel;

    /**
     * Number of the iteration of the item
     */
    int mNumber;

    /**
     *  Color of the item when it is not selected and selected
     */
    Color mDefaultColor, mSelectedColor;

    /**
     * Current color of the item
     */
    Color* mColor;

    Command* mCommand;


public:
    virtual ~Item();

    /**
     * @brief                   Constructor of Item without label and number given
     * @param default_color     Color of unselected item
     * @param selected_color    Color of selected item
     */
    Item(Color default_color = {0xff, 0xff, 0xff}, Color selected_color = {0, 0, 0xff});

    /**
     * @brief                   Constructor of item with the precision of label and number
     * @param label             the name of the item
     * @param number            Number of this item
     * @param default_color     Color of unselected item
     * @param selected_color    Color of selected item
     */
    Item(std::string label, int number, Command* command = nullptr, Color default_color = {0xff, 0xff, 0xff},
         Color selected_color = {0, 0, 0xff});

    /**
     * @brief                   Display the item at screen
     * @param window            the Display manager
     * @param x                 x coordinate of the left of the label
     * @param y                 y coordinate of the label
     * @param x_max             x coordinate of the end of the label (where the number will be displayed)
     */
    void render(std::shared_ptr<Window> window, int x, int y, int x_max);

    /**
     * Treat the item to be considered as selected
     */
    void selected();

    /**
     * Treat the item to be considered as unselected
     */
    void unselected();


    Command * choosen();
};

/**
 * @brief   Class which describe a box to display at screen
 */
class Box {
protected:
    /**
     * Coordinate of the box
     */
    int h, w, x, y;

public:
    /**
     * Default constructor of Box
     */
    Box();

    /**
     * @brief           Constructor of Box with coordinates
     * @param width     Width of the box
     * @param height    height of the box
     * @param x_begin   x coordinate of left corner of the box
     * @param y_begin   y coordinate of left corner of the box
     */
    Box(int width, int height, int x_begin, int y_begin);

    /**
     * @brief           Display box at screen
     * @param window    Window to update with the box
     */
    virtual void render(std::shared_ptr<Window> window);

    /**
     * Interface of item selection for ListUIV
     */
    virtual void select_next() {};

    /**
     * Interface of item selection for ListUIV
     */
    virtual void select_previous() {};

    virtual Command * choose() {};
    virtual bool isMPermanent() const = 0;
};


/**
 * @brief   Class which describe a List to display at screen
 */
class UI_List : public Box
{
public:
    /**
     * @brief   Construct a List for UI with the Title
     */
    UI_List(const std::string &mTitle, bool permanent);

    /**
     * @brief           Display the list at screen
     * @param window    pointer to the window to display the list
     */
    void render(std::shared_ptr<Window> window) override;

    /**
     * @brief           create the list with the item described in list
     * @param list      list of items (key:value) which will become the list
     */
    virtual void createList(const std::unordered_map<std::string, int>& list);

    void clear_item(std::shared_ptr<Window> window, int y);

    void push_item(std::string label, int number, Command* command);


    /**
     * @brief   Select the next item on the list
     */
    void select_next() override;

    /**
     * @brief   Select the previous item on the list
     */
    void select_previous() override;

    Command * choose() override;

    void clear_items();

    bool isMPermanent() const override;

private:

    /**
     * Title of the list
     */
    std::string mTitle;

    /**
     * @brief           Select the item at id : currentId + offset
     * @param offset    Deplacement of the item to select
     */
    void select_item(int offset);

    bool mPermanent;

protected:
/**
 * Vector of each line of the list, each item
 */
std::vector<Item> mItems;
/**
 * The id of the item which is selected
 */
int mCurrentSelected;
};






#endif //PEDAROGUE_UI_LIST_HPP
