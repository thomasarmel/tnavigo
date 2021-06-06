#ifndef CODESOURCE_H_INCLUDED
#define CODESOURCE_H_INCLUDED

#include "mainframe.h"

class MainFrame;

class codeSource : public wxFrame
{
public:
    codeSource(const wxString &titre, const wxString &source, MainFrame *parent, wxWindow *fenetreMere);
    virtual ~codeSource();

private:
    void onURLClique(wxTextUrlEvent &event);
    wxTextCtrl *champSources;
    MainFrame *m_parent;
    wxString m_source;

    DECLARE_EVENT_TABLE()

    enum
    {
        ID_CHAMPSRC = wxID_HIGHEST + 1,
    };
};

#endif // CODESOURCE_H_INCLUDED
