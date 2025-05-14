#!/bin/bash -e

if [ -z "$VERSION" ]; then
    echo "Please set the VERSION environment variable when manually building a release."
    exit 1
fi

FILENAME=inhumate-unreal-rti-$VERSION.zip

cd "$(dirname $0)/.."

# Check some FAB BS
echo "Number of classes:" $(find Source -name '*.cpp' | wc -l)
echo "Number of blueprints": $(find Content -name '*.uasset' | wc -l)

set -e
for file in $(find Source/Inhumate* -name '*.h' -o -name '*.cpp'); do
    head -n1 $file | grep -q Copyright || ( echo "$file is missing copyright" ; false )
    copy=$(head -n1 $file)
done
echo $copy


rm -rf Build
mkdir -p Build/InhumateRTI
cp -rfp InhumateRTI.uplugin Content Resources Source LICENSE.txt Build/InhumateRTI/
cp -f README-Packaged.md Build/InhumateRTI/README.txt
sed -i "s/0.0.1-dev-version/${VERSION}/g" Build/InhumateRTI/README.txt Build/InhumateRTI/InhumateRTI.uplugin Build/InhumateRTI/Source/InhumateRTI/Public/RTISubsystem.h


cd Build
find Source/ThirdParty -name '*.sh' -delete
zip -r $FILENAME *

# FAB doesn't want executables in their packages...

FILENAME=inhumate-unreal-rti-fab-$VERSION.zip

find Source/ThirdParty -name '*.exe' -delete
find Source/ThirdParty -name protoc -delete

zip -r $FILENAME *
