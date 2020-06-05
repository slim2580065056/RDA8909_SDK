#!/bin/bash

STACK_DIR=platform/system/stack # stack path in source tree
WAPMMS_DIR=application/coolmmi/mmi/wapmms/jcore # jcore path in source tree
FOTA_DIR=platform/service/fota/fota_core # fota lib path in source tree
GOKE_FLASH_TOOL_DIR=toolpool/blfpc/goke_flash_tool # goke flash tool path in source tree

function export_diff_files
{
    local PATCH_PACKAGE=$SOFT_WORKDIR/patchdir/diff_$3
    local PATCH_LIST=$PATCH_PACKAGE/filelist
    local NEW=$PATCH_PACKAGE/new
    local OLD=$PATCH_PACKAGE/old
    local OLDVERSION=$1
    local NEWVERSION=$2

    cd $SOFT_WORKDIR

    if test -d $PATCH_PACKAGE; then
        echo "$PATCH_PACKAGE existed!"
        exit -1
    fi

    mkdir -p $PATCH_PACKAGE
    mkdir -p $NEW
    mkdir -p $OLD

    git diff $OLDVERSION $NEWVERSION --name-only > $PATCH_LIST

    for f in `cat $PATCH_LIST`; do
        local SKIP=no
        case "$f" in
        $STACK_DIR/*) SKIP=yes;;
        $WAPMMS_DIR/*) SKIP=yes;;
        $FOTA_DIR/*) SKIP=yes;;
        $GOKE_FLASH_TOOL_DIR/*) SKIP=yes;;
        */internal_doc/*) SKIP=yes;;
        *);;
        esac

        if test $SKIP = "no"; then
            d=`dirname $f`
            mkdir -p $OLD/$d
            git show $OLDVERSION:$f > $OLD/$f
            mkdir -p $NEW/$d
            git show $NEWVERSION:$f > $NEW/$f
        fi
    done
}

if [ $# -eq 3 ]; then
    if test -z "$SOFT_WORKDIR"; then
        echo "SOFT_WORKDIR not defined!"
        exit -1
    fi
    if test ! -d "$SOFT_WORKDIR"; then
        echo "SOFT_WORKDIR ($SOFT_WORKDIR) not existed!"
        exit -1
    fi
    export_diff_files $1 $2 $3
else
    echo "Usage:
    ./run_script.sh old_commit_ID new_commit_ID patch_name
Note:
    Before running the script, both old and new commit ID should exist in
    local repository.
"
fi
