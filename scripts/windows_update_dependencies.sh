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
rm -rf "$root/ThirdParty/Include"/*
rm -rf "$root/ThirdParty/Win64"/*
mkdir -p "$root/ThirdParty/Include"
mkdir -p "$root/ThirdParty/Win64"
cp -rfp "$cpp_build_root/Include"/* "$root/ThirdParty/Include/"
cp -rfp "$cpp_build_root/Win64"/* "$root/ThirdParty/Win64/"
