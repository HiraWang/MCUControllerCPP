#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H
#endif

#include <QtWidgets/QWidget>
#include <utility.h>

class MainWindowUI
{
public:
    QWidget* central_widget;

    void setupUi(QMainWindow* MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

        central_widget = new QWidget(MainWindow);
        // set the object name of private member for user to access
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        
        // set properties for main window
        QMetaObject::connectSlotsByName(MainWindow);
        QIcon icon = QIcon();
        icon.addFile(QString::fromStdString(get_image_path(IMAGE_MET_ICO)));
        MainWindow->setWindowIcon(icon);
        MainWindow->resize(1920, 1080);
        MainWindow->setCentralWidget(central_widget);
        MainWindow->setWindowTitle("MCU Controller");
        MainWindow->setStyleSheet("QMainWindow > QWidget { background-color: rgb(100, 100, 100); }");
        MainWindow->showMaximized();
    }
};