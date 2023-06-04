
#pragma once

#include <QObject>
#include "VBoxLayout.h"
#include "MenuBar.h"
#include "MdiArea.h"
#include "StatusBar.h"
#include "Menu.h"
#include "Action.h"
#include <QApplication>
#include <QWidget>
#include "HBoxLayout.h"


class MainWindow : public QWidget

{
    Q_OBJECT

private:
    VBoxLayout* _vBoxLayout;
    HBoxLayout* _hBoxLayout;
    MenuBar* _menuBar;
    MdiArea* _mdiArea;
    StatusBar* _statusBar;

    Menu* _menuFile;
    Action* _newAction;
    Action* _apriAction;
    Action* _salvaAction;
    Action* _salvaComeAction;
    Action* _chiudiAction;
    Action* _chiudiTuttiAction;
    Action* _stampaAction;
    Action* _exitAction;


    Menu* _modifica;
    Action* _fontAction;
    Action* _coloreAction;

    Menu* _menuVisualiz;
    Action* _frameless;
    Action* _clientWndState;

    Action* _orientamento;

    Menu* _menuMainWindow;
    Action* _normalMainAction;
    Action* _maximizedMainAction;
    Action* _fullScreenMainAction;


    Menu* _menuFileAperti;

    enum { portrait, landscape } orientamento;

private slots:
    void nuovaFinestra();
    void apriDocumento();
    void windowActivateSignalReceived(QMdiSubWindow*);
    void selezionaDocumento();
    void chiudi() { _mdiArea->closeActiveSubWindow(); }
    void salva();
    void chiudiTutteFinestre();
    void mainWindowNormal();
    void maximized();
    void fullScreen();
    void cambiaOrientamento();
    void salvaCome();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Action* apriAction() { return _apriAction; }
    Action* coloreAction() { return _coloreAction; }
    Action* fontAction() { return _fontAction; }
    Action* framelessAction() { return _frameless; }
    Action* clientWndState() { return _clientWndState; }

private:
    void aggiornaMenuMainWindow();
    void aggiorna_orientamento_dimensioni();


    //overridden
    void resizeEvent(QResizeEvent* event);
    bool event(QEvent* event);
};

