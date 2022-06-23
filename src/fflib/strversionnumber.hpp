// -*- Mode : c++ -*-
//
// SUMMARY  :      
// USAGE    :        
// ORG      : 
// AUTHOR   : Frederic Hecht
// E-MAIL   : hecht@ann.jussieu.fr
//

/*
 
 This file is part of Freefem++
 
 Freefem++ is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 Freefem++  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with Freefem++; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#pragma once

#include <string>
using namespace std;

#define xstrg(s) strg(s)
#define strg(s) #s

#ifndef kame
// to global.cpp
double VersionNumber();
string StrVersionNumber();

#define VersionFreeFem 1.1

double VersionNumber() {
	return VersionFreeFem;
}

string StrVersionNumber() {
	ostringstream version;
	version.precision(8);
	version << xstrg(VersionFreeFem)
		<< " (VersionFreeFemDate - git GitVersion)";
	return version.str();
}
#endif