#include "FontDialog.h"


FontDialog::FontDialog(QFont fnt, QWidget* parent) : QFontDialog(parent)
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
	setCurrentFont(fnt);

	window()->setMinimumSize(300, 350);
	window()->resize(600, 400);
}

FontDialog::~FontDialog()
{}
