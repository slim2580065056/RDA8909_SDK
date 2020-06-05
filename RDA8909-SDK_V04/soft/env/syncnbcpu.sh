#!/bin/bash

# This script will sync nbcpu source code from official repo.
# It should be executed from top directory ("soft").
#
# syntax: env/syncnbcpu.sh <version>

set -e

NBCPU_URL=http://rdasvn.rdamicro.com/repos/developing1/Workspaces/aint/NB_IOT/platform/chip/nbcpu
NEW_NBCPU_VERSION=$1
if test -z $NEW_NBCPU_VERSION; then
    echo "Stack version not specified!"
    exit 1
fi

NBCPU_DIR=platform/chip/nbcpu
if test ! -d $NBCPU_DIR; then
    echo "$NBCPU_DIR  not exist!"
    exit 1
fi

if test ! -f ${NBCPU_DIR}/VERSION; then
    touch ${NBCPU_DIR}/VERSION
    chmod +w ${NBCPU_DIR}/VERSION
fi
VERSION_STR=$(cat ${NBCPU_DIR}/VERSION)
OLD_NBCPU_VERSION=${VERSION_STR##*@}
rm -rf $NBCPU_DIR
svn export ${NBCPU_URL}@${NEW_NBCPU_VERSION} $NBCPU_DIR
# remove test and vc project code
rm -f $NBCPU_DIR/*.suo
rm -rf $NBCPU_DIR/pc_test_platform

# House keeping
echo "${NBCPU_URL}@${NEW_NBCPU_VERSION}" > ${NBCPU_DIR}/VERSION

# GIT commit
pushd ${NBCPU_DIR}
LOG=$(svn log ${NBCPU_URL} -r $[$OLD_NBCPU_VERSION+1]:$1)
git add -A .
git commit -m "Sync nbcpu source to r${NEW_NBCPU_VERSION}

$LOG"
popd
echo "update nbcpu from $OLD_NBCPU_VERSION to $1"
