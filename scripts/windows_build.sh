#!/bin/bash -e

[ -z "$UE5" -a -d "/c/Program Files/Epic Games/UE_5.5" ] && export UE5="/c/Program Files/Epic Games/UE_5.5"
[ -z "$UE5" -a -d "/c/UE_5.5" ] && export UE5="/c/UE_5.5"
[ -z "$UE5" -a -d "/d/UE_5.5" ] && export UE5="/d/UE_5.5"
if [ -z "$UE5" ]; then
    echo "Don't know where UE5 is installed. Please set environment variable UE5."
    exit 1
fi

cd "$(dirname $0)/.."

rm -rf Binaries Intermediate Saved Build
"$UE5/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="$PWD/InhumateRTI.uplugin" -Package="$PWD/Build" -Rocket -TargetPlatforms=Win64
rm -rf Build/Intermediate
