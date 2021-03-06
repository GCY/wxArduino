#include "wxarduino.h"

IMPLEMENT_APP(App)
DECLARE_APP(App)

bool App::OnInit()
{
   wxFrame *frame = new Frame(wxT("wxArduino"));

   frame->Show(true);

   return true;
}

BEGIN_EVENT_TABLE(Frame,wxFrame)
   EVT_MENU(wxID_EXIT,Frame::OnExit)
   EVT_MENU(ID_CONNECT_DEVICE,Frame::OnConnectDevice)
   EVT_MENU(ID_RELEASE_DEVICE,Frame::OnReleaseDevice)
   EVT_TIMER(ID_SEND_DATA,Frame::OnSendData)
END_EVENT_TABLE()

Frame::Frame(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxDefaultSize,wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU),timer(this,ID_SEND_DATA)
{
   timer.Stop();

   wxMenu *file = new wxMenu;
   file->Append(wxID_EXIT,wxT("E&xit\tAlt-e"),wxT("Exit"));
   wxMenu *tools = new wxMenu;
   tools->Append(ID_CONNECT_DEVICE,wxT("C&onnect Device\tAlt-c"),wxT("Connect Device"));
   tools->Append(ID_RELEASE_DEVICE,wxT("R&elease Device\tAlt-r"),wxT("Release Device"));

   wxMenuBar *bar = new wxMenuBar;
   bar->Append(file,wxT("File"));
   bar->Append(tools,wxT("Tools"));
   SetMenuBar(bar);

   wxBoxSizer *top = new wxBoxSizer(wxVERTICAL);
   this->SetSizer(top);

   for(int i = 0;i < MAX;++i){
      box[i] = new wxBoxSizer(wxHORIZONTAL);
      top->Add(box[i],0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);

      wxString text;
      text.Printf("Servo %d：",i + 1);
      servos_text[i] = new wxStaticText(this,wxID_STATIC,text,wxDefaultPosition,wxDefaultSize,0);
      box[i]->Add(servos_text[i],0,wxALIGN_CENTER_HORIZONTAL |  wxALIGN_CENTER_VERTICAL,5);

      servos[i] = new wxSlider(this,wxID_ANY,90,0,180,wxDefaultPosition,wxSize(200,-1),wxSL_HORIZONTAL | wxSL_AUTOTICKS | wxSL_LABELS);
      box[i]->Add(servos[i],0,wxALIGN_CENTER_HORIZONTAL | wxALL,5);
   }

   CreateStatusBar(2);
   SetStatusText(wxT("wxArduino"));

   top->Fit(this);
   top->SetSizeHints(this);
}

void Frame::OnSendData(wxTimerEvent &event)
{
   for(int i = 0;i < MAX;++i){
      data[i] = servos[i]->GetValue();
   }
   serial.Write(data,MAX);
}

void Frame::OnConnectDevice(wxCommandEvent &event)
{
    ConnectArgsDialog dlg(this,wxID_ANY,wxT("Connect"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE);

    if(dlg.ShowModal() == wxID_OK){
       serial.Open(dlg.GetDevicePath().mb_str());
       serial.SetBaudRate(wxAtoi(dlg.GetBaudRate()));
       serial.SetParity(8,1,'N');

       timer.Start(30);
    }
}

void Frame::OnReleaseDevice(wxCommandEvent &event)
{
   serial.Close();
   timer.Stop();
}

void Frame::OnExit(wxCommandEvent &event)
{
   timer.Stop();
   Close();
}
