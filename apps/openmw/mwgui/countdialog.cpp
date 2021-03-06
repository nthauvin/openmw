#include "countdialog.hpp"

#include <boost/lexical_cast.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"

namespace MWGui
{
    CountDialog::CountDialog() :
        WindowModal("openmw_count_window.layout")
    {
        getWidget(mSlider, "CountSlider");
        getWidget(mItemEdit, "ItemEdit");
        getWidget(mItemText, "ItemText");
        getWidget(mLabelText, "LabelText");
        getWidget(mOkButton, "OkButton");
        getWidget(mCancelButton, "CancelButton");

        mCancelButton->eventMouseButtonClick += MyGUI::newDelegate(this, &CountDialog::onCancelButtonClicked);
        mOkButton->eventMouseButtonClick += MyGUI::newDelegate(this, &CountDialog::onOkButtonClicked);
        mItemEdit->eventEditTextChange += MyGUI::newDelegate(this, &CountDialog::onEditTextChange);
        mSlider->eventScrollChangePosition += MyGUI::newDelegate(this, &CountDialog::onSliderMoved);
        // make sure we read the enter key being pressed to accept multiple items
        mItemEdit->eventEditSelectAccept += MyGUI::newDelegate(this, &CountDialog::onEnterKeyPressed);
    }

    void CountDialog::open(const std::string& item, const std::string& message, const int maxCount)
    {
        setVisible(true);

        mLabelText->setCaptionWithReplacing(message);

        MyGUI::IntSize viewSize = MyGUI::RenderManager::getInstance().getViewSize();

        mSlider->setScrollRange(maxCount);
        mItemText->setCaption(item);

        int width = std::max(mItemText->getTextSize().width + 128, 320);
        setCoord(viewSize.width/2 - width/2,
                viewSize.height/2 - mMainWidget->getHeight()/2,
                width,
                mMainWidget->getHeight());

        // by default, the text edit field has the focus of the keyboard
        MWBase::Environment::get().getWindowManager()->setKeyFocusWidget(mItemEdit);

        mSlider->setScrollPosition(maxCount-1);
        mItemEdit->setCaption(boost::lexical_cast<std::string>(maxCount));
    }

    void CountDialog::cancel() //Keeping this here as I don't know if anything else relies on it.
    {
        exit();
    }

    void CountDialog::exit()
    {
        setVisible(false);
    }

    void CountDialog::onCancelButtonClicked(MyGUI::Widget* _sender)
    {
        cancel();
    }

    void CountDialog::onOkButtonClicked(MyGUI::Widget* _sender)
    {
        eventOkClicked(NULL, mSlider->getScrollPosition()+1);

        setVisible(false);
    }

    // essentially duplicating what the OK button does if user presses
    // Enter key
    void CountDialog::onEnterKeyPressed(MyGUI::EditBox* _sender)
    {
        eventOkClicked(NULL, mSlider->getScrollPosition()+1);

        setVisible(false);
    }

    void CountDialog::onEditTextChange(MyGUI::EditBox* _sender)
    {
        if (_sender->getCaption() == "")
            return;

        unsigned int count;
        try
        {
            count = boost::lexical_cast<unsigned int>(_sender->getCaption());
        }
        catch (std::bad_cast&)
        {
            count = 1;
        }
        if (count > mSlider->getScrollRange())
        {
            count = mSlider->getScrollRange();
        }
        mSlider->setScrollPosition(count-1);
        onSliderMoved(mSlider, count-1);
    }

    void CountDialog::onSliderMoved(MyGUI::ScrollBar* _sender, size_t _position)
    {
        mItemEdit->setCaption(boost::lexical_cast<std::string>(_position+1));
    }
}
