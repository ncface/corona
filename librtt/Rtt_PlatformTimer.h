//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Corona Labs Inc.
// Contact: support@coronalabs.com
//
// This file is part of the Corona game engine.
//
// Commercial License Usage
// Licensees holding valid commercial Corona licenses may use this file in
// accordance with the commercial license agreement between you and 
// Corona Labs Inc. For licensing terms and conditions please contact
// support@coronalabs.com or visit https://coronalabs.com/com-license
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU General
// Public license version 3. The license is as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL3 included in the packaging
// of this file. Please review the following information to ensure the GNU 
// General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html
//
// For overview and more information on licensing please refer to README.md
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _Rtt_PlatformTimer_H__
#define _Rtt_PlatformTimer_H__

#include "Rtt_MCallback.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

class PlatformTimer
{
	Rtt_CLASS_NO_COPIES( PlatformTimer )

	public:
		PlatformTimer( MCallback& callback );
		virtual ~PlatformTimer();

	public:
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual void SetInterval( U32 milliseconds ) = 0;
		virtual bool IsRunning() const = 0;

		// Problem: On iOS, when the screen locks and the display turns off,
		// CADisplayLink timers stop firing.
		// In my experiments, backgrounding allows the CADisplayLink to continue firing, though if the display sleeps/locks, the timer stops firing.
		// To avoid this problem, we need to switch off of CADisplayLink to NSTimer.
		// Since we can't easily distinguish between a screen lock and backgrounding, we treat both events as the same and switch to the background timer.
		// Note that CVDisplayLink may have similar issues on Mac when there is no display, offscreen rendering, and possibly VNC remote desktop.
		// But as a more general principle, we may want all platforms to use a "nice-to-CPU" background timer which invokes less frequently to ease CPU cost. 
		virtual void SwitchToForegroundTimer();
		virtual void SwitchToBackgroundTimer();
	
	public:
		// Allow manual invocation
		Rtt_FORCE_INLINE void operator()() { fCallback(); }

//	protected:
//		Rtt_FORCE_INLINE MCallback& Callback() { return fCallback; }

	private:
		MCallback& fCallback;
};

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------

#endif // _Rtt_PlatformTimer_H__