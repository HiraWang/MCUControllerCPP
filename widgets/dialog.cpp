#include "dialog.h"

#include "color.h"
#include "label.h"

MetDialog::MetDialog(MetParaList* para_list,
					 QWidget* parent) :
	para_list(para_list),
	QDialog(parent)
{
	layout_list = (QHBoxLayout**)calloc(para_list->size, sizeof(QHBoxLayout*));
	line_edit_list = (MetLineEdit**)calloc(para_list->size, sizeof(MetLineEdit*));
	SetupUi();
}

MetDialog::~MetDialog()
{
	free(layout_list);
	free(line_edit_list);
}

void MetDialog::SetupUi()
{
	setWindowTitle("Dialog");
	setFixedWidth(300);
	setFixedHeight(500);
	QString style_sheet = QString("QDialog { background-color: ") +
						  COLOR_GRAY +
						  QString("; }");
	setStyleSheet(style_sheet);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	
	layout = new QVBoxLayout(this);
	for (int id = 0; id < para_list->size; id++) {
		layout_list[id] = new QHBoxLayout();
		MetLineEditStyle line_edit_style;
		line_edit_list[id] = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);
		AddAttribute(para_list->list[id], layout_list[id],
			line_edit_list[id], para_list->list[id].is_editable);
		layout->addItem(layout_list[id]);
	}
	setLayout(layout);
}

void MetDialog::AddAttribute(MetPara para,
						     QHBoxLayout* layout,
					         MetLineEdit* line_edit,
						     bool is_editable)
{
	MetLabelStyle label_style(COLOR_NONE, FONT_SIZE, FONT_COLOR, "");
	MetLabel* label = new MetLabel(label_style, QString::fromStdString(para.name),
		200, WIDGET_H, this);
	if (para.str.empty()) {
		line_edit->setText(QString::fromStdString(std::to_string(para.num)));
	} else {
		line_edit->setText(QString::fromStdString(para.str));
	}
	line_edit->setEnabled(is_editable);

	layout->addWidget(label, 0, Qt::AlignLeft);
	layout->addWidget(line_edit, 0, Qt::AlignRight);
}

void MetDialog::UpdateAttributes()
{
	for (int id = 0; id < para_list->size; id++) {
		MetPara para = para_list->list[id];
		if (para.str.empty()) {
			line_edit_list[id]->setText(QString::fromStdString(std::to_string(para.num)));
		} else {
			line_edit_list[id]->setText(QString::fromStdString(para.str));
		}
	}
}

void MetDialog::Show()
{
	QDialog::show();
}

void MetDialog::Close()
{
	QDialog::close();
}