#pragma once

#include <QMenu>

class Menu  : public QMenu
{
	Q_OBJECT

public:
	Menu(QWidget *parent, QString, QMenuBar*);
	Menu(QWidget* parent, QString, QMenu*);
	~Menu();
};
