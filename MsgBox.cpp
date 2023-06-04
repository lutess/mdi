

#include "MsgBox.h"
#include <QPushButton>

MsgBox::MsgBox(QWidget* parent,	QString testo, QList<QString> buttons, QString information, QString details, QString winTitle,
				QMessageBox::Icon icon) : QMessageBox(parent)
{
	setText(testo);
	setInformativeText(information);
	setDetailedText(details);
	setWindowTitle(winTitle);
	setIcon(icon);
	setStyleSheet("background-color: #000000; color: #dddddd");
	setFont(QFont("Helvetica", 11));

	QList <QPushButton*> listaPushButton;
	QListIterator <QString> it(buttons);
	while (it.hasNext())
	{
		QString str= it.next();
		QPushButton* pb= addButton(str, QMessageBox::ActionRole);
		listaPushButton.append(pb);
	}
}

MsgBox::~MsgBox()
{}
