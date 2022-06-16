#pragma once
#ifndef kame

#include "mode_open.hpp"
#if _WIN32
#include "ff-win32.cpp"
#else
#include <unistd.h>
#endif

// FFCS: required for chdir() when g++ 4.7 is used
#include <unistd.h>

// FFCS: redirecting visualization output
#include "ffapi.hpp"
#include "strversionnumber.hpp"
#include <string>

extern long mpirank;
extern long verbosity;
extern FILE *ThePlotStream; // Add for new plot. FH oct 2008
// for the environnement variables ...
#endif
extern const char *prognamearg;
extern bool waitatend;
#ifndef kame
extern const char *edpfilenamearg;

extern bool consoleatend;
extern bool echo_edp;
extern bool NoGraphicWindow;
extern const char *  check_plugin;

char *Shell_Space(const char *s);

char *Shell_Space(const char *s) {
  const char *c = s;
  int nbspace;
  int i;
  for (i = 0; i < 100000; ++i) {
    if (!s[i]) break;
    else if (isspace(s[i])) ++nbspace;
  }
  if (!(i < 100000)) {
    cerr << " Bug Shell_Space routine " << endl;
    exit(1);
  }

#ifdef _WIN32
  char * p = new char[i + 1 + nbspace];
  char * q = p;
  for (i = 0; i < 100000; ++i) {
    if (!s[i]) break;
    else if (isspace(s[i])) {
      *q ++= '^';
      *q ++= s[i];
    }
    else *q ++= s[i];
  }
#else
  char *p = new char[i + nbspace];
  char *q = p;
  for (i = 0; i < 100000; ++i) {
    if (!s[i]) break;
    else if (isspace(s[i])) {
      *q ++= '\\';
      *q ++= s[i];
    }
    else *q ++= s[i];
  }
#endif
  *q ++= '\0';
  assert(q - p <= i + nbspace);
  return p;
}

extern void (*init_lgparallele)();
extern bool load(string s);
// <<getprog>> called by [[file:../lglib/lg.ypp::getprog]]

#endif //GETPROG_UNIX_HPP_


