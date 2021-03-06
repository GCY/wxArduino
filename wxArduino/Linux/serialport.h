#ifndef __SERIAL_PORT__
#define __SERIAL_PORT__

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <error.h>

class SerialPort
{
   public:

      SerialPort();
      SerialPort(const char*,int,int,int,int);
      ~SerialPort();
      bool Open(const char*);
      bool SetBaudRate(int);
      bool SetParity(int,int,int);
      void Close();
      void Write(unsigned char*,int);
      void Read(unsigned char*,int);

   private:

      const char *path;
      int device;
      int baud_rate;
      int databits;
      int stopbits;
      int parity;
};

#endif
