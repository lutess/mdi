#include "ColorDialog.h"

ColorDialog::ColorDialog(QColor clr, QWidget *parent) : QColorDialog(parent)
{
	QString style(
		"QDialog { background-color: darkblue}"
		"QLineEdit { font-size: 15px }"
		"QListView { font-size: 15px }"
		"QLabel { font-size: 17px; color: red }"
		"QGroupBox { font-size: 17px; color: red }"
		"QAbstractButton { font-size: 17px}"
		"QComboBox { font-size: 17px}"
	);
	setStyleSheet(style);
	setCurrentColor(clr);
}

ColorDialog::~ColorDialog()
{}
