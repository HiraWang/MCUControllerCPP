#ifndef MSG_SUBWINDOW_H
#define MSG_SUBWINDOW_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>

class METMsgSubwindow : public QDialog
{
	Q_OBJECT // enable meta object abilities

public:
	METMsgSubwindow(QString message,
					QWidget* parent = nullptr);
	virtual ~METMsgSubwindow();

private:
	void SetupUi();
	void LoadStyleSheet();
	QString message;
	QString style_sheet_dialog;
	QString style_sheet_label;
	QVBoxLayout* layout;
};

#endif