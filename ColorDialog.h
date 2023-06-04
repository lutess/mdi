#pragma once

#include <QColorDialog>

class ColorDialog  : public QColorDialog
{
	Q_OBJECT

public:
	ColorDialog(QColor clr, QWidget *parent);
	~ColorDialog();
};
