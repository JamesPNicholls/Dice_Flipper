#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = xconfig_Lab2Idle
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/utils.js:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/utils.js
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xdc.tci:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xdc.tci
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/template.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/template.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/om2.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/om2.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xmlgen.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xmlgen.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xmlgen2.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/xmlgen2.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/Warnings.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/Warnings.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/IPackage.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/IPackage.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/package.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/package.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/global/Clock.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/global/Clock.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/global/Trace.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/global/Trace.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/bld.js:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/bld.js
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/BuildEnvironment.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/PackageContents.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/PackageContents.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/_gen.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/_gen.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Library.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Library.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Executable.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Executable.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Repository.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Repository.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Configuration.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Configuration.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Script.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Script.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Manifest.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Manifest.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Utils.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/Utils.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget2.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget2.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget3.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITarget3.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/ITargetFilter.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/package.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/bld/package.xs
package.mak: config.bld
C:/ti/bios_6_83_00_18/packages/ti/targets/ITarget.xs:
package.mak: C:/ti/bios_6_83_00_18/packages/ti/targets/ITarget.xs
C:/ti/bios_6_83_00_18/packages/ti/targets/C28_large.xs:
package.mak: C:/ti/bios_6_83_00_18/packages/ti/targets/C28_large.xs
C:/ti/bios_6_83_00_18/packages/ti/targets/C28_float.xs:
package.mak: C:/ti/bios_6_83_00_18/packages/ti/targets/C28_float.xs
C:/ti/bios_6_83_00_18/packages/ti/targets/package.xs:
package.mak: C:/ti/bios_6_83_00_18/packages/ti/targets/package.xs
package.mak: package.bld
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/compiler.opt.xdt
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/io/File.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/io/File.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/io/package.xs:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/services/io/package.xs
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/compiler.defs.xdt
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: C:/ti/ccs1040/xdctools_3_62_01_15_core/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.C28_large.rootDir ?= C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS
ti.targets.packageBase ?= C:/ti/bios_6_83_00_18/packages/ti/targets/
.PRECIOUS: $(XDCCFGDIR)/%.o28L
.PHONY: all,28L .dlls,28L .executables,28L test,28L
all,28L: .executables,28L
.executables,28L: .libraries,28L
.executables,28L: .dlls,28L
.dlls,28L: .libraries,28L
.libraries,28L: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,28L
	@$(ECHO) xdc .executables,28L
	@$(ECHO) xdc .libraries,28L
	@$(ECHO) xdc .dlls,28L


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_xconfig_Lab2Idle.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package xconfig_Lab2Idle" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,28L .dlls: Lab2Idle.p28L

-include package/cfg/Lab2Idle_p28L.mak
-include package/cfg/Lab2Idle_p28L.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/Lab2Idle_p28L.dep
endif
Lab2Idle.p28L: package/cfg/Lab2Idle_p28L.xdl
	@


ifeq (,$(wildcard .libraries,28L))
Lab2Idle.p28L package/cfg/Lab2Idle_p28L.c: .libraries,28L
endif

package/cfg/Lab2Idle_p28L.c package/cfg/Lab2Idle_p28L.h package/cfg/Lab2Idle_p28L.xdl: override _PROG_NAME := Lab2Idle.x28L
package/cfg/Lab2Idle_p28L.c: package/cfg/Lab2Idle_p28L.cfg
package/cfg/Lab2Idle_p28L.xdc.inc: package/cfg/Lab2Idle_p28L.xdl
package/cfg/Lab2Idle_p28L.xdl package/cfg/Lab2Idle_p28L.c: .interfaces

clean:: clean,28L
	-$(RM) package/cfg/Lab2Idle_p28L.cfg
	-$(RM) package/cfg/Lab2Idle_p28L.dep
	-$(RM) package/cfg/Lab2Idle_p28L.c
	-$(RM) package/cfg/Lab2Idle_p28L.xdc.inc

clean,28L::
	-$(RM) Lab2Idle.p28L
.executables,28L .executables: Lab2Idle.x28L

Lab2Idle.x28L: |Lab2Idle.p28L

-include package/cfg/Lab2Idle.x28L.mak
Lab2Idle.x28L: package/cfg/Lab2Idle_p28L.o28L 
	$(RM) $@
	@$(MSG) lnk28L $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.C28_large.rootDir)/bin/cl2000 -fs $(XDCCFGDIR)$(dir $@). -q -u _c_int00 -z  -o $@ package/cfg/Lab2Idle_p28L.o28L   package/cfg/Lab2Idle_p28L.xdl  -w -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.C28_large.rootDir)/lib/libc.a
	
Lab2Idle.x28L: export C_DIR=
Lab2Idle.x28L: PATH:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)
Lab2Idle.x28L: Path:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)

Lab2Idle.test test,28L test: Lab2Idle.x28L.test

Lab2Idle.x28L.test:: Lab2Idle.x28L
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 Lab2Idle.x28L.test
else
	@$(MSG) running $<  ...
	$(call EXEC.Lab2Idle.x28L, ) 
endif

clean,28L::
	-$(RM) $(wildcard .tmp,Lab2Idle.x28L,*)


clean:: clean,28L

clean,28L::
	-$(RM) Lab2Idle.x28L
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
Lab2Idle_p28L.o28L,copy : package/cfg/Lab2Idle_p28L.o28L
Lab2Idle_p28L.s28L,copy : package/cfg/Lab2Idle_p28L.s28L

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,xconfig_Lab2Idle
ifeq (,$(MK_NOGENDEPS))
-include package/rel/xconfig_Lab2Idle.tar.dep
endif
package/rel/xconfig_Lab2Idle/xconfig_Lab2Idle/package/package.rel.xml: package/package.bld.xml
package/rel/xconfig_Lab2Idle/xconfig_Lab2Idle/package/package.rel.xml: package/build.cfg
package/rel/xconfig_Lab2Idle/xconfig_Lab2Idle/package/package.rel.xml: package/package.xdc.inc
package/rel/xconfig_Lab2Idle/xconfig_Lab2Idle/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

xconfig_Lab2Idle.tar: package/rel/xconfig_Lab2Idle.xdc.inc package/rel/xconfig_Lab2Idle/xconfig_Lab2Idle/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/xconfig_Lab2Idle.xdc.inc,package/rel/xconfig_Lab2Idle.tar.dep)


release release,xconfig_Lab2Idle: all xconfig_Lab2Idle.tar
clean:: .clean
	-$(RM) xconfig_Lab2Idle.tar
	-$(RM) package/rel/xconfig_Lab2Idle.xdc.inc
	-$(RM) package/rel/xconfig_Lab2Idle.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
