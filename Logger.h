#ifndef __LOGGER_H__
#define __LOGGER_H__


#include <Arduino.h>


#define LOGLEVEL_CRITICAL 50
#define LOGLEVEL_ERROR 40
#define LOGLEVEL_WARNING 30
#define LOGLEVEL_INFO 20
#define LOGLEVEL_DEBUG 10
#define LOGLEVEL_NOTSET 0

#define PRINTMODE_SERIAL 0



class Logger {
  private:
    static int maxloglevel;
    static int printmode;
  
    int loglevel;
    String tag;


  public:
    Logger(const String & tag);
    Logger(const String & tag, int loglevel);

    static bool setMaxLoglevel(int mll);
    static int getMaxLoglevel();

    // TODO: add set/get for printmode

    bool setLogLevel(int ll);
    int getLogLevel(int ll) const;
    
    bool c(const String & msg) const;
    bool e(const String & msg) const;
    bool w(const String & msg) const;
    bool i(const String & msg) const;
    bool d(const String & msg) const;

    private:
      bool checkLogLevel(int functionloglevel) const;

      // TODO: add printMessage mit printmode switch
      
      void printSerial(int functionloglevel, const String & msg) const;

};


#endif
