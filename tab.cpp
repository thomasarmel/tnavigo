#include "tab.h"

BEGIN_EVENT_TABLE(Tab, wxWindow)
    EVT_CONTEXT_MENU(Tab::onContextMenu)

    EVT_TEXT_ENTER(ID_CHAMPURL, Tab::Go)
    EVT_TEXT_ENTER(ID_CONSOLEJS, Tab::fConsoleJSEnter)
    EVT_TEXT_ENTER(ID_CHAMPSEARCH, Tab::Search)

    EVT_BUTTON(wxID_BACKWARD, Tab::GoBack)
    EVT_BUTTON(wxID_FORWARD, Tab::GoForward)
    EVT_BUTTON(wxID_REFRESH, Tab::reloadStop)
    EVT_BUTTON(ID_GOURL, Tab::Go)

    EVT_WEBVIEW_NAVIGATED(ID_ONGLET, Tab::URLChangee)
    EVT_WEBVIEW_NAVIGATING(ID_ONGLET, Tab::navigating)
    EVT_WEBVIEW_LOADED(ID_ONGLET, Tab::pageChargee)
    EVT_WEBVIEW_TITLE_CHANGED(ID_ONGLET, Tab::titreChange)
    EVT_WEBVIEW_NEWWINDOW(ID_ONGLET, Tab::fOuvrirNouvelOnglet)
    EVT_WEBVIEW_ERROR(ID_ONGLET, Tab::fErreur)
END_EVENT_TABLE()

Tab::Tab(wxWindow *parent, wxString URL) : wxWindow(parent, wxID_ANY)
{
    m_auiNotebookParent=(wxAuiNotebook*)parent;
    sizerVertical=new wxBoxSizer(wxVERTICAL);
    infoBar = new wxInfoBar(this, ID_INFOBAR);
    SetSizer(sizerVertical);

    zoneControles=new wxPanel(this);
    page1=wxWebView::New(this, ID_ONGLET, URL);

    //page1->EnableContextMenu(false);


    consoleJS=new wxTextCtrl(this, ID_CONSOLEJS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);
    sizerVertical->Add(zoneControles, 1, wxALL | wxEXPAND, 0);
    sizerVertical->Add(infoBar, 2, wxEXPAND, 0);
    sizerVertical->Add(page1, 36, wxALL | wxEXPAND, 0);
    sizerVertical->Add(consoleJS, 2, wxALL | wxEXPAND, 0);
    sizerVertical->Hide(consoleJS);

    sizerHorizontalControles=new wxBoxSizer(wxHORIZONTAL);
    zoneControles->SetSizer(sizerHorizontalControles);

    goBack=new wxButton(zoneControles, wxID_BACKWARD, _T("Prec."), wxDefaultPosition, wxDefaultSize, wxBU_NOTEXT | wxBORDER_NONE);
    goBack->SetBitmap(wxArtProvider::GetBitmap(wxART_GO_BACK));
    goForward=new wxButton(zoneControles, wxID_FORWARD, _T("Suiv."), wxDefaultPosition, wxDefaultSize, wxBU_NOTEXT | wxBORDER_NONE);
    goForward->SetBitmap(wxArtProvider::GetBitmap(wxART_GO_FORWARD));
    btnReload=new wxButton(zoneControles, wxID_REFRESH, _T("Act."), wxDefaultPosition, wxDefaultSize, /*wxBU_NOTEXT*/wxBORDER_NONE);
    btnReload->SetBitmap(wxArtProvider::GetBitmap(wxART_GOTO_FIRST));
    champURL=new wxTextCtrl(zoneControles, ID_CHAMPURL, URL, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    champURL->SetHint(wxT("http://url.ext"));
    goURL=new wxButton(zoneControles, ID_GOURL, _T("GO"), wxDefaultPosition, wxDefaultSize, wxBU_NOTEXT | wxBORDER_NONE);
    goURL->SetBitmap(wxArtProvider::GetBitmap(wxART_TICK_MARK));
    champSearch=new wxTextCtrl(zoneControles, ID_CHAMPSEARCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    champSearch->SetHint(wxT("Type search and press Enter"));

    sizerHorizontalControles->Add(goBack, 1, wxALL | wxEXPAND, 2);
    sizerHorizontalControles->Add(goForward, 1, wxALL | wxEXPAND, 2);
    sizerHorizontalControles->Add(btnReload, 1, wxALL | wxEXPAND, 2);
    sizerHorizontalControles->Add(champURL, 10, wxALL | wxEXPAND, 2);
    sizerHorizontalControles->Add(goURL, 1, wxALL | wxEXPAND, 2);
    sizerHorizontalControles->AddSpacer(100);
    sizerHorizontalControles->Add(champSearch, 10, wxALL | wxEXPAND, 2);

    champURL->SetFocus();
}

Tab::~Tab()
{}

void Tab::Go(wxCommandEvent &event)
{
    wxString URL=champURL->GetValue();
    if ((URL.Left(7) != "http://") && (URL.Left(8) != "https://") && (URL.Left(7) != "file://"))
    {
        if (wxFileExists(URL))
        {
            if (URL.Left(1) == "/")
            {
                URL = "file://" + URL;
            }
            else
            {
                URL = "file:///" + URL;
            }
        }
        else
        {
            URL = "http://" + URL;
        }
    }
    champURL->Clear();
    champURL->AppendText(URL);
    page1->LoadURL(URL);
}

void Tab::GoBack(wxCommandEvent &event)
{
    if(page1->CanGoBack())
    {
        page1->GoBack();
    }
}

void Tab::GoForward(wxCommandEvent &event)
{
    if(page1->CanGoForward())
    {
        page1->GoForward();
    }
}

void Tab::reloadStop(wxCommandEvent &event)
{
    if(page1->IsBusy())
    {
        page1->Stop();
    }
    else
    {
        page1->Reload();
    }
}

void Tab::fConsoleJSEnter(wxCommandEvent &event)
{
    int nbLines=consoleJS->GetNumberOfLines();
    page1->RunScript(consoleJS->GetLineText(nbLines-1));
    consoleJS->AppendText(wxT("\n"));
}

void Tab::URLChangee(wxWebViewEvent &event)
{
    int indexTab=m_auiNotebookParent->GetPageIndex(this);
    if(event.GetURL().Left(8) == "https://")
    {
        m_auiNotebookParent->SetPageBitmap(indexTab, wxBitmap("icon-https.png", wxBITMAP_TYPE_PNG));
    }
    else if(event.GetURL().Left(7) == "http://")
    {
        m_auiNotebookParent->SetPageBitmap(indexTab, wxBitmap("icon-http.png", wxBITMAP_TYPE_PNG));
    }
    else
    {
        m_auiNotebookParent->SetPageBitmap(indexTab, wxNullBitmap);
    }
    btnReload->SetLabelText(wxT("Stop"));
    champURL->SetValue(page1->GetCurrentURL());
}

void Tab::navigating(wxWebViewEvent &event)
{
    if(infoBar->IsShown())
    {
        infoBar->Dismiss();
    }
}

void Tab::pageChargee(wxWebViewEvent &event)
{
    btnReload->SetLabelText(wxT("Act."));
}

void Tab::fOuvrirNouvelOnglet(wxWebViewEvent &event)
{
    m_auiNotebookParent->AddPage(new Tab(m_auiNotebookParent, event.GetURL()), "Nouvel onglet");
}

void Tab::titreChange(wxWebViewEvent &event)
{
    m_auiNotebookParent->SetPageText(m_auiNotebookParent->GetPageIndex(this), event.GetString());
    m_auiNotebookParent->SetPageToolTip(m_auiNotebookParent->GetPageIndex(this), event.GetString());
}

void Tab::fErreur(wxWebViewEvent &event)
{
    switch(event.GetInt())
    {
    case wxWEBVIEW_NAV_ERR_CONNECTION:
        infoBar->ShowMessage(wxT("Erreur: Nous ne pouvons pas nous connecter au serveur.\nVérifiez votre connexion Internet, vos paramètres de proxy et l'adresse URL du site."), wxICON_WARNING);
        break;
    case wxWEBVIEW_NAV_ERR_CERTIFICATE:
        infoBar->ShowMessage(wxT("Erreur: Le certificat SSL de ce site web présente un problème (ERR 526).\nPeut-être que votre connexion a été interceptée par des pirates."), wxICON_WARNING);
        break;
    /*case wxWEBVIEW_NAV_ERR_AUTH:
        fenAuth=new authentification(this, this, event.GetURL());
        fenAuth->Show();
        break;*/
    case wxWEBVIEW_NAV_ERR_SECURITY:
        infoBar->ShowMessage(wxT("Erreur: La sécurité de ce site web présente un problème.\nNous n'en savons pas plus."), wxICON_WARNING);
        break;
    case wxWEBVIEW_NAV_ERR_NOT_FOUND:
        infoBar->ShowMessage(wxT("Erreur: La page que vous demandez n'existe pas sur le serveur (ERR 404)."), wxICON_WARNING);
        break;
    case wxWEBVIEW_NAV_ERR_REQUEST:
        infoBar->ShowMessage(wxT("Erreur: La requête HTTP est incorrecte (ERR 400)."), wxICON_WARNING);
        break;
    case wxWEBVIEW_NAV_ERR_OTHER:
        infoBar->ShowMessage(wxT("Erreur: Nous avons recontré une erreur lors de la tentative de connexion.\nNous n'en savons pas plus."), wxICON_WARNING); /// Download
        /*FileDownloader test(event.GetURL());
        test.download();*/
        break;
    }
}

wxWebView *Tab::getWebView()
{
    return page1;
}

void Tab::showConsoleJS()
{
    if(this->GetSizer()->IsShown(consoleJS))
    {
        this->GetSizer()->Hide(consoleJS);
    }
    else
    {
        this->GetSizer()->Show(consoleJS);
    }
    this->Layout();
}

void Tab::Search(wxCommandEvent &event)
{
    wxURL URLSearch(wxT("https://www.google.fr/search?q=")+champSearch->GetValue());
    page1->LoadURL(URLSearch.BuildURI());
}

void Tab::onContextMenu(wxContextMenuEvent &event)
{
    event.Skip(true);
    wxMenu menu;
    menu.Append(wxID_ANY, wxT("&About"));
    PopupMenu(&menu);
}
