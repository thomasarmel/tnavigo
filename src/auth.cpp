#include "auth.h"

BEGIN_EVENT_TABLE(authentification, wxFrame)
    EVT_BUTTON(ID_BTNOK, authentification::fOK)
    EVT_BUTTON(ID_BTNANNULER, authentification::fCancel)
END_EVENT_TABLE()

authentification::authentification(MainFrame *parent, wxWindow *fenetreMere, wxString URL) : wxFrame(fenetreMere, wxID_ANY, wxT("Authentification requise"), wxDefaultPosition, wxSize(400, 250)), m_parent(parent), m_URL(URL)
{
    sizerVertical=new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerVertical);
    zone1=new wxPanel(this);
    sizerVertical->Add(zone1, 1, wxALL | wxEXPAND, 0);
    textExplication=new wxStaticText(zone1, wxID_ANY, wxT("L'accès à ce site requiert un nom d'utilisateur et un mot de passe."), wxPoint(5, 5));
    textLogin=new wxStaticText(zone1, wxID_ANY, wxT("Login"), wxPoint(5, 50));
    champLogin=new wxTextCtrl(zone1, wxID_ANY, wxEmptyString, wxPoint(105, 50), wxSize(150, -1));
    textPassword=new wxStaticText(zone1, wxID_ANY, wxT("Password"), wxPoint(5, 100));
    champPassword=new wxTextCtrl(zone1, wxID_ANY, wxEmptyString, wxPoint(105, 100), wxSize(150, -1), wxTE_PASSWORD);
    btnOk=new wxButton(zone1, ID_BTNOK, wxT("OK"), wxPoint(30, 150));
    btnAnnuler=new wxButton(zone1, ID_BTNANNULER, wxT("Annuler"), wxPoint(130, 150));
}

authentification::~authentification()
{
}

void authentification::fOK(wxCommandEvent &event)
{
    sizeURL=m_URL.Length();
    startDNS=m_URL.Find("://");
    if(m_URL.Find("@")==wxNOT_FOUND)
    {
        m_URLLeft=m_URL.Left(startDNS+3);
        m_URLRight=m_URL.Right(sizeURL-(startDNS+3));
    }
    else
    {
        m_URLLeft=m_URL.Left(startDNS+3);
        m_URLRight=m_URL.Right(sizeURL-(m_URL.Find("@")+1));
    }
    if(startDNS==wxNOT_FOUND)
    {
        m_URLWithAuth=champLogin->GetValue() + ":" + champPassword->GetValue() + "@" + m_URLRight;
    }
    else
    {
        m_URLWithAuth=m_URLLeft + champLogin->GetValue() + ":" + champPassword->GetValue() + "@" + m_URLRight;
    }

    m_parent->fConnectWithAuth(m_URLWithAuth);
    Close();
}

void authentification::fCancel(wxCommandEvent &event)
{
    Close();
}
