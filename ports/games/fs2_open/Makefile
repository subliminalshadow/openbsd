# $OpenBSD$

COMMENT =	freespace 2 open

V =		3_7_2_RC4
DISTNAME = 	fs2_open_$V_src
PKGNAME =	fs2_open-$V
CATEGORIES =	games
EXTRACT_SUFX =	.tgz

HOMEPAGE =	http://scp.indiegames.us/

MASTER_SITES =	http://swc.fs2downloads.com/builds/

PERMIT_DISTFILES_FTP =		Yes
PERMIT_PACKAGE_CDROM =		Yes
PERMIT_PACKAGE_FTP =		Yes
NO_TEST=	Yes

WANTLIB =	GL SDL c m ogg pthread stdc++ GLU lua5.1 openal png theora vorbis vorbisfile

BUILD_DEPENDS = devel/autoconf/2.69 \
                devel/automake/1.10 \
		sysutils/ggrep # needed for automating DRM chmod

RUN_DEPENDS = devel/sdl \
		devel/jansson \
		audio/libvorbis \
		multimedia/libtheora \
		graphics/png \
		graphics/jpeg \
		audio/openal \
		lang/lua/5.1

AUTOCONF_VERSION=2.69
AUTOMAKE_VERSION=1.10
CONFIGURE_STYLE = gnu
WRKDIST=${WRKDIR}/fs2_open_$V
WRKSRC=${WRKDIR}/fs2_open_$V

pre-configure:
		# game needs lua.pc, we have lua51.pc, so make that one
		cp /usr/local/lib/pkgconfig/lua51.pc /usr/local/lib/pkgconfig/lua.pc
		cd ${WRKSRC} && ./autogen.sh
do-install:
		cd ${WRKSRC} && make install
post-install:
		# makes DRM acceleration accessible to the end user, adds 'chmod 0666 /dev/drm*'
		# to /etc/rc.local if it's not already present there
		ggrep -q -F 'chmod 0666 /dev/drm*' /etc/rc.local || echo 'chmod 0666 /dev/drm*' >> /etc/rc.local
.include <bsd.port.mk>
