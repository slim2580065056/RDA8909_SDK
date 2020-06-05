#!/bin/bash

# This script will sync nbiot source code from official repo.
# It should be executed from top directory ("soft").
#
# syntax: env/syncnbiot.sh <version>

set -e

NBIOT_URL=http://rdasvn.rdamicro.com/repos/developing1/Workspaces/aint/NB_IOT/platform/system/nbiot
NEW_NBIOT_VERSION=$1
if test -z $NEW_NBIOT_VERSION; then
    echo "Stack version not specified!"
    exit 1
fi

NBIOT_DIR=platform/system/nbiot
if test ! -d $NBIOT_DIR; then
    echo "$NBIOT_DIR  not exist!"
    exit 1
fi

if test ! -f ${NBIOT_DIR}/VERSION; then
    touch ${NBIOT_DIR}/VERSION
    chmod +w ${NBIOT_DIR}/VERSION
fi
VERSION_STR=$(cat ${NBIOT_DIR}/VERSION)
OLD_NBIOT_VERSION=${VERSION_STR##*@}
mv $NBIOT_DIR/ncalib $NBIOT_DIR/..
rm -rf $NBIOT_DIR
svn export ${NBIOT_URL}@${NEW_NBIOT_VERSION} $NBIOT_DIR
rm -rf $NBIOT_DIR/ncalib
mv $NBIOT_DIR/../ncalib $NBIOT_DIR
# remove test and vc project code
rm -rf $NBIOT_DIR/win 
rm -f $NBIOT_DIR/*.sln $NBIOT_DIR/*.vcproj
find $NBIOT_DIR -type d -name "*test" | xargs -r rm -rf

# House keeping
echo "${NBIOT_URL}@${NEW_NBIOT_VERSION}" > ${NBIOT_DIR}/VERSION

# GIT commit
pushd ${NBIOT_DIR}
LOG=$(svn log ${NBIOT_URL} -r $[$OLD_NBIOT_VERSION+1]:$1)
git add -A .
git commit -m "Sync nbiot source to r${NEW_NBIOT_VERSION}

$LOG"
popd
echo "update nbiot from $OLD_NBIOT_VERSION to $1"
