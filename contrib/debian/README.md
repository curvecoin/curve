
Debian
====================
This directory contains files used to package curved/curve-qt
for Debian-based Linux systems. If you compile curved/curve-qt yourself, there are some useful files here.

## curve: URI support ##


curve-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install curve-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your curve-qt binary to `/usr/bin`
and the `../../share/pixmaps/curve128.png` to `/usr/share/pixmaps`

curve-qt.protocol (KDE)

