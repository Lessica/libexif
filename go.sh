#!/bin/sh -xe

# adapted from the script found here:
# https://stackoverflow.com/a/26812514/2358592

OUTPUT_DIR=$PWD/build

# `-Os`            : optimize for size
# `-fembed-bitcode`: embed llvm bitcode
# `-g3`            : produce debugging information
OPT_FLAGS="-Os"

# on M1 Macbook Air there are 8 cores, so that seems an appropriate number
MAKE_JOBS=8

dobuild()
{
    export CC="$(xcrun -find -sdk ${SDK} cc)"
    export CXX="$(xcrun -find -sdk ${SDK} cxx)"
    export CPP="$(xcrun -find -sdk ${SDK} cpp)"
    export CFLAGS="${HOST_FLAGS} ${OPT_FLAGS}"
    export CXXFLAGS="${HOST_FLAGS} ${OPT_FLAGS}"
    export LDFLAGS="${HOST_FLAGS}"

    ./configure --host=${CHOST} --prefix=${PREFIX} --enable-static --disable-shared

    make clean
    make -j${MAKE_JOBS}
    make install
}

# all iOS devices released after late 2013
SDK="iphoneos"
ARCH_FLAGS="-arch arm64"
HOST_FLAGS="${ARCH_FLAGS} -miphoneos-version-min=13.0 -isysroot $(xcrun -sdk ${SDK} --show-sdk-path)"
CHOST="arm-apple-darwin"
PREFIX="$OUTPUT_DIR/iphoneos-arm64"
dobuild

# Simulator on Intel macs
#SDK="iphonesimulator"
#ARCH_FLAGS="-arch x86_64"
#HOST_FLAGS="${ARCH_FLAGS} -mios-simulator-version-min=13.0 -isysroot $(xcrun -sdk ${SDK} --show-sdk-path)"
#CHOST="x86_64-apple-darwin"
#PREFIX="$OUTPUT_DIR/iphonesimulator-x86_64"
#dobuild

# Simulator on Apple Silicon (e.g. M1) macs
#SDK="iphonesimulator"
#ARCH_FLAGS="-arch arm64"
#HOST_FLAGS="${ARCH_FLAGS} -mios-simulator-version-min=13.0 -isysroot $(xcrun -sdk ${SDK} --show-sdk-path)"
#CHOST="arm-apple-darwin"
#PREFIX="$OUTPUT_DIR/iphonesimulator-arm64"
#dobuild

# create a universal('fat') binary for the two architecture for the iphonesimulator platform
#mkdir -p "$OUTPUT_DIR/iphonesimulator-universal/include"
#mkdir -p "$OUTPUT_DIR/iphonesimulator-universal/lib"
#mkdir -p "$OUTPUT_DIR/iphonesimulator-universal/share"
#cp -R "$OUTPUT_DIR/iphonesimulator-arm64/include/" "$OUTPUT_DIR/iphonesimulator-universal/include/"
#cp -R "$OUTPUT_DIR/iphonesimulator-arm64/share/" "$OUTPUT_DIR/iphonesimulator-universal/share/"
#lipo -create "$OUTPUT_DIR/iphonesimulator-arm64/lib/libexif.a" "$OUTPUT_DIR/iphonesimulator-x86_64/lib/libexif.a" -output "$OUTPUT_DIR/iphonesimulator-universal/lib/libexif.a"

# delete the non-universal folders
#rm -rf "$OUTPUT_DIR/iphonesimulator-arm64"
#rm -rf "$OUTPUT_DIR/iphonesimulator-x86_64"

