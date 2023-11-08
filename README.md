# Song_Sorter

A Qt-based application which sorts song files.

Song files are read from the ***source*** directory, then renamed based on their metadata and sorted into the ***destination*** directory. All file operations are performed on a separate thread.

Files missing title, artist, or album tags are not moved, and instead display an error within the program.

At the end of the process, empty source directories are removed, and a message confirming completion is displayed. At this point, the program may be closed.

## Notes
- Limited testing indicates that ***source*** and ***destination*** may point to the same directory.
- The thread performs a single blocking operation. This appears to be incompatible with QThread terminating gracefully. As such, the program will crash when closed. It is nothing to worry about.
- a "FAILED TO MOVE" error typically occurs because the file's source and destination paths are the same. If one appears for which this is not the case, please notify me.

Written with Qt 6.4.0 and taglib 1.13.1, using GCC 11.2.
