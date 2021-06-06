#ifndef AUTH_H_INCLUDED
#define AUTH_H_INCLUDED

#include "mainframe.h"

class MainFrame;

class authentification : public wxFrame
{
public:
    authentification(MainFrame *parent, wxWindow *fenetreMere, wxString URL);
    ~authentification();

private:
    void fOK(wxCommandEvent &event);
    void fCancel(wxCommandEvent &event);

    wxBoxSizer *sizerVertical;
    wxPanel *zone1;
    wxStaticText *textExplication, *textLogin, *textPassword;
    wxTextCtrl *champLogin, *champPassword;
    wxButton *btnOk, *btnAnnuler;
    MainFrame *m_parent;
    wxString m_URL, m_URLWithAuth, m_URLLeft, m_URLRight;
    short sizeURL, startDNS;

    enum
    {
        ID_BTNOK = wxID_HIGHEST + 1,
        ID_BTNANNULER,
    };

    DECLARE_EVENT_TABLE()
};

#endif // AUTH_H_INCLUDED
