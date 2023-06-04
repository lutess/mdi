#pragma once

#include <QFontDialog>

class FontDialog  : public QFontDialog
{
	Q_OBJECT

public:
	FontDialog(QFont fnt, QWidget* parent = 0);
	~FontDialog();
};
