#include "dialog.h"

#include "color.h"
#include "label.h"

extern std::string IMAGE_MET_RESET;

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
	QString style_sheet = QString("QDialog { background-color: ") +
						  COLOR_GRAY +
						  QString("; }");
	setStyleSheet(style_sheet);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	
	unsigned char para_count = 0;
	layout = new QVBoxLayout(this);
	QHBoxLayout* layout_top = new QHBoxLayout();

	MetTextEditStyle text_style;
	text = new MetTextEdit(text_style, 265 - BUTTON_W, BUTTON_W, this);
	layout_top->addWidget(text, 0, Qt::AlignLeft);

	MetButtonStyle button_style;
	refresh_button = new MetButton(button_style, "EXIT", "", BUTTON_W, BUTTON_W,
		QString::fromStdString(GetAbsPath(IMAGE_MET_RESET)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_RESET)), this);
	connect(refresh_button, &QPushButton::released, this,
		&MetDialog::ToggleRefreshButton);
	layout_top->addWidget(refresh_button, 0, Qt::AlignRight);

	layout->addItem(layout_top);

	// add widgets for attributes
	for (int id = 0; id < para_list->size; id++) {
		layout_list[id] = new QHBoxLayout();
		MetLineEditStyle line_edit_style;
		line_edit_list[id] = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);
		AddAttribute(para_list->list[id], layout_list[id],
			line_edit_list[id], para_list->list[id].is_editable, &para_count);
		layout->addItem(layout_list[id]);
	}

	setFixedHeight(BUTTON_W + para_count * 50);
	setLayout(layout);
}

void MetDialog::AddAttribute(MetPara para,
						     QHBoxLayout* layout,
					         MetLineEdit* line_edit,
						     bool is_editable,
						     unsigned char* para_count)
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

	if (para.name.find("keyword") != std::string::npos) {
		(*para_count)++;
		layout->addWidget(label, 0, Qt::AlignLeft);
		layout->addWidget(line_edit, 0, Qt::AlignRight);
	} else {
		label->setVisible(false);
		line_edit->setVisible(false);
	}
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

void MetDialog::ToggleRefreshButton()
{
	text->clear();
	std::vector<std::string> ports = ListComPorts();
	for (std::vector<std::string>::iterator i = ports.begin(); i != ports.end(); ++i) {
		text->appendPlainText(QString::fromStdString(*i));
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