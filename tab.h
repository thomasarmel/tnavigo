#ifndef TAB_INCLUDED
#define TAB_INCLUDED

#include <wx/wx.h>
#include <wx/infobar.h>
#include <wx/webview.h>
#include <wx/aui/auibook.h>
#include <wx/url.h>
#include <wx/artprov.h>

class Tab : public wxWindow
{
public:
    Tab(wxWindow *parent, wxString URL=wxEmptyString);
    ~Tab();
    wxWebView *getWebView();
    void showConsoleJS();

private:
    void Go(wxCommandEvent &event);
    void GoBack(wxCommandEvent &event);
    void GoForward(wxCommandEvent &event);
    void reloadStop(wxCommandEvent &event);
    void fConsoleJSEnter(wxCommandEvent &event);
    void URLChangee(wxWebViewEvent &event);
    void navigating(wxWebViewEvent &event);
    void pageChargee(wxWebViewEvent &event);
    void fOuvrirNouvelOnglet(wxWebViewEvent &event);
    void titreChange(wxWebViewEvent &event);
    void fErreur(wxWebViewEvent &event);
    void Search(wxCommandEvent &event);
    void onContextMenu(wxContextMenuEvent &event);

    wxAuiNotebook *m_auiNotebookParent;

    wxBoxSizer *sizerVertical;
    wxBoxSizer *sizerHorizontalControles;
    wxInfoBar *infoBar;
    wxPanel *zoneControles;
    wxWebView *page1;
    wxTextCtrl *consoleJS;
    wxButton *goBack;
    wxButton *goForward;
    wxButton *btnReload;
    wxTextCtrl *champURL;
    wxButton *goURL;
    wxTextCtrl *champSearch;

    DECLARE_EVENT_TABLE()
    enum
    {
        ID_NOTEB1 = wxID_HIGHEST + 1,
        ID_ONGLET,
        ID_CONSOLEJS,
        ID_CHAMPURL,
        ID_GOURL,
        ID_INFOBAR,
        ID_WEBVIEW,
        ID_CHAMPSEARCH
    };
};

#endif // TAB_INCLUDED
