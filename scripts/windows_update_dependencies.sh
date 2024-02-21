#!/bin/bash -e

[ -z "$UE5" -a -d "/c/Program Files/Epic Games/UE_5.3" ] && export UE5="/c/Program Files/Epic Games/UE_5.3"
[ -z "$UE5" -a -d "/c/UE_5.3" ] && export UE5="/c/UE_5.3"
[ -z "$UE5" -a -d "/d/UE_5.3" ] && export UE5="/d/UE_5.3"
if [ -z "$UE5" ]; then
    echo "Don't know where UE5 is installed. Please set environment variable UE5."
    exit 1
fi

root="$(realpath $(dirname $0)/..)"

if [ -d "$root/../../rti/clients/cpp" ]; then
    cpp_root="$root/../../rti/clients/cpp"
    echo "Using local c++ client"
else
    echo "Where c++ client?"
    exit 1
fi
cpp_build_root="$cpp_root/build-ue5"
cd "$cpp_root"

#bash scripts/windows_ue4_build.sh

cd "$cpp_build_root"
rm -rf "$root/ThirdParty/Include"/*
rm -rf "$root/ThirdParty/Win64"/*
mkdir -p "$root/ThirdParty/Include"
mkdir -p "$root/ThirdParty/Win64"
cp -rfp "$cpp_build_root/Include"/* "$root/ThirdParty/Include/"
cp -rfp "$cpp_build_root/Win64"/* "$root/ThirdParty/Win64/"
