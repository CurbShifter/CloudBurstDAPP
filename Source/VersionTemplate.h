// SubWCRev
#ifndef __SubWCRev__
#define __SubWCRev__

#define SVNRevisionN $WCREV$
#define SVNRevision "$WCREV$"
#define SVNModified "$WCMODS?Modified:Not modified$"
#define SVNDate     "$WCDATE$"
#define SVNRange    "WCRANGE$"
#define SVNMixed    "$WCMIXED?Mixed revision:Not mixed$"
#define SVNURL      "$WCURL$"

//#if $WCMODS?1:0$
//	#error Source is modified
//#endif

#endif //SubWCRev
