#!/bin/bash -e

if [ -z "$VERSION" ]; then
    echo "Please set the VERSION environment variable when manually building a release."
    exit 1
fi

FILENAME=inhumate-rti-unreal-$VERSION.zip

cd "$(dirname $0)/.."

rm -rf Build
mkdir -p Build/InhumateRTI
cp -rfp InhumateRTI.uplugin Content Resources Source ThirdParty Build/InhumateRTI/
cp -f README-Packaged.md Build/InhumateRTI/README.txt
sed -i "s/0.0.1-dev-version/${VERSION}/g" Build/InhumateRTI/README.txt Build/InhumateRTI/Source/InhumateRTI/Public/RTISubsystem.h

cd Build
zip -r $FILENAME *
