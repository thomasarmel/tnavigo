#include "fileDownloader.h"

FileDownloader::FileDownloader(wxString url) : m_url(url)
{
    m_fileSize=0;
    m_totalRead=0;
    urlNormalisee.SetURL(m_url);
    m_server=urlNormalisee.GetServer();
    m_path=urlNormalisee.GetPath();
    m_file=URLToFile(m_path);
}

FileDownloader::~FileDownloader()
{}

bool FileDownloader::download()
{
    m_totalRead=0;
    wxHTTP http;
    //http.SetHeader(_T("Content-type"), contentType);
    http.SetTimeout(10);

    wxFileOutputStream output(m_file);
    wxDataOutputStream store(output);

    if (http.Connect(m_server, 80))
    {
        wxInputStream *stream;
        stream = http.GetInputStream(m_path);
        m_fileSize=(unsigned long long int)stream->GetSize();

        if (stream == NULL)
        {
            output.Close();
        }
        else
        {
            unsigned char buffer[1024];
            int byteRead;
            // receive stream
            while (!stream->Eof())
            {
                stream->Read(buffer, sizeof(buffer));
                store.Write8(buffer, sizeof(buffer));
                byteRead = stream->LastRead();
                m_totalRead+=(unsigned long long int)stream->LastRead();
                std::cout << 100*((double)m_totalRead)/((double)m_fileSize) << " %\r" << std::flush;
                if (byteRead <= 0)
                {
                    break;
                }
            }
            output.Close();
        }
    }
    else
    {
        output.Close();
        return false;
    }
    return true;
}

wxString FileDownloader::URLToFile(wxString URL)
{
    size_t lastSlash=URL.find_last_of("/");
    size_t fileSizeRight=URL.Len()-(lastSlash+1);
    return URL.Right(fileSizeRight);
}
