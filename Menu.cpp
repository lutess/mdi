#include "Menu.h"
#include "MenuBar.h"

Menu::Menu(QWidget *parent, QString title, QMenuBar* ptr) : QMenu(parent)
{
	// "Qt Style Sheets Examples"
	setTitle(title);
	QString styleMenu = QString("QMenu { background-color: black; color: white; border: 1px solid black; } ") +
		QString("QMenu::item { background - color: transparent; } ") +
		QString("QMenu::item:selected { background - color: red; } ");
	setStyleSheet(styleMenu);
	setSeparatorsCollapsible(false);
	addSeparator();

	setFont(QFont("Helvetica", 12));
	ptr->addMenu(this);
}


Menu::Menu(QWidget* parent, QString title, QMenu* ptr) : QMenu(parent)
{
	// "Qt Style Sheets Examples"
	setTitle(title);
	QString styleMenu = QString(" background-color: black; color: white; border: 1px solid black; } ") +
		QString("QMenu::item { background - color: transparent; } ") +
		QString("QMenu::item:selected { background - color: red; } ");
	setStyleSheet(styleMenu);
	setSeparatorsCollapsible(false);
	addSeparator();

	setFont(QFont("Helvetica", 12));
	ptr->addMenu(this);
}


Menu::~Menu()
{}
