#include "mainframe.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_AUINOTEBOOK_PAGE_CLOSED(ID_TABMANAGER, MainFrame::onTabMouseClosed)

    EVT_CLOSE(MainFrame::onClose)
    EVT_MENU(wxID_NEW, MainFrame::fNewTab)
    EVT_MENU(wxID_CLOSE, MainFrame::fCloseTab)
    EVT_MENU(ID_SOURCES, MainFrame::displaySources)
    EVT_MENU(wxID_PRINT, MainFrame::fPrint)
    EVT_MENU(wxID_SAVE, MainFrame::fSave)
    EVT_MENU(wxID_EXIT, MainFrame::fQuit)
    EVT_MENU(ID_MENUMAJ, MainFrame::fMAJ)
    EVT_MENU(ID_MENUPARAM, MainFrame::fSettings)
    EVT_MENU(wxID_EXECUTE, MainFrame::fConsoleJS)
    EVT_CONTEXT_MENU(MainFrame::onRightClick)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE),
    sysConfigDir(wxStandardPaths::Get().GetUserConfigDir())  /// dossier des fichiers de configuration des programmes pour l'utilisateur courant, wxGetCwd() pour le dossier du programme en question
{
    tabManager=new wxAuiNotebook(this, ID_TABMANAGER, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_CLOSE_ON_ALL_TABS);

    menuBar=new wxMenuBar();
    menuFile=new wxMenu();
    menuNav=new wxMenu();
    menuOptions=new wxMenu();
    menuFile->Append(wxID_SAVE, "&Enregistrer\tCTRL+S", "Enregistrer la page actuelle");
    menuFile->Append(wxID_PRINT, "&Imprimer\tCTRL+P", "Imprimer la page actuelle");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "&Quitter\tCTRL+Q", "Quitter et fermer la fenetre");
    menuBar->Append(menuFile, wxT("Fichier"));
    menuNav->Append(wxID_NEW, "&Nouvel onglet\tCTRL+T", "Creer un nouvel onglet");
    menuNav->Append(wxID_CLOSE, "&Fermer l'onglet\tSHIFT+CTRL+T", "Fermer cet onglet");
    menuNav->Append(ID_SOURCES, "&Code source\tCTRL+U", "Afficher le code source de la page");
    menuNav->Append(wxID_EXECUTE, "&Console JavaScript\tSHIFT+CTRL+E", "Afficher la console JavaScript");
    menuBar->Append(menuNav, wxT("Navigation"));
    menuOptions->Append(ID_MENUPARAM, "&Parametres", "Modifier les parametres du navigateur");
    menuOptions->Append(ID_MENUMAJ, "&Mise a jour", "Rechercher et installer des mises a jour");
    menuBar->Append(menuOptions, wxT("Options"));
    SetMenuBar(menuBar);

    dialogueEnregistrer=new wxFileDialog(this, wxT("Enregistrer la page"), wxEmptyString, wxEmptyString, wxT("Fichiers html (*.html)|*.html|Tous les fichiers (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    initConf();
    if(wxGetApp().argc >= 2)
    {
        onArgvArgc();
    }
    else
    {
        tabManager->AddPage(new Tab(tabManager, pageStart), "Nouvel onglet");
    }

}

MainFrame::~MainFrame()
{
}

void MainFrame::fNewTab(wxCommandEvent &event)
{
    tabManager->AddPage(new Tab(tabManager, pageStart), "Nouvel onglet", true);
}

void MainFrame::fCloseTab(wxCommandEvent &event)
{
    if (tabManager->GetSelection() != wxNOT_FOUND)
    {
        tabManager->DeletePage(tabManager->GetSelection());
        if (tabManager->GetPageCount() <= 0)
        {
            tabManager->AddPage(new Tab(tabManager, pageStart), "Nouvel onglet");
        }
    }
    else
    {
        wxMessageBox(wxT("Erreur, vous tentez de fermer un onglet qui n'existe pas"), wxT("Erreur"), wxICON_WARNING);
    }
}

Tab *MainFrame::currentTab()
{
    return (Tab*)tabManager->GetCurrentPage();
}

void MainFrame::fQuit(wxCommandEvent &event)
{
    tabManager->DeleteAllPages();
    Close();
}

void MainFrame::onClose(wxCloseEvent &event)
{
    tabManager->DeleteAllPages();
    Destroy();
}

void MainFrame::fPrint(wxCommandEvent &event)
{
    currentTab()->getWebView()->Print();
}

void MainFrame::fSave(wxCommandEvent &event)
{
    wxString source=currentTab()->getWebView()->GetPageSource();
    wxString cibleEnregistrer;
    wxFile fichierCibleEnregistrer;
    if((dialogueEnregistrer->ShowModal()) == wxID_OK)
    {
        cibleEnregistrer=dialogueEnregistrer->GetPath();
        if(!fichierCibleEnregistrer.Open(cibleEnregistrer, wxFile::write))
        {
            wxMessageBox(wxT("Erreur lors de l'ouverture du fichier.\nPeut-être celui-ci n'existe pas ou vous n'avez pas les droits nécessaires pour l'ouvrir."), wxT("Erreur d'ouverture"), wxICON_WARNING);
            return;
        }
        if(!fichierCibleEnregistrer.Write(source))
        {
            wxMessageBox(wxT("Erreur lors de l'écriture du fichier.\nPeut-être n'avez-vous pas les droits suffisants ou celui-ci est utilisé par un autre programme."), wxT("Erreur d'écriture"), wxICON_WARNING);
            return;
        }
        fichierCibleEnregistrer.Close();
    }
}

void MainFrame::initConf()
{
    configDir=sysConfigDir+wxFileName::GetPathSeparators()+wxT(".TNavigo");
    if (!wxDirExists(configDir))
    {
        if (!wxMkdir(configDir))
        {
            wxMessageBox(wxT("Erreur, impossible d'accéder au dossier ") + configDir + wxT(".\nVérifiez les autorisations et relancez le programme."), wxT("Erreur configuration"), wxICON_WARNING);
            return;
        }
    }
    fichierConf=new wxFileConfig(wxT("TNavigo"), wxT("Thomas"), configDir + wxFileName::GetPathSeparators() + wxT("config.conf"));
    fichierConf->Read(wxT("startupPage"), &pageStart, wxWebViewDefaultURLStr);
    if(pageStart==wxEmptyString)
    {
        pageStart=wxWebViewDefaultURLStr;
    }
}

void MainFrame::onArgvArgc()
{
    if(wxFileName::IsFileReadable(wxGetApp().argv[1]))
    {
        tabManager->AddPage(new Tab(tabManager, wxT("file://")+wxGetApp().argv[1]), "Nouvel onglet");
    }
    else
    {
        wxMessageBox(wxT("Erreur lors de l'ouverture du fichier.\nPeut-être celui-ci n'existe pas ou vous n'avez pas les droits nécessaires pour l'ouvrir."), wxT("Erreur d'ouverture"), wxICON_WARNING);
        tabManager->AddPage(new Tab(tabManager, pageStart), "Nouvel onglet");
    }
}

void MainFrame::fMAJ(wxCommandEvent &event)
{
    if((wxMessageBox(wxT("Fermer ce programme et rechercher des mises à jour ?"), wxT("Mise à jour"), wxYES_NO | wxICON_QUESTION)) == wxYES)
    {
        wxExecute(wxT("up_dater.exe"));
        wxExit();
    }
}

void MainFrame::fSettings(wxCommandEvent &event)
{
    fenParametres=new parametres(fichierConf, this);
    fenParametres->Show();
}

void MainFrame::fConnectWithAuth(wxString url)
{
    currentTab()->getWebView()->LoadURL(url);
}

void MainFrame::onTabMouseClosed(wxAuiNotebookEvent& event)
{
    if (tabManager->GetPageCount() <= 0)
    {
        tabManager->AddPage(new Tab(tabManager, pageStart), "Nouvel onglet");
    }
}

void MainFrame::fNewTabSources(wxString url)
{
    tabManager->AddPage(new Tab(tabManager, url), "Nouvel onglet", true);
}

void MainFrame::onRightClick(wxContextMenuEvent &event)
{
    //page1->EnableContextMenu(false);
    event.Skip(true);
    wxMessageBox("test");
    wxMenu menu;
    menu.Append(wxID_ANY, wxT("&About"));
    PopupMenu(&menu);
}


void MainFrame::displaySources(wxCommandEvent &event)
{
    wxWebView *currentTabWebView=currentTab()->getWebView();
    pageSources=new codeSource(wxT("Sources: ")+currentTabWebView->GetCurrentURL(), currentTabWebView->GetPageSource(), this, this);
    pageSources->Show();
}

void MainFrame::fConsoleJS(wxCommandEvent &event)
{
    currentTab()->showConsoleJS();
}
