#!/bin/bash -e

root="$(realpath $(dirname $0)/..)"

if [ -d "$root/../../rti-client/cpp" ]; then
    cpp_root="$root/../../rti-client/cpp"
    echo "Using local c++ client"
elif [ -d "$root/../../../../rti-client/cpp" ]; then
    cpp_root="$root/../../../../rti-client/cpp"
    echo "Using local c++ client"
else
    echo "Where c++ client?"
    exit 1
fi
cpp_build_root="$cpp_root/build-ue5"
cd "$cpp_root"

#bash scripts/windows_ue5_build.sh

cd "$cpp_build_root"
rm -rf "$root/Source/ThirdParty/Include"/*
rm -rf "$root/Source/ThirdParty/Win64"/*
mkdir -p "$root/Source/ThirdParty/Include"
mkdir -p "$root/Source/ThirdParty/Win64"
cp -rfp "$cpp_build_root/Include"/* "$root/Source/ThirdParty/Include/"
cp -rfp "$cpp_build_root/Win64"/* "$root/Source/ThirdParty/Win64/"
