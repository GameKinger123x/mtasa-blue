/************************************************************************
	filename: 	CEGUIEventArgs.h
	created:	21/2/2004
	author:		Paul D Turner
	
	purpose:	Defines base EventArgs class used with event signalling
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://www.cegui.org.uk)
    Copyright (C)2004 - 2005 Paul D Turner (paul@cegui.org.uk)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#ifndef _CEGUIEventArgs_h_
#define _CEGUIEventArgs_h_

#include "CEGUIBase.h"


// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Base class used as the argument to all subscribers Event object.

	The base EventArgs class does not contain any useful information, it is intended
	to be specialised for each type of event that can be generated by objects within
	the system.  The use of this base class allows all event subscribers to have the
	same function signature.

	The \a handled field is used to signal whether an event was actually handled or not.  While
	the event system does not look at this value, code at a higher level can use it to determine
	how far to propagate an event.
*/
class CEGUIEXPORT EventArgs
{
public:
	/*************************************************************************
		Construction
	*************************************************************************/
	EventArgs(void) : handled(false) {}
	virtual ~EventArgs(void) {}


	/*************************************************************************
		Data members
	*************************************************************************/
	bool	handled;		//!< handlers should set this to true if they handled the event, or false otherwise.
};

} // End of  CEGUI namespace section

#endif	// end of guard _CEGUIEventArgs_h_
