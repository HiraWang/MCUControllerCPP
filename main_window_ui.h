#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H

#include "utility.h"
#include "views/upper_view.h"
#include "views/bottom_view.h"

extern std::string IMAGE_MET_ICO;

class MainWindowUI
{
public:
    QVBoxLayout* layout;
    QWidget* central_widget;
    UpperView* upper_view;
    BottomView* bottom_view;

    void setup_ui(QMainWindow* main_window)
    {
        if (main_window->objectName().isEmpty())
            main_window->setObjectName(QString::fromUtf8("main_window"));

        central_widget = new QWidget(main_window);
        // set the object name of private member for user to access
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        
        QMetaObject::connectSlotsByName(main_window);
        QIcon icon = QIcon();
        icon.addFile(QString::fromStdString(get_abs_path(IMAGE_MET_ICO)));
        QString style_sheet = QString("QMainWindow > QWidget { background-color: ") +
                              COLOR_DEEP_GRAY +
                              QString("; }");

        // set properties for main window
        main_window->setWindowIcon(icon);
        main_window->resize(1920, 1080);
        main_window->setCentralWidget(central_widget);
        main_window->setWindowTitle("MCU Controller");
        main_window->setStyleSheet(style_sheet);
        main_window->showFullScreen();

        // create views
        upper_view = new UpperView(main_window);
        bottom_view = new BottomView(main_window);

        // add views
        layout = new QVBoxLayout(central_widget);
        layout->addWidget(upper_view, 0, Qt::AlignTop);
        layout->addWidget(bottom_view, 0, Qt::AlignTop);
        central_widget->setLayout(layout);
    }
};

#endif