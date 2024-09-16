#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QString>

#include "color.h"
#include "font.h"

class Style
{
public:
	// METButton
	Style(QString met_button_color_1 = COLOR_WHITE,
		  QString met_button_color_2 = COLOR_WHITE,
		  QString met_button_hover_color_1 = COLOR_LIGHT_GRAY,
		  QString met_button_hover_color_2 = COLOR_LIGHT_GRAY,
		  QString met_button_pressed_color_1 = COLOR_GRAY,
		  QString met_button_pressed_color_2 = COLOR_GRAY,
		  QString font_size = FONT_SIZE,
		  QString font_color = FONT_COLOR);
	// METComboBox
	Style(QString met_combobox_selection_color = COLOR_WHITE,
		  QString met_combobox_selection_bkg_color = COLOR_WHITE,
		  QString met_combobox_editable_color = COLOR_WHITE,
		  QString met_combobox_disabled_color = COLOR_WHITE,
		  QString met_combobox_hover_color = COLOR_WHITE,
		  QString met_combobox_drop_down_color = COLOR_WHITE,
		  QString met_combobox_down_arrow_color = COLOR_WHITE,
		  QString met_combobox_down_arrow_on_color = COLOR_WHITE,
		  QString font_size = FONT_SIZE,
		  QString font_color = FONT_COLOR);
	~Style();

	// METButton
	QString met_button_color_1;
	QString met_button_color_2;
	QString met_button_hover_color_1;
	QString met_button_hover_color_2;
	QString met_button_pressed_color_1;
	QString met_button_pressed_color_2;

	// METComboBox
	QString met_combobox_selection_color;
	QString met_combobox_selection_bkg_color;
	QString met_combobox_editable_color;
	QString met_combobox_disabled_color;
	QString met_combobox_hover_color;
	QString met_combobox_drop_down_color;
	QString met_combobox_down_arrow_color;
	QString met_combobox_down_arrow_on_color;

	QString font_size;
	QString font_color;
};

#endif