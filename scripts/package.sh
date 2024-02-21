#!/bin/bash -e

[ -z "$VERSION" ] && VERSION=$CI_COMMIT_TAG
[ -z "$VERSION" -a ! -z "$CI_PIPELINE_IID" ] && VERSION=0.0.$CI_PIPELINE_IID
if [ -z "$VERSION" ]; then
    echo "Please set the VERSION environment variable when manually building a release."
    exit 1
fi

FILENAME=inhumate-unreal-rti-client-$VERSION.zip

cd "$(dirname $0)/../Plugins"

if [ "$VERSION" == "0.0.1" -a ! -z "$CI_PIPELINE_ID" ]; then
    FILENAME=inhumate-unreal-rti-client-$CI_PIPELINE_ID.zip
    echo "CI pipeline ${CI_PIPELINE_ID}" >InhumateRTI/VERSION.txt
else
    echo "${VERSION}" >InhumateRTI/VERSION.txt
fi

mkdir -p ../Build
rm -rf InhumateRTI/Intermediate
rm -f InhumateRTI/Binaries

zip -r ../Build/$FILENAME *
ls -lh ../Build/$FILENAME
