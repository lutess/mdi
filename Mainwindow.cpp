
#include <QApplication>
#include "mainwindow.h"
#include "MdiClient.h"
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QListIterator>
#include <QList>
#include <QMessageBox>
#include "Utility.h"
#include "MsgBox.h"
#include "FontDialog.h"
#include "ColorDialog.h"
#include <QResizeEvent>


MainWindow::MainWindow(QWidget* parent) :	_vBoxLayout(new VBoxLayout(this)),
											_hBoxLayout(new HBoxLayout(this)),
											_menuBar(new MenuBar(this, _vBoxLayout)),
											_mdiArea(new MdiArea(this, _vBoxLayout, _hBoxLayout)),
											_statusBar(new StatusBar(this, _vBoxLayout)),
											orientamento(portrait)
{
	Utility::_pMainWnd = this;
	setStyleSheet("background-color: #000000; color: #dddddd");
	setLayout(_vBoxLayout);

	_menuFile =				new Menu	(this, "File", _menuBar);
	_newAction =			new Action	(this, "Nuovo", _menuFile);
	_apriAction =			new Action	(this, "Apri", _menuFile);				_menuFile->addSeparator();
	_salvaAction =			new Action	(this, "Salva", _menuFile);				/*_menuFile->addSeparator();*/
	_salvaComeAction =		new Action	(this, "Salva come...", _menuFile);		_menuFile->addSeparator();
	_chiudiAction =			new Action	(this, "Chiudi", _menuFile);
	_chiudiTuttiAction =	new Action	(this, "Chiudi Tutto", _menuFile);		_menuFile->addSeparator();
	_stampaAction =			new Action	(this, "Stampa", _menuFile);			_menuFile->addSeparator();
	_exitAction =			new Action	(this, "Esci", _menuFile);

	_modifica =				new Menu	(this, "Modifica", _menuBar);
	_fontAction=			new Action	(this, "Font", _modifica);
	_coloreAction =			new Action	(this, "Colore", _modifica);

	_menuVisualiz=			new Menu(this, "Visualizza", _menuBar);
	_frameless =			new Action(this, "Frameless", _menuVisualiz);		_menuVisualiz->addSeparator();
	_clientWndState =		new Action(this, "SubWndState", _menuVisualiz);		_menuVisualiz->addSeparator();

	_orientamento =			new Action(this, "Orientamento", _menuVisualiz);	_menuVisualiz->addSeparator();

	_menuMainWindow =		new Menu(this, "MainWindow", _menuVisualiz);
	_normalMainAction=		new Action(this, "Normale", _menuMainWindow);
	_maximizedMainAction=	new Action(this, "Maximized", _menuMainWindow);
	_fullScreenMainAction=	new Action(this, "FullScreen", _menuMainWindow);	_menuVisualiz->addSeparator();



	_menuFileAperti =		new Menu	(this, "Windows", _menuBar);

	connect(_newAction, &QAction::triggered, this, &MainWindow::nuovaFinestra);
	connect(_apriAction, &QAction::triggered, this, &MainWindow::apriDocumento);
	connect(_salvaAction, &QAction::triggered, this, &MainWindow::salva);
	connect(_salvaComeAction, &QAction::triggered, this, &MainWindow::salvaCome);
	connect(_chiudiAction, &QAction::triggered, this, &MainWindow::chiudi);
	connect(_chiudiTuttiAction, &QAction::triggered, this, &MainWindow::chiudiTutteFinestre);
	connect(_exitAction, &QAction::triggered, this, &MainWindow::chiudiTutteFinestre);

	connect(_normalMainAction, &QAction::triggered, this, &MainWindow::mainWindowNormal);
	connect(_maximizedMainAction, &QAction::triggered, this, &MainWindow::maximized);
	connect(_fullScreenMainAction, &QAction::triggered, this, &MainWindow::fullScreen);

	connect(_orientamento, &QAction::triggered, this, &MainWindow::cambiaOrientamento);

	aggiornaMenuMainWindow();
	aggiorna_orientamento_dimensioni();
	nuovaFinestra();

}

MainWindow::~MainWindow()
{
}

void MainWindow::nuovaFinestra()
{
	new MdiClient(_mdiArea, "", orientamento);
}


void MainWindow::apriDocumento()
{
	QString filter("TestoHtm (*.htm);;Testo (*.txt);;Any (*.*)");
	QString fileName = QFileDialog::getOpenFileName(this, "OpenFile", Utility::_dirPredef, filter);
	
	QList<QMdiSubWindow*> listaQMdiSubWindow = _mdiArea->subWindowList();		// Controllo che il documento non sia gia' aperto
	QList<QMdiSubWindow*>::iterator it = listaQMdiSubWindow.begin();
	while (it != listaQMdiSubWindow.end() && (*it)->windowTitle() != fileName) it++;
	if (it != listaQMdiSubWindow.end())
		(*it)->setFocus();
	else
	{
		QGuiApplication::setOverrideCursor(Qt::WaitCursor);
		if (!fileName.isNull() && !fileName.isEmpty())
			MdiClient* client = new MdiClient(_mdiArea, fileName, orientamento);
		QGuiApplication::restoreOverrideCursor();
	}
	setWindowTitle(qApp->applicationName() + " - " + QFileInfo(fileName).baseName());
}


void MainWindow::windowActivateSignalReceived(QMdiSubWindow* window)
{
	_menuFileAperti->clear();
	_menuFileAperti->addSeparator();
	QList<QMdiSubWindow*> listaQMdiSubWindow = _mdiArea->subWindowList();
	for (QMdiSubWindow* vnd : listaQMdiSubWindow)
	{
		Action *act= new Action(this, vnd->windowTitle(), _menuFileAperti, true);
		if (vnd->windowTitle() == window->windowTitle())
		{
			act->setChecked(true);
			setWindowTitle(qApp->applicationName() + " - " + QFileInfo(vnd->windowTitle()).baseName());

		}
		else act->setChecked(false);
		connect(act, &QAction::triggered, this, &MainWindow::selezionaDocumento);
	}
}


void MainWindow::selezionaDocumento()
{
	QString str = ((Action*)QObject::sender())->text();;
	QList<QMdiSubWindow*> listaQMdiSubWindow = Utility::_pMdiArea->subWindowList();
	QList<QMdiSubWindow*>::iterator it = listaQMdiSubWindow.begin();
	while (QString((*it)->windowTitle()) != str) it++;
	(*it)->setFocus();
}


void MainWindow::salva()
{
	MdiClient* ptrMdiClient= (MdiClient*)_mdiArea->currentSubWindow()->widget();
	QString str(ptrMdiClient->windowTitle());
	if (ptrMdiClient->isDefaultNome() && !str.compare("untitled0 "))
	{
		QString testo("Untitled0 non puo' essere salvato.");
		QList <QString> buttons = { "Ok" };
		QString information("E' stata annullata l'operazione.");
		QString details("In void MainWindow::salva()\n\n"
						"Il nome de mdiClient in oggetto era: " + str);
		MsgBox msg(this, testo, buttons, information, details); msg.exec();
		return;
	}
	if (ptrMdiClient->isDefaultNome())
	{
		QString filter("TestoHtm (*.htm);;Testo (*.txt);;Any (*.*)");
		str = QFileDialog::getSaveFileName(this, "Salva File", Utility::_dirPredef, filter, 0);
	}
	if(	Utility::scriviFile(ptrMdiClient, str))
	{
		ptrMdiClient->setWindowTitle(str);
		ptrMdiClient->setDefaultNome(false);
		ptrMdiClient->document()->setModified(false);
	}
	else
	{
		QString testo("Impossibile aprire il file in scrittura.\nDisco pieno?");
		QList <QString> buttons = { "Ok" };
		QString information("E' stata annullata l'operazione.");
		QString details("In void MainWindow::salva()\n\n"
						"Il nome de mdiClient in oggetto era: " + ptrMdiClient->nome());
		MsgBox msg(this, testo, buttons, information, details); msg.exec();
	}
}


void MainWindow::salvaCome()
{
	MdiClient* ptrMdiClient = (MdiClient*)_mdiArea->currentSubWindow()->widget();
	if (ptrMdiClient->isDefaultNome() && !ptrMdiClient->nome().compare("untitled0 "))
	{
		QString testo("Untitled0 non puo' essere salvato.");
		QList <QString> buttons = { "Ok" };
		QString information("E' stata annullata l'operazione.");
		QString details("In void MainWindow::salvaCome()\n\n"
						"Il nome de mdiClient in oggetto era: " + ptrMdiClient->nome());
		MsgBox msg(this, testo, buttons, information, details); msg.exec();
		return;
	}
	QString predef = Utility::_dirPredef + ptrMdiClient->windowTitle();
	QFileInfo fi(predef);
	QString filter("TestoHtm (*.htm);;Testo (*.txt);;Any (*.*)");
	QString str = QFileDialog::getSaveFileName(this, "Salva File", predef, filter, 0);
	if (str.isNull()) return;
	if (Utility::scriviFile(ptrMdiClient, str))
	{
		ptrMdiClient->setWindowTitle(str);
		ptrMdiClient->setDefaultNome(false);
		ptrMdiClient->document()->setModified(false);
	}
	else
	{
		QString testo("Impossibile aprire il file in scrittura.\nDisco pieno?");
		QList <QString> buttons = { "Ok" };
		QString information("E' stata annullata l'operazione.");
		QString details("In void MainWindow::salva()\n\n"
			"Il nome de mdiClient in oggetto era: " + ptrMdiClient->nome());
		MsgBox msg(this, testo, buttons, information, details); msg.exec();
	}
}


void MainWindow::chiudiTutteFinestre()
{
	bool esci = false; if (((Action*)QObject::sender())->nome() == "Esci") esci = true;
	if (esci)
	{
		QList <QMdiSubWindow*> listaQMdiSubWindow = _mdiArea->subWindowList();
		QList <QMdiSubWindow*>::iterator it = listaQMdiSubWindow.begin();
		delete *it;
	}
	_mdiArea->closeAllSubWindows();
	if (esci) qApp->exit();
}


void MainWindow::mainWindowNormal()
{
	setWindowState(Qt::WindowNoState);
	aggiornaMenuMainWindow();
}

void MainWindow::maximized()
{
	setWindowState(Qt::WindowMaximized);
	aggiornaMenuMainWindow();
}

void MainWindow::fullScreen()
{
	setWindowState(Qt::WindowFullScreen);
	aggiornaMenuMainWindow();
}


void MainWindow::aggiornaMenuMainWindow()
{
	_menuMainWindow->clear();
	switch (windowState())
	{
	case Qt::WindowNoState:
		_menuMainWindow->addAction(_maximizedMainAction);
		_menuMainWindow->addAction(_fullScreenMainAction); break;
	case Qt::WindowMaximized:
		_menuMainWindow->addAction(_normalMainAction);
		_menuMainWindow->addAction(_fullScreenMainAction); break;
	case Qt::WindowFullScreen:
		_menuMainWindow->addAction(_normalMainAction);
		_menuMainWindow->addAction(_maximizedMainAction); break;
	}
}


void MainWindow::aggiorna_orientamento_dimensioni()
{
	QList<QAction*> listaAction = _menuVisualiz->actions();
	QAction* action = listaAction.at(listaAction.indexOf(_orientamento));

	QScreen* screen = QGuiApplication::primaryScreen();
	qreal screenDpi = screen->physicalDotsPerInch();		// 102.4747...
	int width, heigth;
	switch (orientamento)
	{
	case portrait:
		width = screenDpi * 21 / 2.54; heigth = /*screenDpi * 29.7 / 2.54*/650;
		action->setText("Landscape");
		break;
	case landscape:
		width = screenDpi * 29.7 / 2.54; heigth = /*screenDpi * 21 / 2.54*/650;
		action->setText("Portrait");
		break;
	default: width = 0; heigth = 0;
	}
	_mdiArea->setMinimumWidth(width+ 1); _mdiArea->setMaximumWidth(width);
	_mdiArea->setMinimumHeight(heigth); _mdiArea->setMaximumHeight(heigth);
	QList<QMdiSubWindow*> listaQMdiSubWindow = _mdiArea->subWindowList();
	for (QMdiSubWindow* wdgt : listaQMdiSubWindow)
	{
		MdiClient* mdiClient = (MdiClient*)wdgt->widget();
		mdiClient->setLineWrapColumnOrWidth(width - 32);		/*margine di 0.4 cm*/
		mdiClient->setMinimumWidth(width); mdiClient->setMaximumWidth(width);
		mdiClient->setMinimumHeight(heigth); mdiClient->setMaximumHeight(heigth);
	}
	//_vBoxLayout->invalidate();
	//_hBoxLayout->invalidate();
}


void MainWindow::cambiaOrientamento()
{
	if (QString(QObject::sender()->metaObject()->className()) != "Action")
		return;

	switch (orientamento)
	{
	case portrait:
		orientamento = landscape; break;
	case landscape:
		orientamento = portrait; break;
	}
	aggiorna_orientamento_dimensioni();
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
	QSize oldSize = event->oldSize();
	QSize size = event->size();
	int orient = orientamento;
	int wndState = windowState();
}


bool MainWindow::event(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange)
		aggiornaMenuMainWindow();
	return QWidget::event(event);
}



