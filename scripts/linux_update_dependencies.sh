#!/bin/bash -e

root="$(realpath $(dirname $0)/..)"

if [ -d "$root/../../../../rti/clients/cpp" ]; then
    cpp_root="$root/../../../../rti/clients/cpp"
    echo "Using local c++ client"
else
    echo "Where c++ client?"
    exit 1
fi
cpp_build_root="$cpp_root/build-ue4"
cd "$cpp_root"

#scripts/linux_ue4_build.sh

rm -rf "$root/ThirdParty/Include"
rm -rf "$root/ThirdParty/Linux"
cp -rfp "$cpp_build_root/Include" "$root/ThirdParty/"
cp -rfp "$cpp_build_root/Linux" "$root/ThirdParty/"
