#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.C28_large{1,0,20.2,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/Lab2Idle_p28L.o28L.dep
package/cfg/Lab2Idle_p28L.o28L.dep: ;
endif

package/cfg/Lab2Idle_p28L.o28L: | .interfaces
package/cfg/Lab2Idle_p28L.o28L: package/cfg/Lab2Idle_p28L.c package/cfg/Lab2Idle_p28L.mak 
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl28L $< ...
	$(ti.targets.C28_large.rootDir)/bin/cl2000 -c  -g -qq -pdsw225 -Dfar=  -mo -v28 -DLARGE_MODEL=1 -ml -eo.o28L -ea.s28L   -Dxdc_cfg__xheader__='"xconfig_Lab2Idle/package/cfg/Lab2Idle_p28L.h"'  -Dxdc_target_name__=C28_large -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_20_2_5 -O2  $(XDCINCS) -I$(ti.targets.C28_large.rootDir)/include -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s o28L $< -C   -g -qq -pdsw225 -Dfar=  -mo -v28 -DLARGE_MODEL=1 -ml -eo.o28L -ea.s28L   -Dxdc_cfg__xheader__='"xconfig_Lab2Idle/package/cfg/Lab2Idle_p28L.h"'  -Dxdc_target_name__=C28_large -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_20_2_5 -O2  $(XDCINCS) -I$(ti.targets.C28_large.rootDir)/include -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/Lab2Idle_p28L.o28L: export C_DIR=
package/cfg/Lab2Idle_p28L.o28L: PATH:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)
package/cfg/Lab2Idle_p28L.o28L: Path:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)

package/cfg/Lab2Idle_p28L.s28L: | .interfaces
package/cfg/Lab2Idle_p28L.s28L: package/cfg/Lab2Idle_p28L.c package/cfg/Lab2Idle_p28L.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl28L -n $< ...
	$(ti.targets.C28_large.rootDir)/bin/cl2000 -c -n -s --symdebug:none -g -qq -pdsw225 -Dfar=  -v28 -DLARGE_MODEL=1 -ml -eo.o28L -ea.s28L   -Dxdc_cfg__xheader__='"xconfig_Lab2Idle/package/cfg/Lab2Idle_p28L.h"'  -Dxdc_target_name__=C28_large -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_20_2_5 -O2  $(XDCINCS) -I$(ti.targets.C28_large.rootDir)/include -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s o28L $< -C  -n -s --symdebug:none -g -qq -pdsw225 -Dfar=  -v28 -DLARGE_MODEL=1 -ml -eo.o28L -ea.s28L   -Dxdc_cfg__xheader__='"xconfig_Lab2Idle/package/cfg/Lab2Idle_p28L.h"'  -Dxdc_target_name__=C28_large -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_20_2_5 -O2  $(XDCINCS) -I$(ti.targets.C28_large.rootDir)/include -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/Lab2Idle_p28L.s28L: export C_DIR=
package/cfg/Lab2Idle_p28L.s28L: PATH:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)
package/cfg/Lab2Idle_p28L.s28L: Path:=$(ti.targets.C28_large.rootDir)/bin/;$(PATH)

clean,28L ::
	-$(RM) package/cfg/Lab2Idle_p28L.o28L
	-$(RM) package/cfg/Lab2Idle_p28L.s28L

Lab2Idle.p28L: package/cfg/Lab2Idle_p28L.o28L package/cfg/Lab2Idle_p28L.mak

clean::
	-$(RM) package/cfg/Lab2Idle_p28L.mak
