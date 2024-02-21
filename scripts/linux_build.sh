#!/bin/bash -e

[ -z "$UE5" -a -d "$HOME/UnrealEngine" ] && export UE5="$HOME/UnrealEngine"
[ -z "$UE5" -a -d "$HOME/Projects/UnrealEngine" ] && export UE5="$HOME/Projects/UnrealEngine"
if [ -z "$UE5" ]; then
    echo "Don't know where UE5 is installed. Please set environment variable UE5."
    exit 1
fi

cd "$(dirname $0)/.."

rm -rf Binaries Intermediate Saved Build
"$UE5/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="$PWD/InhumateRTI.uplugin" -Package="$PWD/Build" -Rocket -TargetPlatform=Linux
rm -rf Build/Intermediate
