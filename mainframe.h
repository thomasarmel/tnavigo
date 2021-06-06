#ifndef MAINFRAME_H_INCLUDED
#define MAINFRAME_H_INCLUDED

#include "myapp.h"
#include "tab.h"

class codeSource;
class parametres;
class authentification;

class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
        virtual ~MainFrame();
        void fNewTabSources(wxString url);
        void fConnectWithAuth(wxString url);

    private:
        void onClose(wxCloseEvent &event);
        void fNewTab(wxCommandEvent &event);
        void fCloseTab(wxCommandEvent &event);
        void onTabMouseClosed(wxAuiNotebookEvent& event);
        void fPrint(wxCommandEvent &event);
        void fSave(wxCommandEvent &event);
        void fQuit(wxCommandEvent &event);
        void fMAJ(wxCommandEvent &event);
        void onArgvArgc();
        void fSettings(wxCommandEvent &event);
        void fConsoleJS(wxCommandEvent &event);

        Tab *currentTab();

        void displaySources(wxCommandEvent &event);
        void onRightClick(wxContextMenuEvent &event);

        void initConf();

        wxAuiNotebook *tabManager;

        wxMenuBar *menuBar;
        wxMenu *menuFile;
        wxMenu *menuNav;
        wxMenu *menuOptions;

        wxFileConfig *fichierConf;
        wxString configDir, sysConfigDir, pageStart;
        wxFileDialog *dialogueEnregistrer;

        codeSource *pageSources;
        parametres *fenParametres;
        authentification *fenAuth;

        DECLARE_EVENT_TABLE()

        enum
        {
            ID_TABMANAGER = wxID_HIGHEST + 1,
            ID_SOURCES,
            ID_MENUMAJ,
            ID_MENUPARAM,
        };
};

#endif // MAINFRAME_H_INCLUDED
