/* ---------------------------------------------------------------------------
 #
 #       L-Py: L-systems in Python
 #
 #       Copyright 2003-2008 UMR Cirad/Inria/Inra Dap - Virtual Plant Team
 #
 #       File author(s): F. Boudon (frederic.boudon@cirad.fr)
 #
 # ---------------------------------------------------------------------------
 #
 #                      GNU General Public Licence
 #
 #       This program is free software; you can redistribute it and/or
 #       modify it under the terms of the GNU General Public License as
 #       published by the Free Software Foundation; either version 2 of
 #       the License, or (at your option) any later version.
 #
 #       This program is distributed in the hope that it will be useful,
 #       but WITHOUT ANY WARRANTY; without even the implied warranty of
 #       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 #       GNU General Public License for more details.
 #
 #       You should have received a copy of the GNU General Public
 #       License along with this program; see the file COPYING. If not,
 #       write to the Free Software Foundation, Inc., 59
 #       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 #
 # ---------------------------------------------------------------------------
 */

#ifndef __LSYS_TRACKER_H__
#define __LSYS_TRACKER_H__

#include "pylsys_config.h"
#include <stddef.h>

PYLSYS_BEGIN_NAMESPACE

/*---------------------------------------------------------------------------*/

// #define TRACKER_ENABLED

#ifdef TRACKER_ENABLED

class PYLSYS_API Tracker {
public:

	static size_t Module;
	static size_t AxialTree;
	static size_t LsysContext;
	static size_t LsysOptionValue;
	static size_t LsysOption;
	static size_t LsysOptions;
	static size_t LsysRule;
	static size_t Lsystem;
	static size_t ModuleClass;
	static size_t ModuleClassTable;
	static size_t StringInterpreter;
	static size_t StringMatching;
	static void printReport();
};

#define IncTracker(classname) ++Tracker::classname;
#define DecTracker(classname) --Tracker::classname;

#else

#define IncTracker(classname) 
#define DecTracker(classname)

#endif


PYLSYS_END_NAMESPACE

/*---------------------------------------------------------------------------*/

#endif
