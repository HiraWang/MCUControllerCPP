#include "text_edit.h"

MetTextEdit::MetTextEdit(MetTextEditStyle style,
						 int w,
						 int h,
						 QWidget* parent) :
	style(style),
	w(w),
	h(h),
	QPlainTextEdit(parent)
{
	setFixedWidth(w);
	setFixedHeight(h);
	setReadOnly(true);
	LoadStyleSheet();
	setStyleSheet(style_sheet);
}

MetTextEdit::~MetTextEdit()
{

}

void MetTextEdit::LoadStyleSheet()
{
	style_sheet =
		"QPlainTextEdit {"
		"background: " + style.bkg_color + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}""QScrollBar:vertical {"
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
        "border-top-right-radius: 3px;"
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
        "border-bottom-right-radius: 3px;"
        "subcontrol-position: bottom;"
        "subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-line:vertical:hover {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "QScrollBar::add-line:vertical:pressed {"
        "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
        "}";
}

MetTextEditStyle::MetTextEditStyle(QString bkg_color,
								   QString font_size,
								   QString font_color) :
	bkg_color(bkg_color),
	font_size(font_size),
	font_color(font_color)
{

}

MetTextEditStyle::~MetTextEditStyle()
{

}