# $OpenBSD$

COMMENT =	freespace 2 wxlauncher

V =		0.9.4
DISTNAME = 	wxlauncher-$V
PKGNAME =	wxlauncher-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tar.gz

HOMEPAGE =	https://code.google.com/p/wxlauncher/

MASTER_SITES =  http://wxlauncher.googlecode.com/files/	

MAINTAINER =	subliminal <noxeternae@yandex.ru>

# zlib license
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes
NO_TEST=	Yes

WANTLIB +=	GL SDL X11 c m pthread stdc++ z

BUILD_DEPENDS = devel/cmake
RUN_DEPENDS = devel/sdl \
	      lang/python/2.7 \
	      x11/wxWidgets \
	      textproc/markdown

WRKDIST=${WRKDIR}/wxlauncher-$V
WRKSRC=${WRKDIR}/wxlauncher-$V

pre-configure:
	cd ${WRKDIST} && echo "all:\n\tcd build && make install" > Makefile
	cd ${WRKDIST} && mkdir -p build && cd build && cmake -DPYTHON_EXECUTABLE=/usr/local/bin/python2.7 -DUSE_OPENAL=1 -DCMAKE_INSTALL_PREFIX=${WRKDIST}/build ../ 
do-install:
	${INSTALL_PROGRAM} ${WRKDIST}/build/wxlauncher /usr/local/bin/wxlauncher
.include <bsd.port.mk>
