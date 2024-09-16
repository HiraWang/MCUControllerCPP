#ifndef COMBO_BOX_H
#define COMBO_BOX_H

#include <QComboBox>
#include <QString>

#include "color.h"
#include "font.h"

class METComboBoxStyle
{
public:
	METComboBoxStyle(QString bkg_color = COLOR_WHITE,
					 QString selection_bkg_color = COLOR_DEEP_GRAY,
					 QString editable_color = COLOR_WHITE,
					 QString disabled_color = COLOR_GRAY,
					 QString hover_color = COLOR_LIGHT_GRAY,
					 QString drop_down_color = COLOR_GRAY,
					 QString down_arrow_color = COLOR_BLACK,
					 QString down_arrow_on_color = COLOR_WHITE,
					 QString font_size = FONT_SIZE,
					 QString font_color = FONT_COLOR);
	~METComboBoxStyle();

	QString bkg_color;
	QString selection_bkg_color;
	QString editable_color;
	QString disabled_color;
	QString hover_color;
	QString drop_down_color;
	QString down_arrow_color;
	QString down_arrow_on_color;
	QString font_size;
	QString font_color;
};

class METComboBox : public QComboBox
{
	Q_OBJECT // enable meta object abilities

public:
	METComboBox(METComboBoxStyle style,
			    int w,
			    int h,
			    QWidget* parent = nullptr);
	~METComboBox();

private:
	QString style_sheet;
	METComboBoxStyle style;
	int w;
	int h;
	void load_style_sheet();
};

#endif