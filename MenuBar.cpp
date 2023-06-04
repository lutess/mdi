#include "MenuBar.h"
#include "mainwindow.h"

MenuBar::MenuBar(QWidget*parent, VBoxLayout* ptr) : QMenuBar(parent)
{
	ptr->addWidget(this);

	// "Qt Style Sheets Examples"
	QString styleMenubar = QString("QMenuBar { background-color: black; color: white; spacing: 10px;} ") +
		QString("QMenuBar::item:selected{background - color: darkgray; color: black}") +
		QString("QMenuBar::item:pressed { background: red }") +
		QString("QMenuBar::item{padding: 1px 4px; background: transparent; border - radius: 4px;}");
	setStyleSheet(styleMenubar);
	setFont(QFont("Helvetica", 12));
}

MenuBar::~MenuBar()
{}
