--- themer/main.c.orig	Thu Apr 21 14:05:56 2011
+++ themer/main.c	Fri Jan  2 21:57:34 2015
@@ -71,9 +71,9 @@
         elc=emi.last_compat;
         if (!emi.last_compat)
             elc="0.0.0";
-        ostr1 = g_strdup_printf(strverscmp(val2,elc)>=0?
+        ostr1 = g_strdup_printf(strcmp(val2,elc)>=0?
                 "Engine: YES (%s)\n":"Engine: NO (%s)\n",val2);
-        ostr2 = g_strdup_printf(strverscmp(tver,LAST_COMPAT_VER)>=0?
+        ostr2 = g_strdup_printf(strcmp(tver,LAST_COMPAT_VER)>=0?
                 "Emerald: YES (%s)":"Emerald: NO (%s)",tver);
         ostr = g_strdup_printf("%s%s",ostr1,ostr2);
         g_free(ostr1);
@@ -88,7 +88,7 @@
         val = g_key_file_get_string(f,"theme","version",NULL);
         if (!val)
             val=g_strdup("0.0.0");
-        val2 = g_strdup_printf(strverscmp(val,LAST_COMPAT_VER)>=0?
+        val2 = g_strdup_printf(strcmp(val,LAST_COMPAT_VER)>=0?
                 "No Engine\nEmerald: YES (%s)":"No Engine\nEmerald: NO (%s)",val?val:"NONE");
         gtk_list_store_set(ThemeList,&iter,1,val2,-1);
         g_free(val2);
