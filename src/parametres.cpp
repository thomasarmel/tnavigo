#include "parametres.h"

BEGIN_EVENT_TABLE(parametres, wxFrame)
    EVT_BUTTON(wxID_OK, parametres::fOK)
    EVT_BUTTON(wxID_CANCEL, parametres::fCancel)
END_EVENT_TABLE()

parametres::parametres(wxFileConfig *fichierConf, wxWindow *fenetreMere) : wxFrame(fenetreMere, wxID_ANY, wxT("Modifier les paramètres"), wxDefaultPosition, wxSize(500, 500)),
    m_fichierConf(fichierConf)
{
    zonePrincipale=new wxPanel(this);
    textNom=new wxStaticText(zonePrincipale, wxID_ANY, wxT("Votre nom:"), wxPoint(5, 5));
    champNom=new wxTextCtrl(zonePrincipale, wxID_ANY, wxEmptyString, wxPoint(110, 5), wxSize(150, -1));
    textPageStart=new wxStaticText(zonePrincipale, wxID_ANY, wxT("Page au démarrage:"), wxPoint(5, 50));
    champPageStart=new wxTextCtrl(zonePrincipale, wxID_ANY, wxT("about:blank"), wxPoint(130, 50), wxSize(200, -1));
    btnOk=new wxButton(zonePrincipale, wxID_OK, wxT("OK"), wxPoint(250, 400));
    btnOk=new wxButton(zonePrincipale, wxID_CANCEL, wxT("Annuler"), wxPoint(350, 400));

    fInitConfig();
}

parametres::~parametres()
{
}

void parametres::fInitConfig()
{
    if(m_fichierConf->Read(wxT("startupPage"), &pageStart))
        champPageStart->SetValue(pageStart);

    if(m_fichierConf->Read(wxT("nom"), &pageStart))
        champNom->SetValue(pageStart);
}

void parametres::fOK(wxCommandEvent &event)
{
    m_fichierConf->Write(wxT("startupPage"), champPageStart->GetValue());
    m_fichierConf->Write(wxT("nom"), champNom->GetValue());
    if(!(m_fichierConf->Flush()))
    {
        wxMessageBox(wxT("Impossible de sauvegarder les paramètres.\nPeut-être l'opération nécessite-t'elle une élévation."), wxT("Erreur"), wxICON_ERROR);
        return;
    }
    else
    {
        Close();
    }
}
void parametres::fCancel(wxCommandEvent &event)
{
    Close();
}
