#!/bin/bash -e

root="$(realpath $(dirname $0)/..)"

if [ -d "$root/../../rti-client/cpp" ]; then
    cpp_root="$root/../../rti-client-/cpp"
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

#scripts/linux_ue5_build.sh

rm -rf "$root/Source/ThirdParty/Include"
rm -rf "$root/Source/ThirdParty/Linux"
cp -rfp "$cpp_build_root/Include" "$root/Source/ThirdParty/"
cp -rfp "$cpp_build_root/Linux" "$root/Source/ThirdParty/"
