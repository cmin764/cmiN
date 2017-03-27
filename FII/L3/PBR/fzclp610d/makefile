OBJS = agenda.o analysis.o argacces.o bload.o bmathfun.o bsave.o \
 	classcom.o classexm.o classfun.o classinf.o classini.o \
 	classpsr.o clsltpsr.o commline.o conscomp.o constrct.o \
 	constrnt.o crstrtgy.o cstrcbin.o cstrccom.o cstrcpsr.o \
 	cstrnbin.o cstrnchk.o cstrncmp.o cstrnops.o cstrnpsr.o \
 	cstrnutl.o default.o defins.o developr.o dffctbin.o dffctbsc.o \
 	dffctcmp.o dffctdef.o dffctpsr.o dffnxbin.o dffnxcmp.o \
 	dffnxexe.o dffnxfun.o dffnxpsr.o dfinsbin.o dfinscmp.o drive.o \
 	edbasic.o edmain.o edmisc.o edstruct.o edterm.o emathfun.o \
 	engine.o evaluatn.o expressn.o exprnbin.o exprnops.o \
 	exprnpsr.o extnfunc.o factbin.o factbld.o factcmp.o factcom.o \
 	factfun.o factgen.o facthsh.o factlhs.o factmch.o factmngr.o \
 	factprt.o factrete.o factrhs.o filecom.o filertr.o generate.o \
 	genrcbin.o genrccmp.o genrccom.o genrcexe.o genrcfun.o \
 	genrcpsr.o globlbin.o globlbsc.o globlcmp.o globlcom.o \
 	globldef.o globlpsr.o immthpsr.o incrrset.o inherpsr.o \
 	inscom.o insfile.o insfun.o insmngr.o insmoddp.o insmult.o \
 	inspsr.o insquery.o insqypsr.o iofun.o lgcldpnd.o main.o \
 	memalloc.o miscfun.o modulbin.o modulbsc.o modulcmp.o moduldef.o \
 	modulpsr.o modulutl.o msgcom.o msgfun.o msgpass.o msgpsr.o \
 	multifld.o multifun.o objbin.o objcmp.o objrtbin.o objrtbld.o \
 	objrtcmp.o objrtfnx.o objrtgen.o objrtmch.o parsefun.o pattern.o \
 	pprint.o prccode.o prcdrfun.o prcdrpsr.o prdctfun.o prntutil.o \
 	proflfun.o reorder.o reteutil.o retract.o router.o rulebin.o \
 	rulebld.o rulebsc.o rulecmp.o rulecom.o rulecstr.o ruledef.o \
 	ruledlt.o rulelhs.o rulepsr.o scanner.o sortfun.o strngfun.o \
 	strngrtr.o symblbin.o symblcmp.o symbol.o sysdep.o textpro.o \
 	tmpltbin.o tmpltbsc.o tmpltcmp.o tmpltdef.o tmpltfun.o tmpltlhs.o \
 	tmpltpsr.o tmpltrhs.o tmpltutl.o userdata.o utility.o watch.o

.c.o :
	gcc -c -Wall -Wpointer-arith -Wshadow -Wcast-qual \
	    -Wcast-align -Wconversion -Wid-clash-32 -Winline \
	    -Woverloaded-virtual -Wmissing-prototypes -Wconversion \
	    -Wstrict-prototypes -Waggregate-return -Wno-implicit $<

clips : $(OBJS)
	gcc -o clips $(OBJS) -lm -ltermcap   

agenda.o: agenda.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h constrct.h scanner.h pprint.h \
 crstrtgy.h agenda.h ruledef.h constrnt.h cstrccom.h network.h match.h \
 pattern.h reorder.h engine.h extnfunc.h memalloc.h modulutl.h reteutil.h \
 retract.h router.h prntutil.h rulebsc.h strngrtr.h sysdep.h watch.h

analysis.o: analysis.c setup.h constant.h symbol.h memalloc.h \
 exprnpsr.h extnfunc.h expressn.h exprnops.h \
 userdata.h scanner.h pprint.h reorder.h ruledef.h evaluatn.h constrct.h \
 moduldef.h constrnt.h cstrccom.h agenda.h match.h network.h pattern.h \
 generate.h router.h prntutil.h cstrnchk.h cstrnutl.h cstrnops.h \
 rulecstr.h modulutl.h analysis.h globldef.h

argacces.o: argacces.c setup.h extnfunc.h symbol.h \
 expressn.h exprnops.h userdata.h router.h prntutil.h moduldef.h \
 evaluatn.h constant.h constrct.h scanner.h pprint.h cstrnchk.h constrnt.h \
 insfun.h object.h multifld.h match.h network.h ruledef.h cstrccom.h \
 agenda.h pattern.h reorder.h factmngr.h tmpltdef.h factbld.h argacces.h

bload.o: bload.c setup.h memalloc.h exprnpsr.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h scanner.h pprint.h \
 argacces.h evaluatn.h constant.h moduldef.h  constrct.h router.h prntutil.h bsave.h \
 cstrnbin.h constrnt.h utility.h bload.h exprnbin.h sysdep.h symblbin.h

bmathfun.o: bmathfun.c  setup.h \
 exprnpsr.h extnfunc.h symbol.h expressn.h exprnops.h userdata.h scanner.h \
 pprint.h argacces.h evaluatn.h constant.h moduldef.h constrct.h router.h \
 prntutil.h bmathfun.h

bsave.o: bsave.c setup.h memalloc.h exprnpsr.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h scanner.h pprint.h \
 argacces.h evaluatn.h constant.h moduldef.h  constrct.h router.h prntutil.h cstrnbin.h \
 constrnt.h symblbin.h bload.h exprnbin.h sysdep.h bsave.h

classcom.o: classcom.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h argacces.h evaluatn.h \
 constant.h moduldef.h constrct.h scanner.h pprint.h classfun.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h cstrccom.h agenda.h \
 pattern.h reorder.h classini.h modulutl.h msgcom.h router.h prntutil.h \
 classcom.h

classexm.o: classexm.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h \
 scanner.h pprint.h classcom.h cstrccom.h object.h constrnt.h multifld.h \
 match.h network.h ruledef.h agenda.h pattern.h reorder.h classfun.h \
 classini.h memalloc.h insfun.h msgcom.h msgfun.h msgpass.h router.h \
 prntutil.h strngrtr.h classexm.h

classfun.o: classfun.c setup.h bload.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h classcom.h cstrccom.h moduldef.h \
 evaluatn.h constant.h constrct.h scanner.h pprint.h object.h constrnt.h \
 multifld.h match.h network.h ruledef.h agenda.h pattern.h reorder.h \
 classini.h memalloc.h cstrcpsr.h inscom.h insfun.h \
 insmngr.h modulutl.h msgfun.h msgpass.h router.h prntutil.h utility.h \
 classfun.h

classinf.o: classinf.c setup.h argacces.h expressn.h \
 exprnops.h evaluatn.h constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h classcom.h cstrccom.h object.h constrnt.h \
 multifld.h match.h network.h ruledef.h agenda.h pattern.h reorder.h \
 classexm.h classfun.h classini.h memalloc.h insfun.h msgfun.h msgpass.h \
 prntutil.h classinf.h

classini.o: classini.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classexm.h classfun.h classinf.h \
 classpsr.h memalloc.h cstrcpsr.h extnfunc.h \
 inscom.h modulpsr.h modulutl.h msgcom.h watch.h defins.h insquery.h \
 objbin.h objcmp.h objrtbld.h classini.h

classpsr.o: classpsr.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h classcom.h cstrccom.h \
 moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h agenda.h pattern.h \
 reorder.h classfun.h memalloc.h cstrcpsr.h \
 inherpsr.h modulpsr.h modulutl.h msgpsr.h clsltpsr.h router.h prntutil.h \
 classpsr.h

clsltpsr.o: clsltpsr.c setup.h classfun.h object.h \
 constrct.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h scanner.h pprint.h \
 constrnt.h multifld.h match.h network.h ruledef.h cstrccom.h agenda.h \
 pattern.h reorder.h memalloc.h cstrnchk.h cstrnpsr.h cstrnutl.h default.h \
 insfun.h prntutil.h router.h clsltpsr.h

commline.o: commline.c \
 setup.h constant.h symbol.h memalloc.h scanner.h pprint.h exprnpsr.h \
 extnfunc.h expressn.h exprnops.h userdata.h argacces.h evaluatn.h \
 moduldef.h constrct.h router.h prntutil.h strngrtr.h prcdrfun.h \
 prcdrpsr.h constrnt.h utility.h filecom.h cstrcpsr.h commline.h

conscomp.o: conscomp.c setup.h \
 symbol.h memalloc.h constant.h exprnpsr.h extnfunc.h expressn.h \
 exprnops.h userdata.h scanner.h pprint.h cstrccom.h moduldef.h evaluatn.h \
 constrct.h argacces.h cstrncmp.h constrnt.h router.h prntutil.h utility.h \
 modulcmp.h network.h match.h pattern.h reorder.h ruledef.h agenda.h \
 dffnxcmp.h dffnxfun.h tmpltcmp.h globlcmp.h genrccmp.h genrcfun.h \
 object.h multifld.h objcmp.h conscomp.h symblcmp.h

constrct.o: constrct.c \
 setup.h constant.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h evaluatn.h expressn.h exprnops.h userdata.h \
 constrct.h scanner.h pprint.h watch.h prcdrfun.h prcdrpsr.h constrnt.h \
 argacces.h exprnpsr.h extnfunc.h multifld.h utility.h commline.h

constrnt.o: constrnt.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h extnfunc.h multifld.h constrnt.h \
 argacces.h

crstrtgy.o: crstrtgy.c setup.h constant.h pattern.h evaluatn.h symbol.h \
 expressn.h exprnops.h userdata.h scanner.h pprint.h match.h network.h \
 ruledef.h constrct.h moduldef.h constrnt.h cstrccom.h agenda.h reorder.h \
 reteutil.h argacces.h crstrtgy.h

cstrcbin.o: cstrcbin.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h bsave.h moduldef.h \
 evaluatn.h constant.h constrct.h scanner.h pprint.h cstrcbin.h

cstrccom.o: cstrccom.c \
 setup.h constant.h memalloc.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 argacces.h multifld.h modulutl.h router.h prntutil.h utility.h commline.h \
 bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h cstrcpsr.h cstrccom.h

cstrcpsr.o: cstrcpsr.c setup.h router.h prntutil.h \
 moduldef.h symbol.h evaluatn.h constant.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h watch.h prcdrpsr.h constrnt.h \
 exprnpsr.h extnfunc.h modulutl.h modulpsr.h utility.h cstrcpsr.h

cstrnbin.o: cstrnbin.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h bsave.h cstrnbin.h \
 constrnt.h

cstrnchk.o: cstrnchk.c setup.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h multifld.h extnfunc.h cstrnutl.h constrnt.h cstrnchk.h

cstrncmp.o: cstrncmp.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 conscomp.h extnfunc.h symblcmp.h cstrncmp.h constrnt.h

cstrnops.o: cstrnops.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h \
 expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h extnfunc.h \
 multifld.h constrnt.h cstrnchk.h cstrnutl.h cstrnops.h

cstrnpsr.o: cstrnpsr.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h cstrnutl.h constrnt.h cstrnchk.h \
 cstrnpsr.h

cstrnutl.o: cstrnutl.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h extnfunc.h multifld.h argacces.h \
 cstrnutl.h constrnt.h

default.o: default.c setup.h constant.h constrnt.h \
 evaluatn.h symbol.h expressn.h exprnops.h userdata.h cstrnchk.h \
 multifld.h inscom.h object.h constrct.h moduldef.h scanner.h pprint.h \
 match.h network.h ruledef.h cstrccom.h agenda.h pattern.h reorder.h \
 exprnpsr.h extnfunc.h router.h prntutil.h factmngr.h tmpltdef.h factbld.h \
 cstrnutl.h default.h

defins.o: defins.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h dfinsbin.h dfinscmp.h \
 argacces.h evaluatn.h constant.h moduldef.h constrct.h scanner.h pprint.h \
 classcom.h cstrccom.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h memalloc.h \
 cstrcpsr.h insfun.h inspsr.h modulpsr.h router.h \
 prntutil.h utility.h defins.h

developr.o: developr.c setup.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h argacces.h extnfunc.h \
 modulutl.h tmpltdef.h constrnt.h factbld.h pattern.h match.h network.h \
 ruledef.h cstrccom.h agenda.h reorder.h factmngr.h multifld.h facthsh.h \
 classcom.h object.h classfun.h objrtmch.h developr.h

dffctbin.o: dffctbin.c setup.h memalloc.h dffctdef.h \
 symbol.h expressn.h exprnops.h evaluatn.h constant.h userdata.h \
 constrct.h moduldef.h scanner.h pprint.h cstrccom.h bload.h extnfunc.h \
 exprnbin.h sysdep.h symblbin.h bsave.h dffctbin.h modulbin.h cstrcbin.h

dffctbsc.o: dffctbsc.c setup.h argacces.h expressn.h \
 exprnops.h evaluatn.h constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h memalloc.h router.h prntutil.h extnfunc.h \
 cstrccom.h factrhs.h factmngr.h pattern.h match.h network.h ruledef.h \
 constrnt.h agenda.h reorder.h multifld.h tmpltdef.h factbld.h cstrcpsr.h \
 dffctpsr.h dffctdef.h dffctbin.h modulbin.h cstrcbin.h dffctcmp.h \
 dffctbsc.h

dffctcmp.o: dffctcmp.c setup.h conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h moduldef.h evaluatn.h constant.h \
 constrct.h scanner.h pprint.h dffctdef.h cstrccom.h dffctcmp.h

dffctdef.o: dffctdef.c setup.h memalloc.h dffctpsr.h \
 dffctbsc.h evaluatn.h constant.h symbol.h expressn.h exprnops.h \
 userdata.h bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h dffctbin.h \
 modulbin.h moduldef.h constrct.h scanner.h pprint.h cstrcbin.h dffctcmp.h \
 dffctdef.h cstrccom.h

dffctpsr.o: dffctpsr.c setup.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h cstrcpsr.h factrhs.h factmngr.h pattern.h match.h \
 network.h ruledef.h constrnt.h cstrccom.h agenda.h reorder.h multifld.h \
 tmpltdef.h factbld.h bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h \
 dffctdef.h dffctbsc.h dffctpsr.h

dffnxbin.o: dffnxbin.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h bsave.h memalloc.h \
 cstrcbin.h constrct.h moduldef.h evaluatn.h \
 constant.h scanner.h pprint.h modulbin.h dffnxbin.h dffnxfun.h cstrccom.h

dffnxcmp.o: dffnxcmp.c setup.h conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h \
 moduldef.h evaluatn.h constant.h constrct.h \
 scanner.h pprint.h dffnxcmp.h dffnxfun.h cstrccom.h

dffnxexe.o: dffnxexe.c setup.h \
 constrct.h moduldef.h symbol.h evaluatn.h \
 constant.h expressn.h exprnops.h userdata.h scanner.h pprint.h prcdrfun.h \
 prccode.h proflfun.h router.h prntutil.h utility.h watch.h dffnxexe.h \
 dffnxfun.h cstrccom.h

dffnxfun.o: dffnxfun.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h dffnxbin.h dffnxfun.h \
 cstrccom.h moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h \
 dffnxcmp.h cstrcpsr.h dffnxpsr.h modulpsr.h dffnxexe.h watch.h argacces.h \
 memalloc.h router.h prntutil.h

dffnxpsr.o: dffnxpsr.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h network.h match.h \
 evaluatn.h constant.h pattern.h scanner.h pprint.h reorder.h ruledef.h \
 constrct.h moduldef.h constrnt.h cstrccom.h agenda.h genrccom.h \
 genrcfun.h object.h multifld.h memalloc.h \
 cstrcpsr.h dffnxfun.h exprnpsr.h prccode.h router.h prntutil.h dffnxpsr.h

dfinsbin.o: dfinsbin.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h bsave.h memalloc.h \
 cstrcbin.h constrct.h moduldef.h evaluatn.h \
 constant.h scanner.h pprint.h defins.h cstrccom.h object.h constrnt.h \
 multifld.h match.h network.h ruledef.h agenda.h pattern.h reorder.h \
 modulbin.h dfinsbin.h

dfinscmp.o: dfinscmp.c setup.h conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h \
 moduldef.h evaluatn.h constant.h constrct.h \
 scanner.h pprint.h defins.h cstrccom.h object.h constrnt.h multifld.h \
 match.h network.h ruledef.h agenda.h pattern.h reorder.h dfinscmp.h

drive.o: drive.c setup.h constant.h memalloc.h \
 reteutil.h evaluatn.h symbol.h expressn.h exprnops.h userdata.h match.h \
 network.h ruledef.h constrct.h moduldef.h scanner.h pprint.h constrnt.h \
 cstrccom.h agenda.h pattern.h reorder.h prntutil.h router.h retract.h \
 lgcldpnd.h incrrset.h drive.h

edbasic.o: edbasic.c setup.h ed.h \
 argacces.h expressn.h exprnops.h evaluatn.h constant.h symbol.h \
 userdata.h moduldef.h constrct.h scanner.h pprint.h memalloc.h router.h \
 prntutil.h
 
edmain.o: edmain.c setup.h ed.h \
 argacces.h expressn.h exprnops.h evaluatn.h constant.h symbol.h \
 userdata.h moduldef.h constrct.h scanner.h pprint.h memalloc.h router.h \
 prntutil.h sysdep.h extnfunc.h

edmisc.o: edmisc.c setup.h ed.h \
 argacces.h expressn.h exprnops.h evaluatn.h constant.h symbol.h \
 userdata.h moduldef.h constrct.h scanner.h pprint.h memalloc.h router.h \
 prntutil.h cstrcpsr.h 

edstruct.o: edstruct.c setup.h ed.h \
 argacces.h expressn.h exprnops.h evaluatn.h constant.h symbol.h \
 userdata.h moduldef.h constrct.h scanner.h pprint.h memalloc.h router.h \
 prntutil.h 

edterm.o: edterm.c setup.h ed.h \
 argacces.h expressn.h exprnops.h evaluatn.h constant.h symbol.h \
 userdata.h moduldef.h constrct.h scanner.h pprint.h memalloc.h router.h \
 prntutil.h

emathfun.o: emathfun.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h extnfunc.h \
 router.h prntutil.h emathfun.h 

engine.o: engine.c \
 setup.h agenda.h ruledef.h symbol.h expressn.h \
 exprnops.h evaluatn.h constant.h userdata.h constrct.h moduldef.h \
 scanner.h pprint.h constrnt.h cstrccom.h network.h match.h pattern.h \
 reorder.h argacces.h factmngr.h multifld.h tmpltdef.h factbld.h inscom.h \
 object.h memalloc.h modulutl.h prccode.h prcdrfun.h proflfun.h reteutil.h \
 retract.h router.h prntutil.h ruledlt.h sysdep.h utility.h watch.h \
 engine.h

evaluatn.o: evaluatn.c setup.h commline.h constant.h memalloc.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h extnfunc.h prcdrfun.h multifld.h \
 factmngr.h pattern.h match.h network.h ruledef.h constrnt.h cstrccom.h \
 agenda.h reorder.h tmpltdef.h factbld.h exprnpsr.h utility.h proflfun.h \
 sysdep.h dffnxfun.h genrccom.h genrcfun.h object.h

expressn.o: expressn.c setup.h memalloc.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h extnfunc.h

exprnbin.o: exprnbin.c setup.h memalloc.h dffctdef.h \
 symbol.h expressn.h exprnops.h evaluatn.h constant.h userdata.h \
 constrct.h moduldef.h scanner.h pprint.h cstrccom.h extnfunc.h bload.h \
 exprnbin.h sysdep.h symblbin.h bsave.h network.h match.h pattern.h \
 reorder.h ruledef.h constrnt.h agenda.h genrcbin.h genrcfun.h object.h \
 multifld.h dffnxbin.h dffnxfun.h tmpltbin.h cstrcbin.h modulbin.h \
 tmpltdef.h factbld.h factmngr.h globlbin.h globldef.h objbin.h insfun.h \
 inscom.h

exprnops.o: exprnops.c setup.h  memalloc.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h extnfunc.h cstrnchk.h \
 constrnt.h cstrnutl.h cstrnops.h

exprnpsr.o: exprnpsr.c setup.h constant.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h strngrtr.h memalloc.h argacces.h \
 cstrnchk.h constrnt.h extnfunc.h exprnpsr.h modulutl.h prcdrfun.h \
 network.h match.h pattern.h reorder.h ruledef.h cstrccom.h agenda.h \
 genrccom.h genrcfun.h object.h multifld.h dffnxfun.h

extnfunc.o: extnfunc.c setup.h \
 constant.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 memalloc.h extnfunc.h

factbin.o: factbin.c setup.h memalloc.h \
 tmpltdef.h symbol.h expressn.h exprnops.h \
 evaluatn.h constant.h userdata.h constrct.h moduldef.h scanner.h pprint.h \
 constrnt.h factbld.h pattern.h match.h network.h ruledef.h cstrccom.h \
 agenda.h reorder.h factmngr.h multifld.h bload.h extnfunc.h exprnbin.h \
 sysdep.h symblbin.h bsave.h rulebin.h modulbin.h cstrcbin.h factbin.h

factbld.o: factbld.c setup.h memalloc.h \
 reteutil.h evaluatn.h constant.h symbol.h \
 expressn.h exprnops.h userdata.h match.h network.h ruledef.h constrct.h \
 moduldef.h scanner.h pprint.h constrnt.h cstrccom.h agenda.h pattern.h \
 reorder.h router.h prntutil.h factcmp.h factmch.h factmngr.h multifld.h \
 tmpltdef.h factbld.h factgen.h factlhs.h argacces.h modulutl.h

factcmp.o: factcmp.c setup.h factbld.h \
 pattern.h evaluatn.h constant.h symbol.h expressn.h exprnops.h userdata.h \
 scanner.h pprint.h match.h network.h ruledef.h constrct.h moduldef.h \
 constrnt.h cstrccom.h agenda.h reorder.h conscomp.h extnfunc.h symblcmp.h \
 factcmp.h tmpltdef.h factmngr.h multifld.h

factcom.o: factcom.c setup.h memalloc.h exprnpsr.h extnfunc.h symbol.h \
 expressn.h exprnops.h userdata.h scanner.h pprint.h factmngr.h pattern.h \
 evaluatn.h constant.h match.h network.h ruledef.h constrct.h moduldef.h \
 constrnt.h cstrccom.h agenda.h reorder.h multifld.h tmpltdef.h factbld.h \
 argacces.h router.h prntutil.h factrhs.h factmch.h tmpltpsr.h tmpltutl.h \
 facthsh.h modulutl.h strngrtr.h tmpltfun.h bload.h exprnbin.h sysdep.h \
 symblbin.h factcom.h

factfun.o: factfun.c setup.h extnfunc.h symbol.h expressn.h exprnops.h \
 userdata.h argacces.h evaluatn.h constant.h moduldef.h constrct.h \
 scanner.h pprint.h prntutil.h tmpltutl.h factmngr.h pattern.h match.h \
 network.h ruledef.h constrnt.h cstrccom.h agenda.h reorder.h multifld.h \
 tmpltdef.h factbld.h factfun.h

factgen.o: factgen.c setup.h constant.h \
 memalloc.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 exprnpsr.h extnfunc.h network.h match.h pattern.h reorder.h ruledef.h \
 constrnt.h cstrccom.h agenda.h reteutil.h factmch.h factmngr.h multifld.h \
 tmpltdef.h factbld.h factrete.h factprt.h tmpltlhs.h factgen.h

facthsh.o: facthsh.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h lgcldpnd.h match.h network.h \
 ruledef.h constrnt.h cstrccom.h agenda.h pattern.h reorder.h facthsh.h \
 factmngr.h multifld.h tmpltdef.h factbld.h

factlhs.o: factlhs.c setup.h router.h \
 prntutil.h moduldef.h symbol.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h reorder.h ruledef.h \
 constrnt.h cstrccom.h agenda.h match.h network.h pattern.h tmpltpsr.h \
 tmpltdef.h factbld.h factmngr.h multifld.h tmpltlhs.h tmpltutl.h \
 modulutl.h modulpsr.h cstrcpsr.h factlhs.h

factmch.o: factmch.c setup.h \
 memalloc.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h router.h prntutil.h moduldef.h evaluatn.h \
 constant.h constrct.h scanner.h pprint.h incrrset.h ruledef.h constrnt.h \
 cstrccom.h agenda.h match.h network.h pattern.h reorder.h reteutil.h \
 drive.h factgen.h factrete.h tmpltdef.h factbld.h factmngr.h multifld.h \
 factmch.h

factmngr.o: factmngr.c setup.h constant.h symbol.h memalloc.h exprnpsr.h \
 extnfunc.h expressn.h exprnops.h userdata.h scanner.h pprint.h argacces.h \
 evaluatn.h moduldef.h constrct.h router.h prntutil.h strngrtr.h match.h \
 network.h ruledef.h constrnt.h cstrccom.h agenda.h pattern.h reorder.h \
 factbld.h reteutil.h retract.h filecom.h factfun.h factmngr.h multifld.h \
 tmpltdef.h factrhs.h factmch.h watch.h utility.h factbin.h facthsh.h \
 default.h commline.h engine.h lgcldpnd.h drive.h ruledlt.h tmpltbsc.h \
 tmpltutl.h tmpltfun.h

factprt.o: factprt.c setup.h symbol.h \
 router.h prntutil.h moduldef.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h factgen.h reorder.h \
 ruledef.h constrnt.h cstrccom.h agenda.h match.h network.h pattern.h \
 factprt.h

factrete.o: factrete.c setup.h \
 memalloc.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h router.h prntutil.h moduldef.h evaluatn.h \
 constant.h constrct.h scanner.h pprint.h incrrset.h ruledef.h constrnt.h \
 cstrccom.h agenda.h match.h network.h pattern.h reorder.h reteutil.h \
 drive.h factgen.h factmch.h factmngr.h multifld.h tmpltdef.h factbld.h \
 factrete.h

factrhs.o: factrhs.c \
 setup.h constant.h prntutil.h moduldef.h symbol.h \
 evaluatn.h expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h \
 extnfunc.h pattern.h match.h network.h ruledef.h constrnt.h cstrccom.h \
 agenda.h reorder.h modulutl.h modulpsr.h cstrcpsr.h bload.h exprnbin.h \
 sysdep.h symblbin.h tmpltpsr.h tmpltdef.h factbld.h factmngr.h multifld.h \
 tmpltrhs.h tmpltutl.h exprnpsr.h strngrtr.h router.h factrhs.h

filecom.o: filecom.c setup.h memalloc.h argacces.h expressn.h exprnops.h \
 evaluatn.h constant.h symbol.h userdata.h moduldef.h constrct.h scanner.h \
 pprint.h router.h prntutil.h strngrtr.h extnfunc.h cstrcpsr.h utility.h \
 commline.h prcdrfun.h filecom.h bsave.h bload.h exprnbin.h sysdep.h \
 symblbin.h

filertr.o: filertr.c setup.h constant.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h evaluatn.h expressn.h exprnops.h userdata.h \
 constrct.h scanner.h pprint.h filertr.h

generate.o: generate.c setup.h constant.h memalloc.h \
 symbol.h exprnpsr.h extnfunc.h expressn.h exprnops.h userdata.h scanner.h \
 pprint.h argacces.h evaluatn.h moduldef.h constrct.h router.h prntutil.h \
 ruledef.h constrnt.h cstrccom.h agenda.h match.h network.h pattern.h \
 reorder.h generate.h globlpsr.h

genrcbin.o: genrcbin.c setup.h constant.h memalloc.h bload.h extnfunc.h \
 symbol.h expressn.h exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h bsave.h cstrcbin.h \
 constrct.h moduldef.h evaluatn.h scanner.h pprint.h objbin.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h cstrccom.h agenda.h \
 pattern.h reorder.h genrccom.h genrcfun.h modulbin.h genrcbin.h router.h \
 prntutil.h

genrccmp.o: genrccmp.c setup.h network.h match.h evaluatn.h constant.h \
 symbol.h expressn.h exprnops.h userdata.h pattern.h \
 scanner.h pprint.h reorder.h ruledef.h \
 constrct.h moduldef.h constrnt.h cstrccom.h agenda.h genrccom.h \
 genrcfun.h object.h multifld.h conscomp.h extnfunc.h symblcmp.h objcmp.h \
 genrccmp.h

genrccom.o: genrccom.c setup.h network.h match.h \
 evaluatn.h constant.h symbol.h expressn.h exprnops.h userdata.h pattern.h scanner.h \
 pprint.h reorder.h ruledef.h constrct.h moduldef.h constrnt.h cstrccom.h \
 agenda.h bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h genrcbin.h \
 genrcfun.h object.h multifld.h genrccmp.h genrcpsr.h classcom.h inscom.h \
 watch.h argacces.h memalloc.h cstrcpsr.h genrcexe.h modulpsr.h router.h \
 prntutil.h genrccom.h

genrcexe.o: genrcexe.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h insfun.h argacces.h \
 genrccom.h genrcfun.h prcdrfun.h prccode.h proflfun.h router.h prntutil.h \
 utility.h genrcexe.h

genrcfun.o: genrcfun.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h classcom.h cstrccom.h \
 moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h agenda.h pattern.h \
 reorder.h classfun.h argacces.h memalloc.h \
 cstrcpsr.h genrccom.h genrcfun.h genrcexe.h prccode.h router.h prntutil.h

genrcpsr.o: genrcpsr.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h dffnxfun.h cstrccom.h \
 moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h classfun.h \
 object.h constrnt.h multifld.h match.h network.h ruledef.h agenda.h \
 pattern.h reorder.h classcom.h memalloc.h \
 cstrcpsr.h exprnpsr.h genrccom.h genrcfun.h immthpsr.h modulutl.h \
 prcdrpsr.h prccode.h router.h prntutil.h genrcpsr.h

globlbin.o: globlbin.c setup.h memalloc.h multifld.h \
 evaluatn.h constant.h symbol.h expressn.h exprnops.h userdata.h \
 globldef.h constrct.h moduldef.h scanner.h pprint.h cstrccom.h bload.h \
 extnfunc.h exprnbin.h sysdep.h symblbin.h bsave.h globlbsc.h globlbin.h \
 modulbin.h cstrcbin.h

globlbsc.o: globlbsc.c setup.h constrct.h moduldef.h \
 symbol.h evaluatn.h constant.h expressn.h \
 exprnops.h userdata.h scanner.h pprint.h extnfunc.h watch.h globlcom.h \
 globldef.h cstrccom.h globlbin.h modulbin.h cstrcbin.h globlcmp.h \
 globlbsc.h

globlcmp.o: globlcmp.c setup.h conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h moduldef.h evaluatn.h constant.h \
 constrct.h scanner.h pprint.h globldef.h cstrccom.h globlcmp.h

globlcom.o: globlcom.c setup.h extnfunc.h symbol.h expressn.h exprnops.h \
 userdata.h argacces.h evaluatn.h constant.h moduldef.h constrct.h \
 scanner.h pprint.h prntutil.h router.h globldef.h cstrccom.h globlcom.h

globldef.o: globldef.c setup.h memalloc.h modulpsr.h \
 symbol.h evaluatn.h constant.h expressn.h exprnops.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h multifld.h router.h prntutil.h \
 strngrtr.h modulutl.h globlbsc.h globlpsr.h globlcom.h utility.h \
 commline.h bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h globlbin.h \
 modulbin.h cstrcbin.h globldef.h cstrccom.h globlcmp.h

globlpsr.o: globlpsr.c setup.h pprint.h router.h \
 prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h memalloc.h exprnpsr.h extnfunc.h multifld.h watch.h modulutl.h \
 modulpsr.h cstrcpsr.h globldef.h cstrccom.h globlbsc.h bload.h exprnbin.h \
 sysdep.h symblbin.h globlpsr.h

immthpsr.o: immthpsr.c setup.h classcom.h cstrccom.h moduldef.h \
 symbol.h evaluatn.h constant.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h object.h constrnt.h multifld.h \
 match.h network.h ruledef.h agenda.h pattern.h reorder.h classfun.h \
 memalloc.h cstrnutl.h extnfunc.h genrcpsr.h \
 genrcfun.h prccode.h immthpsr.h

incrrset.o: incrrset.c setup.h \
 constant.h agenda.h ruledef.h symbol.h \
 expressn.h exprnops.h evaluatn.h userdata.h constrct.h moduldef.h \
 scanner.h pprint.h constrnt.h cstrccom.h network.h match.h pattern.h \
 reorder.h router.h prntutil.h drive.h argacces.h incrrset.h

inherpsr.o: inherpsr.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h memalloc.h \
 modulutl.h router.h prntutil.h inherpsr.h

inscom.o: inscom.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h classcom.h \
 cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 agenda.h pattern.h reorder.h classfun.h classinf.h memalloc.h \
 exprnpsr.h extnfunc.h insfile.h insfun.h insmngr.h \
 insmoddp.h insmult.h inspsr.h msgfun.h msgpass.h router.h prntutil.h \
 strngrtr.h utility.h commline.h inscom.h

insfile.o: insfile.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h classcom.h \
 cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 agenda.h pattern.h reorder.h classfun.h memalloc.h \
 extnfunc.h inscom.h insfun.h insmngr.h inspsr.h router.h prntutil.h \
 strngrtr.h symblbin.h sysdep.h factmngr.h tmpltdef.h factbld.h insfile.h

insfun.o: insfun.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h classcom.h \
 cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 agenda.h pattern.h reorder.h classfun.h memalloc.h \
 cstrnchk.h inscom.h insmngr.h modulutl.h msgfun.h msgpass.h prccode.h \
 router.h prntutil.h utility.h drive.h objrtmch.h insfun.h

insmngr.o: insmngr.c setup.h network.h match.h evaluatn.h constant.h \
 symbol.h expressn.h exprnops.h userdata.h pattern.h \
 scanner.h pprint.h reorder.h ruledef.h \
 constrct.h moduldef.h constrnt.h cstrccom.h agenda.h drive.h objrtmch.h \
 object.h multifld.h lgcldpnd.h classcom.h classfun.h memalloc.h \
 extnfunc.h insfun.h modulutl.h msgfun.h msgpass.h \
 prccode.h router.h prntutil.h utility.h insmngr.h inscom.h

insmoddp.o: insmoddp.c setup.h network.h match.h evaluatn.h constant.h \
 symbol.h expressn.h exprnops.h userdata.h pattern.h \
 scanner.h pprint.h reorder.h ruledef.h \
 constrct.h moduldef.h constrnt.h cstrccom.h agenda.h objrtmch.h object.h \
 multifld.h argacces.h memalloc.h extnfunc.h \
 insfun.h insmngr.h inspsr.h msgfun.h msgpass.h prccode.h router.h \
 prntutil.h insmoddp.h

insmult.o: insmult.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h extnfunc.h \
 insfun.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 cstrccom.h agenda.h pattern.h reorder.h msgfun.h msgpass.h multifun.h \
 router.h prntutil.h insmult.h

inspsr.o: inspsr.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h classinf.h exprnpsr.h \
 extnfunc.h prntutil.h router.h inspsr.h

insquery.o: insquery.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h classcom.h \
 cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 agenda.h pattern.h reorder.h classfun.h memalloc.h \
 exprnpsr.h extnfunc.h insfun.h insmngr.h insqypsr.h prcdrfun.h router.h \
 prntutil.h utility.h insquery.h

insqypsr.o: insqypsr.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h exprnpsr.h extnfunc.h insquery.h \
 prcdrpsr.h prntutil.h router.h strngrtr.h insqypsr.h

iofun.o: iofun.c setup.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h strngrtr.h filertr.h argacces.h extnfunc.h memalloc.h \
 commline.h sysdep.h utility.h iofun.h
 
lgcldpnd.o: lgcldpnd.c setup.h \
 memalloc.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h engine.h ruledef.h constrnt.h cstrccom.h agenda.h \
 match.h network.h pattern.h reorder.h reteutil.h argacces.h factmngr.h \
 multifld.h tmpltdef.h factbld.h insfun.h object.h lgcldpnd.h

main.o: main.c setup.h sysdep.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h commline.h

memalloc.o: memalloc.c setup.h \
 constant.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h evaluatn.h expressn.h exprnops.h userdata.h \
 constrct.h scanner.h pprint.h utility.h 

miscfun.o: miscfun.c \
 setup.h memalloc.h sysdep.h multifld.h evaluatn.h \
 constant.h symbol.h expressn.h exprnops.h userdata.h exprnpsr.h \
 extnfunc.h scanner.h pprint.h argacces.h moduldef.h constrct.h router.h \
 prntutil.h utility.h dffnxfun.h cstrccom.h miscfun.h

modulbin.o: modulbin.c setup.h memalloc.h constrct.h \
 moduldef.h symbol.h evaluatn.h constant.h expressn.h exprnops.h \
 userdata.h scanner.h pprint.h bload.h extnfunc.h exprnbin.h sysdep.h \
 symblbin.h bsave.h modulbin.h

modulbsc.o: modulbsc.c setup.h  constrct.h moduldef.h \
 symbol.h evaluatn.h constant.h expressn.h exprnops.h userdata.h scanner.h \
 pprint.h extnfunc.h modulbin.h prntutil.h modulcmp.h router.h argacces.h \
 bload.h exprnbin.h sysdep.h symblbin.h modulbsc.h

modulcmp.o: modulcmp.c setup.h \
 conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h moduldef.h evaluatn.h constant.h \
 constrct.h scanner.h pprint.h modulcmp.h

moduldef.o: moduldef.c setup.h memalloc.h constant.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h extnfunc.h argacces.h modulpsr.h \
 modulcmp.h modulbsc.h utility.h bload.h exprnbin.h sysdep.h symblbin.h \
 modulbin.h

modulpsr.o: modulpsr.c setup.h memalloc.h constant.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h extnfunc.h argacces.h cstrcpsr.h \
 modulutl.h utility.h bload.h exprnbin.h sysdep.h symblbin.h modulpsr.h

modulutl.o: modulutl.c setup.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h modulpsr.h modulutl.h

msgcom.o: msgcom.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h \
 scanner.h pprint.h classcom.h cstrccom.h object.h constrnt.h multifld.h \
 match.h network.h ruledef.h agenda.h pattern.h reorder.h classfun.h \
 classinf.h insfun.h insmoddp.h msgfun.h msgpass.h prccode.h router.h \
 prntutil.h bload.h extnfunc.h exprnbin.h sysdep.h symblbin.h msgpsr.h \
 watch.h msgcom.h

msgfun.o: msgfun.c setup.h classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h memalloc.h \
 extnfunc.h insfun.h prccode.h router.h prntutil.h \
 msgfun.h msgpass.h

msgpass.o: msgpass.c setup.h \
 argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h constrct.h scanner.h pprint.h \
 classcom.h cstrccom.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h memalloc.h \
 exprnpsr.h extnfunc.h insfun.h msgfun.h msgpass.h \
 prcdrfun.h prccode.h proflfun.h router.h prntutil.h utility.h commline.h \
 inscom.h

msgpsr.o: msgpsr.c setup.h bload.h extnfunc.h \
 symbol.h expressn.h exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h classcom.h cstrccom.h \
 moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h agenda.h pattern.h \
 reorder.h classfun.h memalloc.h cstrcpsr.h cstrnchk.h exprnpsr.h insfun.h \
 msgfun.h msgpass.h prccode.h router.h prntutil.h strngrtr.h msgpsr.h

multifld.o: multifld.c setup.h \
 constant.h memalloc.h evaluatn.h symbol.h \
 expressn.h exprnops.h userdata.h scanner.h pprint.h router.h prntutil.h \
 moduldef.h constrct.h strngrtr.h utility.h multifld.h

multifun.o: multifun.c setup.h memalloc.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h multifld.h router.h prntutil.h \
 multifun.h exprnpsr.h extnfunc.h prcdrpsr.h constrnt.h prcdrfun.h \
 utility.h object.h match.h network.h ruledef.h cstrccom.h agenda.h \
 pattern.h reorder.h

objbin.o: objbin.c setup.h bload.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h bsave.h classcom.h cstrccom.h \
 moduldef.h evaluatn.h constant.h constrct.h scanner.h pprint.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h agenda.h pattern.h \
 reorder.h classfun.h classini.h memalloc.h \
 cstrcbin.h cstrnbin.h insfun.h modulbin.h msgfun.h msgpass.h prntutil.h \
 router.h objbin.h

objcmp.o: objcmp.c setup.h conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h \
 moduldef.h evaluatn.h constant.h constrct.h \
 scanner.h pprint.h classcom.h cstrccom.h object.h constrnt.h multifld.h \
 match.h network.h ruledef.h agenda.h pattern.h reorder.h classfun.h \
 classini.h cstrncmp.h objcmp.h

objrtbin.o: objrtbin.c setup.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h \
 sysdep.h symblbin.h bsave.h memalloc.h \
 insfun.h evaluatn.h constant.h moduldef.h \
 constrct.h scanner.h pprint.h object.h constrnt.h multifld.h match.h \
 network.h ruledef.h cstrccom.h agenda.h pattern.h reorder.h objrtmch.h \
 rulebin.h modulbin.h cstrcbin.h objrtbin.h

objrtbld.o: objrtbld.c setup.h classcom.h \
 cstrccom.h moduldef.h symbol.h evaluatn.h constant.h \
 expressn.h exprnops.h userdata.h constrct.h scanner.h pprint.h object.h \
 constrnt.h multifld.h match.h network.h ruledef.h agenda.h pattern.h \
 reorder.h classfun.h memalloc.h cstrnutl.h cstrnchk.h cstrnops.h drive.h \
 exprnpsr.h extnfunc.h insfun.h insmngr.h reteutil.h rulepsr.h utility.h \
 objrtmch.h objrtgen.h objrtfnx.h router.h prntutil.h objrtcmp.h \
 objrtbin.h objrtbld.h

objrtcmp.o: objrtcmp.c setup.h \
 conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h moduldef.h evaluatn.h constant.h \
 constrct.h scanner.h pprint.h objrtmch.h match.h network.h ruledef.h \
 constrnt.h cstrccom.h agenda.h pattern.h reorder.h object.h multifld.h \
 objrtcmp.h

objrtfnx.o: objrtfnx.c setup.h \
 classcom.h cstrccom.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h object.h constrnt.h multifld.h match.h network.h \
 ruledef.h agenda.h pattern.h reorder.h classfun.h drive.h objrtmch.h \
 reteutil.h router.h prntutil.h objrtfnx.h

objrtgen.o: objrtgen.c setup.h \
 classfun.h object.h constrct.h moduldef.h \
 symbol.h evaluatn.h constant.h expressn.h exprnops.h userdata.h scanner.h \
 pprint.h constrnt.h multifld.h match.h network.h ruledef.h cstrccom.h \
 agenda.h pattern.h reorder.h objrtfnx.h objrtgen.h

objrtmch.o: objrtmch.c setup.h classfun.h object.h constrct.h moduldef.h \
 symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h scanner.h pprint.h \
 constrnt.h multifld.h match.h network.h ruledef.h cstrccom.h agenda.h \
 pattern.h reorder.h memalloc.h drive.h lgcldpnd.h \
 incrrset.h reteutil.h ruledlt.h retract.h router.h prntutil.h objrtfnx.h \
 objrtmch.h insmngr.h

parsefun.o: parsefun.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h \
 scanner.h pprint.h cstrcpsr.h exprnpsr.h extnfunc.h memalloc.h multifld.h \
 prcdrpsr.h constrnt.h router.h prntutil.h strngrtr.h utility.h parsefun.h

pattern.o: pattern.c setup.h \
 constant.h memalloc.h match.h \
 evaluatn.h symbol.h expressn.h exprnops.h userdata.h network.h ruledef.h \
 constrct.h moduldef.h scanner.h pprint.h constrnt.h cstrccom.h agenda.h \
 pattern.h reorder.h reteutil.h exprnpsr.h extnfunc.h router.h prntutil.h \
 cstrnchk.h cstrnutl.h rulecmp.h conscomp.h symblcmp.h

pprint.o: pprint.c setup.h constant.h memalloc.h utility.h pprint.h

prccode.o: prccode.c setup.h memalloc.h constant.h globlpsr.h expressn.h \
 exprnops.h exprnpsr.h extnfunc.h symbol.h userdata.h scanner.h pprint.h \
 multifld.h evaluatn.h object.h constrct.h moduldef.h constrnt.h match.h \
 network.h ruledef.h cstrccom.h agenda.h pattern.h reorder.h prcdrpsr.h \
 router.h prntutil.h utility.h prccode.h

prcdrfun.o: prcdrfun.c setup.h \
 memalloc.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h argacces.h constrnt.h cstrnchk.h cstrnops.h multifld.h \
 exprnpsr.h extnfunc.h utility.h prcdrpsr.h prcdrfun.h globldef.h \
 cstrccom.h

prcdrpsr.o: prcdrpsr.c setup.h \
 memalloc.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h argacces.h constrnt.h cstrnchk.h cstrnops.h multifld.h \
 exprnpsr.h extnfunc.h utility.h modulutl.h cstrnutl.h prcdrpsr.h \
 globldef.h cstrccom.h globlpsr.h

prdctfun.o: prdctfun.c setup.h \
 exprnpsr.h extnfunc.h symbol.h expressn.h exprnops.h userdata.h scanner.h \
 pprint.h argacces.h evaluatn.h constant.h moduldef.h constrct.h \
 multifld.h router.h prntutil.h prdctfun.h

prntutil.o: prntutil.c \
 setup.h constant.h symbol.h utility.h evaluatn.h \
 expressn.h exprnops.h userdata.h argacces.h moduldef.h constrct.h \
 scanner.h pprint.h router.h prntutil.h

proflfun.o: proflfun.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h classcom.h \
 cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h \
 agenda.h pattern.h reorder.h dffnxfun.h extnfunc.h extobj.h genrccom.h \
 genrcfun.h memalloc.h msgcom.h router.h prntutil.h \
 sysdep.h proflfun.h

reorder.o: reorder.c setup.h memalloc.h \
 cstrnutl.h constrnt.h evaluatn.h constant.h \
 symbol.h expressn.h exprnops.h userdata.h pattern.h scanner.h pprint.h \
 match.h network.h ruledef.h constrct.h moduldef.h cstrccom.h agenda.h \
 reorder.h extnfunc.h rulelhs.h prntutil.h router.h

reteutil.o: reteutil.c setup.h \
 memalloc.h router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h retract.h match.h network.h ruledef.h constrnt.h \
 cstrccom.h agenda.h pattern.h reorder.h drive.h incrrset.h reteutil.h

retract.o: retract.c \
 setup.h constant.h memalloc.h \
 symbol.h argacces.h expressn.h exprnops.h evaluatn.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h router.h prntutil.h network.h \
 match.h pattern.h reorder.h ruledef.h constrnt.h cstrccom.h agenda.h \
 drive.h lgcldpnd.h retract.h

router.o: router.c setup.h constant.h memalloc.h \
 filertr.h strngrtr.h extnfunc.h symbol.h expressn.h exprnops.h userdata.h \
 argacces.h evaluatn.h moduldef.h constrct.h scanner.h pprint.h sysdep.h \
 router.h prntutil.h

rulebin.o: rulebin.c setup.h \
 memalloc.h bload.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h exprnbin.h sysdep.h symblbin.h bsave.h reteutil.h \
 evaluatn.h constant.h match.h network.h ruledef.h constrct.h moduldef.h \
 scanner.h pprint.h constrnt.h cstrccom.h agenda.h pattern.h reorder.h \
 engine.h rulebsc.h rulebin.h modulbin.h cstrcbin.h

rulebld.o: rulebld.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h watch.h drive.h match.h \
 network.h ruledef.h constrnt.h cstrccom.h agenda.h pattern.h reorder.h \
 reteutil.h incrrset.h rulebld.h

rulebsc.o: rulebsc.c setup.h argacces.h \
 expressn.h exprnops.h evaluatn.h constant.h symbol.h userdata.h \
 moduldef.h constrct.h scanner.h pprint.h router.h prntutil.h watch.h \
 extnfunc.h ruledef.h constrnt.h cstrccom.h agenda.h match.h network.h \
 pattern.h reorder.h engine.h rulebin.h modulbin.h cstrcbin.h rulecmp.h \
 conscomp.h symblcmp.h rulebsc.h

rulecmp.o: rulecmp.c setup.h \
 factbld.h pattern.h evaluatn.h constant.h symbol.h \
 expressn.h exprnops.h userdata.h scanner.h pprint.h match.h network.h \
 ruledef.h constrct.h moduldef.h constrnt.h cstrccom.h agenda.h reorder.h \
 reteutil.h rulecmp.h conscomp.h extnfunc.h symblcmp.h

rulecom.o: rulecom.c setup.h constant.h memalloc.h evaluatn.h symbol.h \
 expressn.h exprnops.h userdata.h extnfunc.h engine.h ruledef.h constrct.h \
 moduldef.h scanner.h pprint.h constrnt.h cstrccom.h agenda.h match.h \
 network.h pattern.h reorder.h watch.h crstrtgy.h argacces.h router.h \
 prntutil.h reteutil.h ruledlt.h rulebin.h modulbin.h cstrcbin.h \
 lgcldpnd.h incrrset.h rulecom.h

rulecstr.o: rulecstr.c setup.h \
 router.h prntutil.h moduldef.h symbol.h \
 evaluatn.h constant.h expressn.h exprnops.h userdata.h constrct.h \
 scanner.h pprint.h reorder.h ruledef.h constrnt.h cstrccom.h agenda.h \
 match.h network.h pattern.h cstrnchk.h cstrnops.h extnfunc.h analysis.h \
 prcdrpsr.h cstrnutl.h rulepsr.h rulecstr.h

ruledef.o: ruledef.c setup.h memalloc.h \
 engine.h ruledef.h symbol.h expressn.h exprnops.h \
 evaluatn.h constant.h userdata.h constrct.h moduldef.h scanner.h pprint.h \
 constrnt.h cstrccom.h agenda.h match.h network.h pattern.h reorder.h \
 rulebsc.h rulecom.h drive.h rulepsr.h ruledlt.h bload.h extnfunc.h \
 exprnbin.h sysdep.h symblbin.h rulebin.h modulbin.h cstrcbin.h rulecmp.h \
 conscomp.h symblcmp.h

ruledlt.o: ruledlt.c setup.h \
 memalloc.h engine.h ruledef.h symbol.h expressn.h \
 exprnops.h evaluatn.h constant.h userdata.h constrct.h moduldef.h \
 scanner.h pprint.h constrnt.h cstrccom.h agenda.h match.h network.h \
 pattern.h reorder.h reteutil.h drive.h retract.h bload.h extnfunc.h \
 exprnbin.h sysdep.h symblbin.h ruledlt.h

rulelhs.o: rulelhs.c setup.h \
 constant.h symbol.h memalloc.h exprnpsr.h \
 extnfunc.h expressn.h exprnops.h userdata.h scanner.h pprint.h argacces.h \
 evaluatn.h moduldef.h constrct.h reorder.h ruledef.h constrnt.h \
 cstrccom.h agenda.h match.h network.h pattern.h router.h prntutil.h \
 cstrnchk.h rulelhs.h

rulepsr.o: rulepsr.c setup.h \
 constant.h memalloc.h symbol.h scanner.h pprint.h \
 router.h prntutil.h moduldef.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h engine.h ruledef.h constrnt.h cstrccom.h agenda.h \
 match.h network.h pattern.h reorder.h rulelhs.h rulebld.h cstrnchk.h \
 cstrnops.h exprnpsr.h extnfunc.h analysis.h prcdrpsr.h prccode.h \
 incrrset.h rulecstr.h watch.h ruledlt.h cstrcpsr.h rulebsc.h lgcldpnd.h \
 tmpltfun.h factmngr.h multifld.h tmpltdef.h factbld.h bload.h exprnbin.h \
 sysdep.h symblbin.h rulepsr.h

scanner.o: scanner.c setup.h \
 constant.h router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h \
 exprnops.h userdata.h constrct.h scanner.h pprint.h utility.h memalloc.h 

sortfun.o: sortfun.c setup.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h extnfunc.h \
 memalloc.h multifld.h sysdep.h sortfun.h

strngfun.o: strngfun.c setup.h \
 memalloc.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h argacces.h evaluatn.h constant.h moduldef.h \
 constrct.h scanner.h pprint.h router.h prntutil.h strngrtr.h prcdrpsr.h \
 constrnt.h cstrcpsr.h exprnpsr.h drive.h match.h network.h ruledef.h \
 cstrccom.h agenda.h pattern.h reorder.h strngfun.h

strngrtr.o: strngrtr.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h strngrtr.h

symblbin.o: symblbin.c setup.h memalloc.h exprnpsr.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h scanner.h pprint.h \
 argacces.h evaluatn.h constant.h moduldef.h constrct.h router.h prntutil.h cstrnbin.h \
 constrnt.h bload.h exprnbin.h sysdep.h symblbin.h bsave.h

symblcmp.o: symblcmp.c setup.h symbol.h memalloc.h \
 constant.h exprnpsr.h extnfunc.h expressn.h exprnops.h userdata.h \
 scanner.h pprint.h cstrccom.h moduldef.h evaluatn.h constrct.h argacces.h \
 cstrncmp.h constrnt.h router.h prntutil.h conscomp.h symblcmp.h utility.h

symbol.o: symbol.c setup.h constant.h memalloc.h \
 router.h prntutil.h moduldef.h symbol.h evaluatn.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h utility.h argacces.h

sysdep.o: sysdep.c setup.h argacces.h expressn.h \
 exprnops.h evaluatn.h constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h bmathfun.h conscomp.h extnfunc.h symblcmp.h \
 constrnt.h cstrcpsr.h emathfun.h filecom.h iofun.h memalloc.h miscfun.h \
 multifun.h parsefun.h prccode.h prdctfun.h proflfun.h prcdrfun.h router.h \
 prntutil.h sortfun.h strngfun.h textpro.h utility.h watch.h sysdep.h \
 dffctdef.h cstrccom.h ruledef.h agenda.h match.h network.h pattern.h \
 reorder.h genrccom.h genrcfun.h object.h multifld.h dffnxfun.h globldef.h \
 tmpltdef.h factbld.h factmngr.h extobj.h

textpro.o: textpro.c setup.h \
 commline.h memalloc.h argacces.h expressn.h exprnops.h evaluatn.h \
 constant.h symbol.h userdata.h moduldef.h constrct.h scanner.h pprint.h \
 extnfunc.h router.h prntutil.h textpro.h

tmpltbin.o: tmpltbin.c setup.h memalloc.h bload.h \
 extnfunc.h symbol.h expressn.h exprnops.h userdata.h exprnbin.h sysdep.h \
 symblbin.h bsave.h factbin.h factbld.h pattern.h evaluatn.h constant.h \
 scanner.h pprint.h match.h network.h ruledef.h constrct.h moduldef.h \
 constrnt.h cstrccom.h agenda.h reorder.h cstrnbin.h factmngr.h multifld.h \
 tmpltdef.h tmpltpsr.h tmpltutl.h tmpltbin.h cstrcbin.h modulbin.h

tmpltbsc.o: tmpltbsc.c setup.h argacces.h expressn.h \
 exprnops.h evaluatn.h constant.h symbol.h userdata.h moduldef.h \
 constrct.h scanner.h pprint.h memalloc.h router.h prntutil.h extnfunc.h \
 cstrccom.h factrhs.h factmngr.h pattern.h match.h network.h ruledef.h \
 constrnt.h agenda.h reorder.h multifld.h tmpltdef.h factbld.h cstrcpsr.h \
 tmpltpsr.h tmpltbin.h cstrcbin.h modulbin.h tmpltcmp.h tmpltutl.h \
 tmpltbsc.h

tmpltcmp.o: tmpltcmp.c setup.h \
 conscomp.h extnfunc.h symbol.h expressn.h \
 exprnops.h userdata.h symblcmp.h moduldef.h evaluatn.h constant.h \
 constrct.h scanner.h pprint.h factcmp.h pattern.h match.h network.h \
 ruledef.h constrnt.h cstrccom.h agenda.h reorder.h cstrncmp.h tmpltdef.h \
 factbld.h factmngr.h multifld.h tmpltcmp.h

tmpltdef.o: tmpltdef.c setup.h memalloc.h exprnops.h \
 expressn.h cstrccom.h moduldef.h symbol.h evaluatn.h constant.h \
 userdata.h constrct.h scanner.h pprint.h network.h match.h pattern.h \
 reorder.h ruledef.h constrnt.h agenda.h tmpltpsr.h tmpltdef.h factbld.h \
 factmngr.h multifld.h tmpltbsc.h tmpltutl.h tmpltfun.h router.h \
 prntutil.h modulpsr.h modulutl.h cstrnchk.h bload.h extnfunc.h exprnbin.h \
 sysdep.h symblbin.h tmpltbin.h cstrcbin.h modulbin.h tmpltcmp.h

tmpltfun.o: tmpltfun.c setup.h constant.h memalloc.h \
 symbol.h scanner.h pprint.h exprnpsr.h extnfunc.h expressn.h exprnops.h \
 userdata.h argacces.h evaluatn.h moduldef.h constrct.h router.h \
 prntutil.h cstrnchk.h constrnt.h default.h factmngr.h pattern.h match.h \
 network.h ruledef.h cstrccom.h agenda.h reorder.h multifld.h tmpltdef.h \
 factbld.h commline.h factrhs.h modulutl.h tmpltlhs.h tmpltutl.h \
 tmpltrhs.h tmpltfun.h

tmpltlhs.o: tmpltlhs.c setup.h constant.h memalloc.h \
 symbol.h scanner.h pprint.h exprnpsr.h extnfunc.h expressn.h exprnops.h \
 userdata.h router.h prntutil.h moduldef.h evaluatn.h constrct.h \
 constrnt.h reorder.h ruledef.h cstrccom.h agenda.h match.h network.h \
 pattern.h factrhs.h factmngr.h multifld.h tmpltdef.h factbld.h modulutl.h \
 tmpltutl.h tmpltlhs.h

tmpltpsr.o: tmpltpsr.c setup.h constant.h memalloc.h \
 symbol.h scanner.h pprint.h exprnpsr.h extnfunc.h expressn.h exprnops.h \
 userdata.h router.h prntutil.h moduldef.h evaluatn.h constrct.h \
 factmngr.h pattern.h match.h network.h ruledef.h constrnt.h cstrccom.h \
 agenda.h reorder.h multifld.h tmpltdef.h factbld.h cstrnchk.h cstrnpsr.h \
 cstrcpsr.h bload.h exprnbin.h sysdep.h symblbin.h default.h watch.h \
 cstrnutl.h tmpltbsc.h tmpltpsr.h

tmpltrhs.o: tmpltrhs.c setup.h memalloc.h prntutil.h \
 moduldef.h symbol.h evaluatn.h constant.h expressn.h exprnops.h \
 userdata.h constrct.h scanner.h pprint.h router.h tmpltfun.h factmngr.h \
 pattern.h match.h network.h ruledef.h constrnt.h cstrccom.h agenda.h \
 reorder.h multifld.h tmpltdef.h factbld.h factrhs.h extnfunc.h modulutl.h \
 default.h tmpltutl.h tmpltlhs.h tmpltrhs.h

tmpltutl.o: tmpltutl.c setup.h extnfunc.h symbol.h \
 expressn.h exprnops.h userdata.h memalloc.h constrct.h moduldef.h \
 evaluatn.h constant.h scanner.h pprint.h router.h prntutil.h argacces.h \
 cstrnchk.h constrnt.h tmpltfun.h factmngr.h pattern.h match.h network.h \
 ruledef.h cstrccom.h agenda.h reorder.h multifld.h tmpltdef.h factbld.h \
 tmpltpsr.h modulutl.h watch.h tmpltbsc.h tmpltutl.h

userdata.o: userdata.c setup.h userdata.h

utility.o: utility.c setup.h evaluatn.h \
 constant.h symbol.h expressn.h exprnops.h userdata.h facthsh.h factmngr.h \
 pattern.h scanner.h pprint.h match.h network.h ruledef.h constrct.h \
 moduldef.h constrnt.h cstrccom.h agenda.h reorder.h multifld.h tmpltdef.h \
 factbld.h memalloc.h prntutil.h utility.h

watch.o: watch.c setup.h constant.h memalloc.h router.h prntutil.h \
 moduldef.h symbol.h evaluatn.h expressn.h exprnops.h userdata.h \
 constrct.h scanner.h pprint.h argacces.h extnfunc.h watch.h
