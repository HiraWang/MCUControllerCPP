#ifndef MSG_SUBWINDOW_H
#define MSG_SUBWINDOW_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>

typedef enum { MSG_INFO = 0, MSG_WARNING = 1, MSG_ERROR = 2 } MsgType;

class MetMsgSubwindow : public QDialog {
  Q_OBJECT
  // enable meta object abilities

 public:
  MetMsgSubwindow(QString message, MsgType type = MSG_ERROR,
                  QWidget* parent = nullptr);
  virtual ~MetMsgSubwindow();

 private:
  void SetupUi();
  void LoadStyleSheet();
  QString message;
  QString style_sheet_dialog;
  QString style_sheet_label;
  MsgType type;
  QVBoxLayout* layout;
};

#endif