#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <Arduino.h>


#define LOGLEVEL_CRITICAL 50
#define LOGLEVEL_ERROR 40
#define LOGLEVEL_WARNING 30
#define LOGLEVEL_INFO 20
#define LOGLEVEL_DEBUG 10
#define LOGLEVEL_NOTSET 0

#define PRINTMODE_SERIAL 1



class Logger {
  private:
    static int maxloglevel;
    static int printmode;
  
    int loglevel;
    String tag;


  public:
    Logger(const String & tag);
    Logger(const String & tag, int loglevel);

    static void setMaxLoglevel(int mll);
    static int getMaxLoglevel();

    static void setPrintMode(int pm);
    static int getPrintMode();

    void setLogLevel(int ll);
    int getLogLevel(int ll) const;
    
    void c(const String & msg) const;
    void e(const String & msg) const;
    void w(const String & msg) const;
    void i(const String & msg) const;
    void d(const String & msg) const;

    private:
      bool checkLogLevel(int functionloglevel) const;
      void printMessage(int functionloglevel, const String & msg) const;
      
      void printSerial(const String & msg) const;

};


#endif
