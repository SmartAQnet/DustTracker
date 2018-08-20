#include "Logger.h"

#include <Arduino.h>


// static variables

int Logger::maxloglevel = LOGLEVEL_NOTSET;
int Logger::printmode = PRINTMODE_SERIAL;


// constructors

Logger::Logger(const String & tag) {
  this->tag = tag;
  this->loglevel = LOGLEVEL_NOTSET;
}


Logger::Logger(const String & tag, int loglevel) {
  this->tag = tag;
  this->loglevel = loglevel;
}


// public functions

void Logger::setMaxLoglevel(int mll) {
  maxloglevel = mll;
}


int Logger::getMaxLoglevel() {
  return maxloglevel;
}


void Logger::setPrintMode(int pm) {
  printmode = pm;
}


int Logger::getPrintMode() {
  return printmode;
}


void Logger::setLogLevel(int ll) {
  this->loglevel = ll;
}


int Logger::getLogLevel(int ll) const {
  return this->loglevel;
}


void Logger::c(const String & msg) const {
  printMessage(LOGLEVEL_CRITICAL, msg);
}


void Logger::e(const String & msg) const {
  printMessage(LOGLEVEL_ERROR, msg);
}


void Logger::w(const String & msg) const {
  printMessage(LOGLEVEL_WARNING, msg);
}


void Logger::i(const String & msg) const {
  printMessage(LOGLEVEL_INFO, msg);
}


void Logger::d(const String & msg) const {
  printMessage(LOGLEVEL_DEBUG, msg);
}


// private functions

bool Logger::checkLogLevel(int functionloglevel) const {
  if(this->loglevel > functionloglevel) {
    return false;
  }

  if(this->maxloglevel > functionloglevel) {
    return false;
  }

  return true;
}


void Logger::printMessage(int functionloglevel, const String & msg) const {
  if(checkLogLevel(functionloglevel) == false)
    return;

  // make prefix
  String newmsg = "";
  
  switch(functionloglevel) {
    case LOGLEVEL_CRITICAL:
      newmsg += "CRITICAL";
      break;

    case LOGLEVEL_ERROR:
      newmsg += "ERROR";
      break;

    case LOGLEVEL_WARNING:
      newmsg += "WARNING";
      break;

    case LOGLEVEL_INFO:
      newmsg += "INFO";
      break;

    case LOGLEVEL_DEBUG:
      newmsg += "DEBUG";
      break;

    default:
      newmsg += "NONE";
      break;
  }

  newmsg += "(" + this->tag + "): " + msg;

  // choose print mode
  switch(this->printmode) {
    case PRINTMODE_SERIAL:
      printSerial(newmsg);
      break;

    default:
      break;
  }

  return;
}


void Logger::printSerial(const String & msg) const {
  Serial.println(msg);
}

