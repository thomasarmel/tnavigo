#ifndef PARAMETRES_H_INCLUDED
#define PARAMETRES_H_INCLUDED

#include "mainframe.h"

class parametres : public wxFrame
{
public:
    parametres(wxFileConfig *fichierConf, wxWindow *fenetreMere);
    ~parametres();

private:
    void fInitConfig();
    void fOK(wxCommandEvent &event);
    void fCancel(wxCommandEvent &event);

    wxFileConfig *m_fichierConf;
    wxPanel *zonePrincipale;
    wxStaticText *textNom;
    wxTextCtrl *champNom;
    wxStaticText *textPageStart;
    wxTextCtrl *champPageStart;
    wxString pageStart;
    wxButton *btnOk;
    wxButton *btnCancel;
    DECLARE_EVENT_TABLE()
};

#endif // PARAMETRES_H_INCLUDED
