#include "Logger.h"

#include <Arduino.h>


// static variables

int Logger::maxloglevel = LOGLEVEL_CRITICAL;
int Logger::printmode = PRINTMODE_SERIAL


// constructors

Logger::Logger(const String & tag) {
  this->tag = tag;
  this->loglevel = LOGLEVEL_CRITICAL;
}


Logger::Logger(const String & tag, int loglevel) {
  this->tag = tag;
  this->loglevel = loglevel;
}


// public functions

bool Logger::setMaxLoglevel(int mll) {
  maxloglevel = mll;
  return true;
}


int Logger::getMaxLoglevel() {
  return maxloglevel;
}


bool Logger::setLogLevel(int ll) {
  this->loglevel = ll;
  return true;
}


int Logger::getLogLevel(int ll) const {
  return this->loglevel;
}


// private functions

bool Logger::checkLogLevel(int functionloglevel) const {
  if(this->loglevel < functionloglevel) {
    return false;
  }

  if(this->maxloglevel < functionloglevel) {
    return false;
  }

  return true;
}


void Logger::printSerial(int functionloglevel, const String & msg) const {
  switch(functionloglevel) {
    case LOGLEVEL_CRITICAL:
      Serial.print("CRITICAL");
      break;

    case LOGLEVEL_ERROR:
      Serial.print("CRITICAL");
      break;

    case LOGLEVEL_WARNING:
      Serial.print("CRITICAL");
      break;

    case LOGLEVEL_INFO:
      Serial.print("CRITICAL");
      break;

    case LOGLEVEL_DEBUG:
      Serial.print("CRITICAL");
      break;

    default:
      Serial.print("NONE");
      break;
  }

  Serial.print("(");
  Serial.print(this->tag);
  Serial.print("): ");
  Serial.println(msg);

  return;
}

