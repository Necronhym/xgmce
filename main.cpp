/*	xgmce
 *	Xserver Grab Mouse Click Event
 *	Necronhym 29.06.2021
 *	
 *	Allows for simultanious logging and
 *	execution of mouse click events
 *
 *	The events are printed to console
 *	in a x:i y:i b:i format
 *	Where x and y are the on screen coordiantes
 *	and b is the mouse botton id.
 *	1 being left, 2 middle, 3 right, scrool up 4 down 5.
 */
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
int main()
	{
		Display* d = XOpenDisplay(NULL);
		Window w = DefaultRootWindow(d);
		XEvent e;
		XGrabPointer(d, w, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
				GrabModeAsync, GrabModeAsync, None,
				None, CurrentTime);
		int px, py, rx, ry, b;
		while(true)
			{
				XNextEvent(d, &e);
				switch (e.type)
					{
						case ButtonPress:
							b = e.xbutton.button;
							px = e.xbutton.x;
							py = e.xbutton.y;
						break;
						case ButtonRelease:
							b = e.xbutton.button;
							rx = e.xbutton.x;
							ry = e.xbutton.y;
							goto exit;
						break;
					}
			}
		exit:
		XUngrabPointer(d, CurrentTime);
		//std::cout << "xdotool mousemove "<< px << " " << py << " click " << b << std::endl;
		printf("x:%i y:%i button:%i\n" , px, py, b);
		XTestFakeMotionEvent(d, 0, px, py, CurrentTime);
		XTestFakeButtonEvent(d, b, True, CurrentTime);
		XTestFakeMotionEvent(d, 0, rx, ry, CurrentTime);
		XTestFakeButtonEvent(d, b, False, CurrentTime);
		XCloseDisplay(d);
		return 0;
	}
