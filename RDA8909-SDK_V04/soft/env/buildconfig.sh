#!/bin/bash

# This is the script to be integrated with buildbot
# * Master will call "$0 --linux-patch-list" and etc to get the target list to be built
# * Then, master will trigger indivisual target build on workers. And indivisual target
#   build can be performed in parellel. Target build is performed by "$0 -b name"
#
# Environment from master
# * bb_buildnumber
# * bb_revision
# * bb_branch
# * bb_product
# * bb_time
# * bb_res_host
# * bb_res_path

set -e

export bb_time=${bb_time:=$(date +%s)}
export bb_revision=${bb_revision:=unknown}
export bb_product=${bb_product:=dev_unknown}
export bb_res_host=${bb_res_host:=localhost}
export bb_res_path=${bb_res_path:=$HOME/tmp/builds}

export SOFT_WORKDIR=$(readlink -f $(pwd))
export BUILD_TIME=$(date -d "@${bb_time}" "+%Y-%m-%d_%H:%M:%S")
export BUILD_DATE=$(date -d "@${bb_time}" "+%Y%m%d")
export CT_PRODUCT=$bb_product
export PATH=/opt/CSDTK/bin:/opt/mips-rda-elf-20170629p2/bin:/opt/rv32-elf-20170919/bin:/opt/mingw32_3.4.4/usr/bin:$PATH

if test -d .git; then
	export WITH_GIT=1
	export WITH_SVN=0
elif test -d .svn; then
	export WITH_GIT=0
	export WITH_SVN=1
else
	export WITH_GIT=0
	export WITH_SVN=0
fi

cleanup() {
	echo "Cleanup ..."
}

upload_file() {
	local LOCAL_FILE=$1
	local REMOTE_PATH=$2
	local REMOTE_FILE=$3

	echo "Upload file to $2/$3 ..."
	chmod go+r $LOCAL_FILE
	ssh -oStrictHostKeyChecking=no $bb_res_host mkdir -p $bb_res_path/$REMOTE_PATH
	scp -oStrictHostKeyChecking=no $LOCAL_FILE ${bb_res_host}:/$bb_res_path/$REMOTE_PATH/$REMOTE_FILE
}

upload_lod() {
	echo "Upload lod ..."
	local HEX=${CT_TARGET}_${CT_PRODUCT}_${CT_RELEASE}
	cd hex/$HEX
	7z a -tzip ../../${HEX}.zip
	cd ../..
	upload_file ${HEX}.zip . ${HEX}.zip
}

build_modem() {
	export CT_TARGET=$1
	export CT_RELEASE=$2

	cleanup
	source $SOFT_WORKDIR/env/set_env.sh
	ctmake CT_RESGEN=no CT_USERGEN=no
	upload_lod
}

build_modemdb() {
	export CT_TARGET=$1
	export CT_RELEASE=$2

	cleanup
	source $SOFT_WORKDIR/env/set_env.sh
	ctmake CT_RESGEN=no CT_USERGEN=no -C toolpool/blfota
	ctmake CT_RESGEN=no CT_USERGEN=no dbmerge
	upload_lod
}

build_phone() {
	export CT_TARGET=$1
	export CT_RELEASE=$2

	cleanup
	source $SOFT_WORKDIR/env/set_env.sh
	ctmake CT_RESGEN=yes CT_USERGEN=no
	upload_lod
}

build_flash_programmer() {
	cleanup
	source $SOFT_WORKDIR/env/set_env.sh
	cd toolpool/blfpc
	./install.sh
	cd ../../toolpool/plugins/fastpf/flash_programmers/
	7z a -tzip ../../../../blramrun_${CT_PRODUCT}.zip
	cd ../../../..
	upload_file blramrun_${CT_PRODUCT}.zip . blramrun_${CT_PRODUCT}.zip
}

extract_target_release() {
	# example: modem-target-debug
	echo "$1" | cut -d- --output-delimiter=' ' -f2,3
}

build() {
	local TARGET=$1
	echo "build $TARGET ......"

	case "$TARGET" in
	modem-*-debug | modem-*-release) build_modem $(extract_target_release $TARGET) ;;
	modemdb-*-debug | phone-*-release) build_modemdb $(extract_target_release $TARGET) ;;
	phone-*-debug | phone-*-release) build_phone $(extract_target_release $TARGET) ;;
	flash_programmer) build_flash_programmer ;;
	*)
		echo "Unknown target: $TARGET"
		false
		;;
	esac
}

usage() {
	echo "$0 usage:" && grep ")\ #" $0
	exit 0
}

if ! options=$(getopt -o hb: -l help,linux-list,linux-patch-list,linux-merge-list,linux-daily-list,win-list,win-patch-list,win-merge-list,win-daily-list,build: -n "$0" -- "$@"); then
	exit 1
fi

eval set -- "$options"

while [ $# -gt 0 ]; do
	case "$1" in
	--linux-list) #         list Linux target list
		;&
	--linux-patch-list) #   list Linux patch target list
		;&
	--linux-merge-list) #   list Linux merge target list
		;&
	--linux-daily-list) #   list Linux daily target list
		echo "flash_programmer"
		echo "modemdb-8908a_nb_modem_p2-debug"
		echo "modemdb-8908a_nb_modem_p3-debug"
		echo "modemdb-8908a_nb_modem_ml510-debug"
		echo "modemdb-8908a_nb_modem_p4-debug"
		echo "modemdb-8908a_nb_modem_p42-debug"
		echo "modemdb-8908a_nb_modem_1618-debug"
		echo "modemdb-8908a_nb_modem_rsw61-debug"
		echo "modemdb-8908a_nb_modem_wcn-debug"
		shift
		;;
	--win-list) #           list Windows target list
		;&
	--win-patch-list) #     list Windows patch target list
		;&
	--win-merge-list) #     list Windows merge target list
		;&
	--win-daily-list) #     list Windows daily target list
		echo "modemdb-8908a_nb_modem_p2-debug"
		echo "modemdb-8908a_nb_modem_p3-debug"
		echo "modemdb-8908a_nb_modem_ml510-debug"
		echo "modemdb-8908a_nb_modem_p4-debug"
		echo "modemdb-8908a_nb_modem_1618-debug"
		shift
		;;
	-b | --build) #       build a target
		build $2
		shift
		shift
		;;
	-h | --help) #        display help
		usage
		;;
	*) shift ;;
	esac
done
