#!/bin/bash

# This script will sync stack source code from official repo.
# It should be executed from top directory ("soft").
#
# syntax: env/syncstack.sh <version>

set -e

STACK_URL=http://rdasvn.rdamicro.com/repos/developing1/Sources/stack/branches/4C4D
NEW_STACK_VERSION=$1
if test -z $NEW_STACK_VERSION; then
    echo "Stack version not specified!"
    exit 1
fi

STACK_DIR=platform/system/stack
if test ! -d $STACK_DIR; then
    echo "$STACK_DIR  not exist!"
    exit 1
fi

VERSION_STR=$(cat ${STACK_DIR}/VERSION)
OLD_STACK_VERSION=${VERSION_STR##*@}
mv $STACK_DIR/Makefile $STACK_DIR/../stack_makefile
mv $STACK_DIR/stack.mk $STACK_DIR/../stack_mk
rm -rf $STACK_DIR
svn export ${STACK_URL}@${NEW_STACK_VERSION} $STACK_DIR
mv $STACK_DIR/../stack_makefile $STACK_DIR/Makefile
mv $STACK_DIR/../stack_mk $STACK_DIR/stack.mk

# House keeping
sed -i "/export PLATFORM_STACK/c\export PLATFORM_STACK :=platform\/system\/stack" ${STACK_DIR}/stack.mk
echo "${STACK_URL}@${NEW_STACK_VERSION}" > ${STACK_DIR}/VERSION

# GIT commit
pushd ${STACK_DIR}
LOG=$(svn log ${STACK_URL} -r $[$OLD_STACK_VERSION+1]:$1)
git add -A .
git commit -m "
Sync stack source to r${NEW_STACK_VERSION}

$LOG"
popd
echo "update stack from $OLD_STACK_VERSION to $1"
