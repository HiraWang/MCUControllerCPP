#ifndef LOGIN_SUBWINDOW_H
#define LOGIN_SUBWINDOW_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>

#include "../widgets/line_edit.h"

class MetLoginSubwindow : public QDialog
{
	Q_OBJECT // enable meta object abilities

public:
	MetLoginSubwindow(QString account,
					  QString password,
					  QWidget* parent = nullptr);
	virtual ~MetLoginSubwindow();

private:
	void SetupUi();
	void LoadStyleSheet();
	QString account;
	QString password;
	QString style_sheet;
	MetLineEdit* account_edit;
	MetLineEdit* password_edit;
	QVBoxLayout* layout;
};

#endif