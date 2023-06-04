#pragma once

#include <QObject>
#include "MainWindow.h"


class Utility  : public QObject
{
	Q_OBJECT

public:
	static bool scriviFile(class MdiClient* mdiClient, QString str);
	static QString _dirPredef;
	static MainWindow* _pMainWnd;
	static MdiArea* _pMdiArea;
	static double _MonitorDpi;
};
