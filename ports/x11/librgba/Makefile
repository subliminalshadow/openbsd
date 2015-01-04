# $OpenBSD$

COMMENT=	rgba gtk+ module
DISTNAME=	librgba
V=		1.0
PKGNAME=	librgba-${V}
CATEGORIES=	x11
REVISION=	0
EXTRACT_SUFX=	.tar.gz

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WANTLIB += X11

LIB_DEPENDS=	x11/gtk+2
NO_BUILD=	Yes
WRKSRC=${WRKDIST}/..

do-install:
	cd ${WRKSRC} && \
	gcc -fPIC -shared librgba.c -o librgba.so `pkg-config --cflags --libs gtk+-2.0` && \
	cp librgba.so /usr/local/lib/gtk-2.0/modules

.include <bsd.port.mk>
