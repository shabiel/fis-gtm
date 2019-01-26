;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;								;
;	Copyright 2001, 2013 Fidelity Information Services, Inc	;
;								;
;	This source code contains the intellectual property	;
;	of its copyright holder(s), and is made available	;
;	under a license.  If you do not know the terms of	;
;	the license, please stop and do not read further.	;
;								;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delete:	;implement the verb: DELETE
NAME
	i '$d(nams(NAME)) d message^GDE(gdeerr("OBJNOTFND"),"""Name"":"_$zwrite($$namedisp^GDESHOW(NAME,0)))
	i NAME="*" d message^GDE(gdeerr("LVSTARALON"),"""""")
	; deleting a name should not cause any new range overlap issues so no need to call "namerangeoverlapcheck" here
	s update=1 k nams(NAME) s nams=nams-1
	q
REGION
	i '$d(regs(REGION)) d message^GDE(gdeerr("OBJNOTFND"),"""Region"":"_$zwrite(REGION))
	s update=1 k regs(REGION) s regs=regs-1
	q
SEGMENT
	i '$d(segs(SEGMENT)) d message^GDE(gdeerr("OBJNOTFND"),"""Segment"":"_$zwrite(SEGMENT))
	s update=1 k segs(SEGMENT) s segs=segs-1
	q
GBLNAME
	i '$d(gnams(GBLNAME)) d message^GDE(gdeerr("OBJNOTFND"),"""Global Name"":"_$zwrite(GBLNAME))
	; check if changing (i.e. deleting) collation for GBLNAME poses issues with existing names & ranges
	i $d(gnams(GBLNAME,"COLLATION")) d
	. d gblnameeditchecks^GDEPARSE(GBLNAME,0)
	. i $d(namrangeoverlap) d namcoalesce^GDEMAP
	s update=1 k gnams(GBLNAME) s gnams=gnams-1
	q
