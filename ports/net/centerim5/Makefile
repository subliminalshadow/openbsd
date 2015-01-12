# $OpenBSD$

COMMENT=		text based IM client

DISTNAME=		centerim5-5.0.0beta2
CATEGORIES=		net

HOMEPAGE=		http://www.centerim.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes

MASTER_SITES=		http://centerim.org/download/cim5/

MODULES=		devel/cmake \
			devel/gettext
BUILD_DEPENDS=		devel/ncursesw \
			net/pidgin,-libpurple \
			devel/libsigc++-2 \
			devel/libtool \
			devel/gconf2 \
			devel/glib2

CONFIGURE_ENV=		CPPFLAGS="-I${LOCALBASE}/include" \
			LDFLAGS="-L${LOCALBASE}/lib"

.include <bsd.port.mk>
