# $OpenBSD$

COMMENT =		port of Arx Fatalis, 3D dungeon crawling RPG

V =			1.1.2
DISTNAME =		arx-libertatis-${V}

CATEGORIES =		games

HOMEPAGE =		http://arx-libertatis.org/

# GPLv3+
PERMIT_PACKAGE_CDROM =	Yes

WANTLIB += GL GLEW SDL c pthread freetype m openal stdc++ z

MASTER_SITES =		${MASTER_SITE_SOURCEFORGE:=arx/}

EXTRACT_SUFX =		.tar.xz

MODULES =		devel/cmake
LIB_DEPENDS =		audio/openal \
			graphics/glew \
			devel/sdl

CONFIGURE_ARGS =	-DBUILD_CRASHREPORTER=off
CONFIGURE_ENV =		LDFLAGS=-lpthread

NO_TEST =		Yes

pre-configure:
	cp ${FILESDIR}/wrapper.sh ${WRKDIST}
do-install:
	${INSTALL_SCRIPT} ${WRKDIST}/scripts/arx-install-data \
		${PREFIX}/bin/arx-install-data
	${INSTALL_PROGRAM} ${WRKBUILD}/arx ${PREFIX}/libexec
	${INSTALL_SCRIPT} ${WRKDIST}/wrapper.sh ${PREFIX}/bin/arx
	${INSTALL_PROGRAM} ${WRKBUILD}/arxsavetool ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKBUILD}/arxunpak ${PREFIX}/bin

.include <bsd.port.mk>
