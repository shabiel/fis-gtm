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
template:	;implement the verb: TEMPLATE
REGION
	i $d(lquals("JOURNAL")),lquals("JOURNAL"),'tmpreg("JOURNAL"),'$d(lquals("BEFORE_IMAGE")) d
	. d message^GDE(gdeerr("QUALREQD"),"""Before_image""")
	i '$$TRQUALS^GDEVERIF(.lquals) d message^GDE(gdeerr("OBJNOTCHG"),"""region"":""template""")
	s update=1,s=""
	f  s s=$o(lquals(s)) q:'$l(s)  s tmpreg(s)=lquals(s) i s="ALLOCATION" s tmpreg("EXTENSION")=lquals(s)\10
	q
SEGMENT
	i $d(lquals("ACCESS_METHOD")) s am=lquals("ACCESS_METHOD")
	e  s am=tmpacc
	i '$$TSQUALS^GDEVERIF(am,.lquals) d message^GDE(gdeerr("OBJNOTCHG"),"""segment"":""template""")
	s update=1,s="",tmpacc=am
	f  s s=$o(lquals(s)) q:'$l(s)  s tmpseg(tmpacc,s)=lquals(s)
	q
