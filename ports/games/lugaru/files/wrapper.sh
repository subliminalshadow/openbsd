#!/bin/sh
# $OpenBSD$

cd /usr/local/lugaru || exit 1
exec /usr/local/lugaru/lugaru "$@"
