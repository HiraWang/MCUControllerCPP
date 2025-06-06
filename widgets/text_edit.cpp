#include "text_edit.h"

extern MetMenu* g_menu;
extern std::string IMAGE_MET_COPY;

MetTextEdit::MetTextEdit(MetTextEditStyle style, int w, int h, QWidget* parent)
    : style(style), w(w), h(h), menu(nullptr), QPlainTextEdit(parent) {
  setFixedWidth(w);
  setFixedHeight(h);
  setReadOnly(true);
  setContextMenuPolicy(Qt::CustomContextMenu);
  LoadStyleSheet();
  setStyleSheet(style_sheet);
}

MetTextEdit::~MetTextEdit() {}

void MetTextEdit::LoadStyleSheet() {
  style_sheet =
      "QPlainTextEdit {"
      "background: " +
      style.bkg_color +
      ";"
      "border: 2px solid black;"
      "border-radius: 5px;"
      "font: " +
      style.font_size +
      ";"
      "color: " +
      style.font_color +
      ";"
      "}"
      "QScrollBar:vertical {"
      "border-left: 2px solid black;"
      "border-top: 2px solid black;"
      "border-bottom: 2px solid black;"
      "background: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "width: 25px;"
      "margin: 15px 0 15px 0;"
      "border-radius: 0px;"
      "}"
      "QScrollBar::handle:vertical {"
      "background-color: " +
      QString(COLOR_GRAY) +
      ";"
      "min-height: 30px;"
      "}"
      "QScrollBar::handle:vertical:hover {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "}"
      "QScrollBar::handle:vertical:pressed {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "}"
      "QScrollBar::sub-line:vertical {"
      "border-left: 2px solid black;"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "height: 15px;"
      "border-top-right-radius: 3px;"
      "subcontrol-position: top;"
      "subcontrol-origin: margin;"
      "}"
      "QScrollBar::sub-line:vertical:hover {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "}"
      "QScrollBar::sub-line:vertical:pressed {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "}"
      "QScrollBar::add-line:vertical {"
      "border-left: 2px solid black;"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "height: 15px;"
      "border-bottom-right-radius: 3px;"
      "subcontrol-position: bottom;"
      "subcontrol-origin: margin;"
      "}"
      "QScrollBar::add-line:vertical:hover {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "QScrollBar::add-line:vertical:pressed {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "}";
}

void MetTextEdit::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::RightButton) {
    if (g_menu) g_menu->close();

    menu = new MetMenu();

    QIcon icon_copy = QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_COPY)));
    QAction* act_copy = menu->addAction(icon_copy, "Copy");
    connect(act_copy, &QAction::triggered, this, [=]() {
      copy();
      menu->close();
      menu = nullptr;
    });

    QAction* act_select_all = menu->addAction("Select all");
    connect(act_select_all, &QAction::triggered, this, [=]() {
      selectAll();
      menu->close();
      menu = nullptr;
    });

    menu->exec(QCursor::pos());
  } else if (event->button() == Qt::LeftButton) {
    if (menu) {
      QAction* action = menu->actionAt(event->pos());
      if (!action) {
        menu->close();
        menu = nullptr;
      }
    }
  }
}

MetTextEditStyle::MetTextEditStyle(QString bkg_color, QString font_size,
                                   QString font_color)
    : bkg_color(bkg_color), font_size(font_size), font_color(font_color) {}

MetTextEditStyle::~MetTextEditStyle() {}