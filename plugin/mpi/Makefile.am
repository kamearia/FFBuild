############################################################################
# This file is part of FreeFem++.                                          #
#                                                                          #
# FreeFem++ is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU Lesser General Public License as           #
# published by the Free Software Foundation, either version 3 of           #
# the License, or (at your option) any later version.                      #
#                                                                          #
# FreeFem++ is distributed in the hope that it will be useful,             #
# but WITHOUT ANY WARRANTY; without even the implied warranty of           #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
# GNU Lesser General Public License for more details.                      #
#                                                                          #
# You should have received a copy of the GNU Lesser General Public License #
# along with FreeFem++. If not, see <http://www.gnu.org/licenses/>.        #
############################################################################
# SUMMARY : Makefile for FreeFem++
# LICENSE : LGPLv3
# ORG     : LJLL Universite Pierre et Marie Curie, Paris, FRANCE
# AUTHORS : ...
# E-MAIL  : ...

TESTS=  DDM-Schwarz-Lame-2d.edp DDM-Schwarz-Lame-3d.edp DDM-Schwarz-Lap-2dd.edp DDM-Schwarz-Lap-3d.edp	\
	DDM-Schwarz-Stokes-2d.edp LaplaceRT-3d-matrix-mumps.edp MPICGLap.edp MPIGMRES2D.edp MPIGMRES3D.edp MUMPS.edp	\
	NSI3d-carac-mumps.edp NSI3d-carac.edp Stokes-v1-matrix-mumps.edp 	\
	Stokes-v2-matrix-mumps.edp Stokes-v3-matrix-mumps.edp VG.edp 	\
	cavityNewtow-MUMPS.edp  cmaes-mpi-VarIneq.edp	\
	essai.edp mortar-DN-4-mpi.edp testsolver_MUMPS.edp  parmetis.edp parmetis-3d.edp \
	LapMPIEigenValue.edp htool.edp

XFAIL_TESTS=$(TESTS)

LOG_DRIVER=$(SHELL) $(top_srcdir)/bin/test-driver-ff
TESTS_ENVIRONMENT=TEST_FFPP=$(TEST_FFPPMPI) FLAGS_FFPP="-np 4 -nw" SKIP=$(SKIP_TESTS_MPI)

EXTRA_DIST=*.edp regtests.sh  \
MPICG.cpp \
MUMPS_FreeFem.cpp \
complex_SuperLU_DIST_FreeFem.cpp \
complex_pastix_FreeFem.cpp \
dSuperLU_DIST.cpp \
ffsuperludistoption-1.hpp \
ffsuperludistoption.hpp \
generaldefs.h \
hips_FreeFem.cpp \
hypre_FreeFem.cpp \
interfacepastix.cpp \
parms_FreeFem.cpp \
real_SuperLU_DIST_FreeFem.cpp \
real_pastix_FreeFem.cpp mpi-cmaes.cpp \
ffmumps_fileparam.txt		ffpastix_iparm_dparm.txt	ffsuperlu_dist_fileparam.txt \
MUMPS.cpp parmetis.cpp  \
MUMPS.edp  dmatrix.hpp  ffmumps_fileparam.txt		ffpastix_iparm_dparm.txt	ffsuperlu_dist_fileparam.txt \
htool.cpp htool.edp

# FFCS - list modified to disable some downloaded tools depending on the platform (see
# [[file:../../../configure.ac::tools_problems_all_platforms]] for reasons why some tools may be
# deactivated).

LIST_COMPILE=@TOOL_DYLIB_mumps@ @TOOL_DYLIB_hips@ @TOOL_DYLIB_superludist@ @TOOL_DYLIB_pastix@ MPICG.$(DYLIB_SUFFIX)	\
@TOOL_DYLIB_parms@ mpi-cmaes.$(DYLIB_SUFFIX) parmetis.$(DYLIB_SUFFIX) @TOOL_DYLIB_htool@

if FFCS_MPIOK

# FFCS - do not set loadpath to be able to run an external version of FF on the examples in this directory with
# [[../../mkffref]]

all-local:$(LIST_COMPILE)
	@echo Warning missing mpi plugin: `for i in $(LIST_COMPILE); do if test ! -s $i ; then j=1; echo "$i," ;fi; done`
	echo "finish compile load mpi solver !"
else
all-local:
endif

.cpp.$(DYLIB_SUFFIX): ../plugin/ff-c++ ../plugin/WHERE_LIBRARY-download
#	FFCS needs an error exit code to make sure that all libraries are correctly compiled
#
#	FFCS on Windows inserts all MPI options (include, lib, ...) in the $MPICXX compiler script, instead of "$CXX $MPI_xxx",
#	but it needs '-mpi' to do that
#
###	-../plugin/ff-c++ -auto  $<
	../plugin/ff-c++ -auto -mpi $<

install-exec-local::
	$(mkinstalldirs) -m 755 $(DESTDIR)$(ff_prefix_dir)/lib/mpi
	$(mkinstalldirs) -m 755 $(DESTDIR)$(ff_prefix_dir)/include
	$(mkinstalldirs) -m 755 $(DESTDIR)$(ff_prefix_dir)/etc
	$(mkinstalldirs) -m 755 $(DESTDIR)$(ff_prefix_dir)/idp
	-for i in $(LIST_COMPILE); do \
	 if [ -f $$i ] ; then 	$(INSTALL)  -m 555 $$i $(DESTDIR)$(ff_prefix_dir)/lib/mpi; fi; done


freefem++.pref:Makefile
	echo 'loadpath = "./;../plugin/"' >freefem++.pref
	echo 'includepath = "../../idp/"' >>freefem++.pref
#	echo loadpath += \"./\" >>freefem++.pref
# force the build for freefem++.pref  FH..
DDM-Schwarz-Lame-2d.edp:freefem++.pref
# FFCS - cleaning is useful sometimes
clean-local::
	-rm $(LIST_COMPILE)
	-rm *.$(OBJEXT)

# Local Variables:
# mode:makefile
# ispell-local-dictionary:"british"
# coding:utf-8
# End: