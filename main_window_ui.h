#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H

#include "utility.h"
#include "upper_view.h"

class MainWindowUI
{
public:
    QHBoxLayout* layout;
    QWidget* central_widget;
    UpperView* upper_view;

    void setup_ui(QMainWindow* main_window)
    {
        if (main_window->objectName().isEmpty())
            main_window->setObjectName(QString::fromUtf8("main_window"));

        central_widget = new QWidget(main_window);
        // set the object name of private member for user to access
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        
        // set properties for main window
        QMetaObject::connectSlotsByName(main_window);
        QIcon icon = QIcon();
        icon.addFile(QString::fromStdString(get_image_path(IMAGE_MET_ICO)));
        main_window->setWindowIcon(icon);
        main_window->resize(1920, 1080);
        main_window->setCentralWidget(central_widget);
        main_window->setWindowTitle("MCU Controller");
        main_window->setStyleSheet("QMainWindow > QWidget { background-color: rgb(100, 100, 100); }");
        main_window->showMaximized();

        // create views
        upper_view = new UpperView;
        
        // add views
        layout = new QHBoxLayout();
        layout->addWidget(upper_view);
        central_widget->setLayout(layout);
    }
};

#endif