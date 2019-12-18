#include "codesource.h"

BEGIN_EVENT_TABLE(codeSource, wxFrame)
    EVT_TEXT_URL(ID_CHAMPSRC, codeSource::onURLClique)
END_EVENT_TABLE()

codeSource::codeSource(const wxString &titre, const wxString &source, MainFrame *parent, wxWindow *fenetreMere) : wxFrame(fenetreMere, wxID_ANY, titre, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE), m_parent(parent), m_source(source)
{
    champSources=new wxTextCtrl(this, ID_CHAMPSRC, source, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_AUTO_URL);
}

codeSource::~codeSource()
{
}

void codeSource::onURLClique(wxTextUrlEvent &event)
{
    if(event.GetMouseEvent().ButtonDown(wxMOUSE_BTN_LEFT))
    {
        wxString URL=m_source.Mid(event.GetURLStart(), (event.GetURLEnd() - event.GetURLStart()));
        m_parent->fNewTabSources(URL);
    }
}
