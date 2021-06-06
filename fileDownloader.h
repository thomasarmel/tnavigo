#ifndef FILEDOWNLOADER_H_INCLUDED
#define FILEDOWNLOADER_H_INCLUDED

#include <wx/wx.h>
#include <wx/protocol/http.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>
#include <wx/url.h>

class FileDownloader
{
public:
    FileDownloader(wxString url);
    ~FileDownloader();
    bool download();

private:
    static wxString URLToFile(wxString URL);

    wxString m_url, m_file, m_server, m_path;
    wxURL urlNormalisee;
    unsigned long long int m_fileSize, m_totalRead;
};

#endif // FILEDOWNLOADER_H_INCLUDED
