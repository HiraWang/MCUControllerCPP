#ifndef UPPER_VIEW_H
#define UPPER_VIEW_H

#include <QPushButton>
#include <QHBoxLayout>

class UpperView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    UpperView(QWidget* parent = nullptr);
    ~UpperView();

private:
    void setup_ui();
    QHBoxLayout* layout;
    QPushButton* button;
};

#endif
