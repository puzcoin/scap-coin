
Debian
====================
This directory contains files used to package safecapitald/safecapital-qt
for Debian-based Linux systems. If you compile safecapitald/safecapital-qt yourself, there are some useful files here.

## safecapital: URI support ##


safecapital-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install safecapital-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your safecapitalqt binary to `/usr/bin`
and the `../../share/pixmaps/safecapital128.png` to `/usr/share/pixmaps`

safecapital-qt.protocol (KDE)

