#include "tree.h"

MetTree::MetTree(MetTreeStyle style,
                 int w,
                 int h,
                 QWidget* parent) :
    style(style),
    QTreeWidget(parent)
{
    LoadStyleSheet();
    setStyleSheet(style_sheet);
    setIndentation(20);
    setColumnCount(3);
    setFixedHeight(h);
    setColumnWidth(0, 120);
    setColumnWidth(1, 80);
    setColumnWidth(2, 20);

    QStringList column_title;
    column_title.append("Name");
    column_title.append("Value");
    column_title.append("Unit");
    setHeaderLabels(column_title);

    QStringList list_1[2] = { { "pump", "reglo icc" }, { "pulse gen", "g1b" } };
    QStringList list_2[2] = { { "rpm", "dir" },
                              { "freq", "pw", "voltage", "offset" } };
    QStringList list_3[2] = { { "rpm", "" },
                              { "Hz", "ms", "v", "v" } };

    for (int i = 0; i < 2; i++) {
        QTreeWidgetItem* item_1 = new QTreeWidgetItem(this);
        item_1->setText(0, list_1[i][0]);
        item_1->setText(1, list_1[i][1]);
        item_1->setBackground(0, Qt::green);

        if (list_1[i][0] == "pump") {
            for (int c = 0; c < 2; c++) {
                QTreeWidgetItem* item_channel = new QTreeWidgetItem(item_1);
                item_channel->setText(0, "channel");
                item_channel->setText(1, QString::number(c + 1));
                item_1->addChild(item_channel);
                for (int j = 0; j < 2; j++) {
                    QTreeWidgetItem* item_2 = new QTreeWidgetItem(item_channel);
                    item_2->setText(0, list_2[i][j]);
                    item_2->setText(2, list_3[i][j]);
                    item_channel->addChild(item_2);
                }
                item_channel->setExpanded(true);
            }
        } else if (list_1[i][0] == "pulse gen") {
            for (int j = 0; j < 4; j++) {
                QTreeWidgetItem* item_2 = new QTreeWidgetItem(item_1);
                item_2->setText(0, list_2[i][j]);
                item_2->setText(2, list_3[i][j]);
                item_1->addChild(item_2);
            }
        }
        addTopLevelItem(item_1);
        item_1->setExpanded(true);
    }
}

MetTree::~MetTree()
{

}

void MetTree::LoadStyleSheet()
{
    style_sheet =
        "QTreeView {"
        "background-color: " + style.bkg_color + ";"
        "border-radius: 10px;"
        "border: 2px solid black;"
        "font: " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTreeView::item {"
        "background-color: " + style.bkg_color + ";"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        "font: " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTreeView::item:last {"
        "background-color: " + style.bkg_color + ";"
        "margin-right: -2px;"
        "border-bottom: 2px solid black;"
        "font: " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTreeView::item:hover {"
        "background-color: " + QString(COLOR_GRAY) + ";"
        "border-bottom: 2px solid black;"
        "font: " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTreeView::branch {"
        "background-color: " + QString(COLOR_DEBUG_1) + ";"
        "border-bottom: 2px solid black;"
        "}"
        "QTreeView::branch:has-siblings:!adjoins-item {"
        "background-color: " + QString(COLOR_DEBUG_1) + ";"
        "border-bottom: 2px solid black;"
        //"border-image: url(:/images/BranchT.png) 0;"
        "}"
        "QTreeView::branch:has-siblings:adjoins-item {"
        "background-color: " + QString(COLOR_DEBUG_1) + ";"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        //"border-image: url(:/images/BranchMore.png) 0;"
        "}"
        "QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
        "background-color: " + QString(COLOR_DEBUG_1) + ";"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        //"border-image: url(:/images/BranchEnd.png) 0;"
        "}"
        "QTreeView::branch:has-children:!has-siblings:closed,"
        "QTreeView::branch:closed:has-children:has-siblings {"
        "background-color: " + QString(COLOR_ON_1) + ";"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        "border-image: none;"
        "image: url(:/images/Right.png);"
        "}"
        "QTreeView::branch:open:has-children:!has-siblings,"
        "QTreeView::branch:open:has-children:has-siblings {"
        "background-color: " + QString(COLOR_ON_1) + ";"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        "border-image: none;"
        "image: url(:/images/Down.png);"
        "}"
        "QHeaderView {"
        "background-color: " + QString(COLOR_BLACK) + ";"
        "border: 0px solid black;"
        "border-radius: 10px;"
        "}"
        "QHeaderView:section {"
        "background-color: " + QString(COLOR_GRAY) + ";"
        "border: 2px solid black;"
        "border-top-left-radius: 10px;"
        "border-top-right-radius: 10px;"
        "padding-left: 10px;"
        "margin-left: -2px;"
        "margin-top: -2px;"
        "font: bold " + style.font_size + ";"
        "}"
        "QHeaderView:section:last {"
        "background-color: " + QString(COLOR_GRAY) + ";"
        "border: 2px solid black;"
        "border-top-left-radius: 10px;"
        "border-top-right-radius: 10px;"
        "padding-left: 10px;"
        "margin-left: -2px;"
        "margin-right: -2px;"
        "margin-top: -2px;"
        "font: bold " + style.font_size + ";"
        "}"
        "QScrollBar:vertical {"
        "border-left: 2px solid black;"
        "border-top: 2px solid black;"
        "border-bottom: 2px solid black;"
        "background: " + QString(COLOR_DEEP_GRAY) + ";"
        "width: 25px;"
        "margin: 15px 0 15px 0;"
        "border-radius: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background-color: " + QString(COLOR_GRAY) + ";"
        "min-height: 30px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::handle:vertical:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::sub-line:vertical {"
        "border-left: 2px solid black;"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "height: 15px;"
        "border-top-right-radius: 8px;"
        "subcontrol-position: top;"
        "subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::sub-line:vertical:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::add-line:vertical {"
        "border-left: 2px solid black;"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "height: 15px;"
        "border-bottom-right-radius: 8px;"
        "subcontrol-position: bottom;"
        "subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-line:vertical:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "QScrollBar::add-line:vertical:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar:horizontal {"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "border-top: 2px solid black;"
        "background: " + QString(COLOR_DEEP_GRAY) + ";"
        "height: 25px;"
        "margin: 0 15px 0 15px;"
        "border-radius: 0px;"
        "}";
        "QScrollBar::handle:horizontal {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "min-width: 30px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::handle:horizontal:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::sub-line:horizontal {"
        "border-top: 2px solid black;"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "width: 15px;"
        "border-bottom-left-radius: 8px;"
        "subcontrol-position: left;"
        "subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:horizontal:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::sub-line:horizontal:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}"
        "QScrollBar::add-line:horizontal {"
        "border-top: 2px solid black;"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "width: 15px;"
        "border-bottom-right-radius: 8px;"
        "subcontrol-position: right;"
        "subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-line:horizontal:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "QScrollBar::add-line:horizontal:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}";
}

MetTreeStyle::MetTreeStyle(QString bkg_color,
                           QString font_size,
                           QString font_color) :
    bkg_color(bkg_color),
    font_size(font_size),
    font_color(font_color)
{

}

MetTreeStyle::~MetTreeStyle()
{

}
