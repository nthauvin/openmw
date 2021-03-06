#ifndef MGUI_CONTAINER_H
#define MGUI_CONTAINER_H

#include "windowbase.hpp"
#include "referenceinterface.hpp"

#include "itemmodel.hpp"

namespace MWWorld
{
    class Environment;
}

namespace MyGUI
{
    class Gui;
    class Widget;
}

namespace MWGui
{
    class WindowManager;
    class ContainerWindow;
    class ItemView;
    class SortFilterItemModel;
}


namespace MWGui
{
    class DragAndDrop
    {
    public:
        bool mIsOnDragAndDrop;
        MyGUI::Widget* mDraggedWidget;
        ItemModel* mSourceModel;
        ItemView* mSourceView;
        SortFilterItemModel* mSourceSortModel;
        ItemStack mItem;
        int mDraggedCount;

        DragAndDrop();

        void startDrag (int index, SortFilterItemModel* sortModel, ItemModel* sourceModel, ItemView* sourceView, int count);
        void drop (ItemModel* targetModel, ItemView* targetView);

        void finish();
    };

    class ContainerWindow : public WindowBase, public ReferenceInterface
    {
    public:
        ContainerWindow(DragAndDrop* dragAndDrop);

        void open(const MWWorld::Ptr& container, bool loot=false);
        virtual void close();

        virtual void resetReference();

        virtual void exit();

    private:
        DragAndDrop* mDragAndDrop;

        bool mPickpocketDetected;

        MWGui::ItemView* mItemView;
        SortFilterItemModel* mSortModel;
        ItemModel* mModel;
        int mSelectedItem;

        MyGUI::Button* mDisposeCorpseButton;
        MyGUI::Button* mTakeButton;
        MyGUI::Button* mCloseButton;

        void onItemSelected(int index);
        void onBackgroundSelected();
        void dragItem(MyGUI::Widget* sender, int count);
        void dropItem();
        void onCloseButtonClicked(MyGUI::Widget* _sender);
        void onTakeAllButtonClicked(MyGUI::Widget* _sender);
        void onDisposeCorpseButtonClicked(MyGUI::Widget* sender);
        void onKeyPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);

        /// @return is taking the item allowed?
        bool onTakeItem(const ItemStack& item, int count);

        virtual void onReferenceUnavailable();
    };
}
#endif // CONTAINER_H
