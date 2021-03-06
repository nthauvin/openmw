#ifndef CSV_WIDGET_PUSHBUTTON_H
#define CSV_WIDGET_PUSHBUTTON_H

#include <QPushButton>

namespace CSVWidget
{
    class PushButton : public QPushButton
    {
            Q_OBJECT

        public:

            enum Type
            {
                Type_TopMode, // top level button for mode selector panel
                Type_Mode, // mode button
                Type_Toggle
            };

        private:

            bool mKeepOpen;
            Type mType;
            QString mToolTip;

        private:

            void setExtendedToolTip();

        protected:

            virtual void keyPressEvent (QKeyEvent *event);

            virtual void keyReleaseEvent (QKeyEvent *event);

            virtual void mouseReleaseEvent (QMouseEvent *event);

        public:

            /// \param push Do not maintain a toggle state
            PushButton (const QIcon& icon, Type type, const QString& tooltip = "",
                QWidget *parent = 0);

            /// \param push Do not maintain a toggle state
            PushButton (Type type, const QString& tooltip = "",
                QWidget *parent = 0);

            bool hasKeepOpen() const;

            /// Return tooltip used at construction (without any button-specific modifications)
            QString getBaseToolTip() const;
    };
}

#endif
