--- src/notification/notification.c.orig	Thu Apr 21 13:50:44 2011
+++ src/notification/notification.c	Fri Jan  2 14:56:18 2015
@@ -25,6 +25,8 @@
 #include <stdarg.h>
 #include <string.h>
 #include <unistd.h>
+#undef TRUE
+#undef FALSE
 #include <compiz-core.h>
 
 #define NOTIFY_DISPLAY_OPTION_TIMEOUT   0
@@ -104,9 +106,6 @@
     n = notify_notification_new (logLevel,
                                  message,
                                  iconUri
-#if !defined (HAVE_LIBNOTIFY_0_6_1)
-                                 , NULL
-#endif
                                  );
 
     notify_notification_set_timeout (n, nd->timeout);
