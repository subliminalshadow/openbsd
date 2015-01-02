#!/bin/sh
# $OpenBSD$

GAMEDIR=~/.assaultcube

if [ -d $GAMEDIR ]; then
	echo "Using $GAMEDIR directory."
else
	echo "Creating $GAMEDIR directory."
	mkdir $GAMEDIR
	mkdir $GAMEDIR/config
	cd ${DATADIR} || exit 1
	for f in config/*; do
		cp -R $f $GAMEDIR/$f
		chmod -R u+w $GAMEDIR/$f
	done
	ln -s ${DATADIR}/bot $GAMEDIR/bot
	ln -s ${DATADIR}/packages $GAMEDIR/packages
fi

cd $GAMEDIR || exit 1
exec ${PREFIX}/libexec/assaultcube "$@"
