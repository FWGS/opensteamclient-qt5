#include <QObject>
#include <QCoreApplication>
#include <QThread>
#include <QSettings>
#include <string>
#include "windows/mainwindow.h"
#include "dialogs/startupprogressdialog.h"
#include "../../common/commandline.h"
#include "../threading/threadcontroller.h"
#include "windows/loginwindow.h"
#include "../login/loginthread.h"
#include "dynamicwebviewlibrarymanager.h"

#pragma once

// Our "main" gui class
class Application : public QObject
{
    Q_OBJECT
private:
    static Application *instance;
    Application();
    // Called from quitApp
    void Shutdown(bool bRestoreValveSteam = false);
    void loginFailed(SteamServerConnectFailure_t);
    void loginSucceeded(SteamServersConnected_t);

public:
    QCoreApplication *QApp;
    MainWindow *mainWindow;
    CommandLine *commandLine;
    QSettings *settings;
    LoginWindow *loginWindow;
    StartupProgressDialog *progDialog;
    AppManager *appManager;
    DynamicWebViewLibraryMgr *dynamicWebViewLibraryMgr;

    bool hasLogonCompleted = false;

    // Misc variables not related to UI directly
    uint64_t currentUserSteamID = 0;

    static Application *GetApplication();
    int StartApplication();
    bool IsGUIBoot();
    void InitApplication();
    ~Application();
private slots:
    void postLogonState(PostLogonState_t state);
public slots:
    void quitApp();
    void quitAppAndRestoreValveSteam();
signals:
    void quitRequested();
};

Q_DECLARE_METATYPE(App*);
Q_DECLARE_METATYPE(PostLogonState_t);
Q_DECLARE_METATYPE(SteamServersConnected_t);
Q_DECLARE_METATYPE(SteamServerConnectFailure_t);
Q_DECLARE_METATYPE(AppLicensesChanged_t);
Q_DECLARE_METATYPE(DownloadScheduleChanged_t);
Q_DECLARE_METATYPE(DownloadSpeedInfo);
Q_DECLARE_METATYPE(AppId_t);
                  

//Q_DECLARE_METATYPE(App)
