#ifndef TREE_H
#define TREE_H

#include <QString>
#include <QTreeWidget>

#include "color.h"
#include "font.h"
#include "menu.h"

class MetTreeStyle {
 public:
  MetTreeStyle(QString bkg_color = COLOR_LIGHT_GRAY,
               QString font_size = FONT_SIZE, QString font_color = FONT_COLOR);
  virtual ~MetTreeStyle();

  QString bkg_color;
  QString font_size;
  QString font_color;
};

class MetTree : public QTreeWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  MetTree(MetTreeStyle style, int w, int h, QWidget* parent = nullptr);
  virtual ~MetTree();

 protected:
  void mousePressEvent(QMouseEvent* event);

 private:
  void LoadStyleSheet();
  MetTreeStyle style;
  QString style_sheet;
  MetMenu* menu;
};

#endif