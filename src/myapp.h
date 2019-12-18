#ifndef MYAPP_H_INCLUDED
#define MYAPP_H_INCLUDED

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

#include <wx/textctrl.h>
#include <wx/webview.h>
#include <wx/event.h>
//#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/filesys.h>
#include <wx/filedlg.h>
#include <wx/process.h>
#include <wx/infobar.h>
#include <wx/aui/auibook.h>

#include "mainframe.h"
#include "codesource.h"
#include "parametres.h"
#include "auth.h"
#include "fileDownloader.h"
#include "tab.h"

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

DECLARE_APP(MyApp);

#endif // MYAPP_H_INCLUDED
