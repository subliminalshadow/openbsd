# $OpenBSD$

COMMENT =	freespace 2 open

V =		3_7_0
DISTNAME = 	fs2_open_$V_src
PKGNAME =	fs2_open-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tgz

HOMEPAGE =	http://scp.indiegames.us/

MASTER_SITES =	http://swc.fs2downloads.com/builds/

MAINTAINER =	subliminal <noxeternae@yandex.ru>

# zlib license
PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes
NO_TEST=	Yes

WANTLIB +=	GL SDL X11 c m ogg pthread stdc++ z

BUILD_DEPENDS = devel/autoconf/2.69 \
                devel/automake/1.9

RUN_DEPENDS = devel/sdl \
		devel/jansson \
		audio/libvorbis \
		multimedia/libtheora \
		graphics/png \
		audio/openal \
		lang/lua/5.1

AUTOCONF_VERSION=2.69
AUTOMAKE_VERSION=1.9
CONFIGURE_STYLE = gnu
WRKDIST=${WRKDIR}/fs2_open_$V
WRKSRC=${WRKDIR}/fs2_open_$V

pre-configure:
		cp /usr/local/lib/pkgconfig/lua51.pc /usr/local/lib/pkgconfig/lua.pc
		cd ${WRKSRC} && ./autogen.sh
do-install:
		cd ${WRKSRC} && make install
post-install:
		grep -q -F 'chmod 0666 /dev/drm*' /etc/rc.local || echo 'chmod 0666 /dev/drm*' >> /etc/rc.local
.include <bsd.port.mk>
