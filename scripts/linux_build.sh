#!/bin/bash -e

# apt install libc++-dev libc++abi-dev clang cmake

# Note: UE4 stupidly needs write permissions within the engine source tree
# cd $UE4
# find . -name Intermediate -exec chmod -R a+w {} \;
# find . -name '*FilesWrittenAbsolute.txt' -exec chmod -R a+w {} \;
# chmod -R a+w Engine/Programs

[ -z "$UE4" -a -d "$HOME/UE4" ] && export UE4="$HOME/UE4"
[ -z "$UE4" -a -d "$HOME/UnrealEngine" ] && export UE4="$HOME/UnrealEngine"
[ -z "$UE4" -a -d "$HOME/Projects/UnrealEngine" ] && export UE4="$HOME/Projects/UnrealEngine"

if [ -z "$UE4" ]; then
    echo "Don't know where UE4 is installed. Please set environment variable UE4."
    exit 1
fi

cd "$(dirname $0)/.."

rm -rf Binaries Intermediate Saved Build
"$UE4/Engine/Build/BatchFiles/RunUAT.sh" BuildPlugin -Plugin="$PWD/InhumateRTI.uplugin" -Package="$PWD/Build" -Rocket -TargetPlatform=Linux
rm -rf Build/Intermediate
