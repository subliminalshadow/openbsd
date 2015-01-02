# $OpenBSD$

COMMENT =	AssaultCube First Person Shooter

V =		1.2.0.2
DISTNAME = 	AssaultCube_v$V
PKGNAME =	assaultcube-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tar.bz2

HOMEPAGE =	http://assault.cubers.net/

MASTER_SITES =	${MASTER_SITE_SOURCEFORGE:=actiongame/}

MAINTAINER =	subliminal <noxeternae@yandex.ru>

# zlib license
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes

WANTLIB +=	GL SDL X11 c m ogg pthread stdc++ z

RUN_DEPENDS = devel/sdl-image \
		audio/libvorbis \
		audio/openal

WRKSRC =	${WRKDIST}/source/src

NO_TEST =	Yes
USE_GMAKE =	Yes

MAKE_FLAGS +=	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib" \
		CXX="${CXX}"

DATADIR =	${PREFIX}/share/assaultcube

SUBST_VARS +=	DATADIR

.include <bsd.port.mk>
