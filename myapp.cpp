#include "myapp.h"

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *frm=new MainFrame(_T("TNavigo"));
    frm->Show();
    return true;
}
