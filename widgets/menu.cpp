#include "menu.h"
#include "color.h"
#include "label.h"

METMenu::METMenu(METParaList* para_list,
				 QWidget* parent) :
	para_list(para_list),
	QDialog(parent)
{
	layout_list = (QHBoxLayout**)calloc(para_list->size, sizeof(QHBoxLayout*));
	line_edit_list = (METLineEdit**)calloc(para_list->size, sizeof(METLineEdit*));
	setup_ui();
}

METMenu::~METMenu()
{
	for (int id = 0; id < para_list->size; id++) {
		delete layout_list[id];
	}
	free(layout_list);
	free(line_edit_list);
}

void METMenu::setup_ui()
{
	setWindowTitle("Menu");
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
		METLineEditStyle line_edit_style;
		line_edit_list[id] = new METLineEdit(line_edit_style, 100, 25, this);
		add_attribute(para_list->list[id], layout_list[id],
			line_edit_list[id], para_list->list[id].is_editable);
		layout->addItem(layout_list[id]);
	}
	setLayout(layout);
}

void METMenu::add_attribute(METPara para,
							QHBoxLayout* layout,
					        METLineEdit* line_edit,
							bool is_editable)
{
	METLabelStyle label_style(FONT_SIZE, FONT_COLOR);
	METLabel* label = new METLabel(label_style, QString::fromStdString(para.name),
		200, 25, this);
	if (para.str.empty()) {
		line_edit->setText(QString::fromStdString(std::to_string(para.num)));
	} else {
		line_edit->setText(QString::fromStdString(para.str));
	}
	line_edit->setEnabled(is_editable);

	layout->addWidget(label, 0, Qt::AlignLeft);
	layout->addWidget(line_edit, 0, Qt::AlignRight);
}

void METMenu::update_attributes()
{
	for (int id = 0; id < para_list->size; id++) {
		METPara para = para_list->list[id];
		if (para.str.empty()) {
			line_edit_list[id]->setText(QString::fromStdString(std::to_string(para.num)));
		}
		else {
			line_edit_list[id]->setText(QString::fromStdString(para.str));
		}
	}
}

void METMenu::show()
{
	QDialog::show();
}

void METMenu::close()
{
	QDialog::close();
}