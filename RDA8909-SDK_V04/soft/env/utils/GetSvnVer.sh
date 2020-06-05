#!/bin/bash


SVN_VER_PATH="${SOFT_WORKDIR}/platform/system/nbiot/ps/eas/l1c/include"
#handle svn is different from compiler enviroment
ver_cygwin_hdl(){
	BIN_SUBWCREV="SubWCRev.exe"
	#SVN_VER_PATH="./platform/system/nbiot/ps/eas/l1c/include"
	SVN_WORK_COPY_PATH="."
	export PATH=$PATH:/cygdrive/c/Program\ Files/TortoiseSVN/bin/:/cygdrive/c/Program\ Files\ \(x86\)/TortoiseSVN/bin/:/cygdrive/c/TortoiseSVN/bin/:
	which ${BIN_SUBWCREV}
	if [ $? -eq 0 ];then
		${BIN_SUBWCREV} ${SVN_WORK_COPY_PATH} ${SVN_VER_PATH}/nl1c_version.tmpl ${SVN_VER_PATH}/nl1c_version_svn.h
	else
		echo "${BIN_SUBWCREV} not exist!"
	fi
}

ver_linux_hdl(){
	if svn info > /dev/null 2>&1; then
		VER_NUM=`svn info | grep "Last Changed Rev:" | awk -F : '{print $2}' | sed 's/^[ \t]*//g'`
		#echo "static const char *g_strNbiotSvnVersion = \"svn:${VER_NUM}\";" >  ${SVN_VER_PATH}/nl1c_version_svn.h
		awk -v ver_var=${VER_NUM} '{if(/WCREV/){print "static const char *g_strNbiotSvnVersion = \"svn:"ver_var"\";" }else{print $0}}' ${SVN_VER_PATH}/nl1c_version.tmpl >  ${SVN_VER_PATH}/nl1c_version_svn.h
	fi
}

COMP_TYPE=`uname`
if [ "${COMP_TYPE}"S = "Linux"S ];then
    ver_linux_hdl
else
    ver_cygwin_hdl
fi



