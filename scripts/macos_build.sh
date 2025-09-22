#!/bin/bash -e

[ -z "$UE5" -a -d "/Users/Shared/Epic Games/UE_5.6" ] && export UE5="/Users/Shared/Epic Games/UE_5.6"
if [ -z "$UE5" ]; then
    echo "Don't know where UE5 is installed. Please set environment variable UE5."
    exit 1
fi

cd "$(dirname $0)/.."

rm -rf Binaries Intermediate Saved Build
"$UE5/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="$PWD/InhumateRTI.uplugin" -Package="$PWD/Build" -Rocket -TargetPlatform=Mac -specifiedarchitecture=arm64
rm -rf Build/Intermediate
