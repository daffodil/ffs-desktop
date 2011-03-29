FFS-Desktop

This is an attempt at creating a FlightGear launcher xplatform using Qt.

## Update end March 2011. The developer is also looking at https://gitorious.org/fgx



Fetures:
* DNS lookup of mpServers
* Embedded mpMap
* Property Tree Browser
* Airport searchable (import to sqlite or mysql)
* 



Ideas are:

Make it lightweight (I know with Qt).
* ability to make it dissapear to the "desktop status"
* Embedded browser
* dynamic selection of MpServers
* Downladable aircraft straight from GIT


===== Help Wanted =====

I'm not by any stretch of the imagination a c++ coder,
more familiar with pyqt, python, php and javascript etc

Someone with c++ experience and qt would be useful, if even for code review etc.


===================================
Thoughts..

Aircraft can be loaded with 
* command line "fgfs --show-aircraft"
* or parsing the xml-set's (which can now indlude Aircraft directories)


MultiPlayer
* there could be an embedded map (google map or other background) and traffic data from
* Flight gear instance or
* telnet to mpservers or
* mpMap calls (every few seconds)
THe idea of slaving a map to FlightGear leads to the possibility of moving aircraft on a map

Chat
* there could be a chat interface



