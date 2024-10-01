#ifndef LOGIN_SUBWINDOW_H
#define LOGIN_SUBWINDOW_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>

#include "../devices/device.h"

class MetLoginSubwindow : public QDialog
{
	Q_OBJECT // enable meta object abilities

public:
	MetLoginSubwindow(SerialPort* device,
					  QString account,
					  QString password,
					  QWidget* parent = nullptr);
	virtual ~MetLoginSubwindow();

private:
	void SetupUi();
	void LoadStyleSheet();
	void Login();
	QString account;
	QString password;
	QString style_sheet;
	SerialPort* device;
	QVBoxLayout* layout;
};

#endif