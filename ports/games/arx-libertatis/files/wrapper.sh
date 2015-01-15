#!/bin/sh
# $OpenBSD$

cd $HOME || exit 1
exec /usr/local/libexec/arx "$@"
