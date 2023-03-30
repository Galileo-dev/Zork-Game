# start by removing the old release
rm -rf Release

cmake .
cmake --build .

mkdir -p Release


# copy the executable from the build directory to the release directory mac
cp ./build/Game Release/Game

# in the future, we will copy the resources from the build directory to the release directory

