#ifndef __WX_ARDUINO__
#define __WX_ARDUINO__

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include <libudev.h>

#include "serialport.h"
#include "connectargsdlg.h"

class App:public wxApp
{
   public:
      bool OnInit();
};

class Frame:public wxFrame
{
   public:
      Frame(const wxString&);

      void OnSendData(wxTimerEvent&);
      void OnConnectDevice(wxCommandEvent&);
      void OnReleaseDevice(wxCommandEvent&);
      void OnExit(wxCommandEvent&);

   private:

      enum{
	 ID_SEND_DATA = 100,
	 ID_CONNECT_DEVICE,
	 ID_RELEASE_DEVICE
      };

      static const unsigned int MAX = 2;

      wxMenu *device_path;

      wxTimer timer;

      SerialPort serial;

      wxSlider *servos[MAX];
      wxBoxSizer *box[MAX];
      wxStaticText *servos_text[MAX];
      unsigned char data[MAX];

      DECLARE_EVENT_TABLE()
};

#endif
