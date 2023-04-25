# start by removing the old release
rm -rf Release

# make build directory if it doesn't exist
mkdir -p build

# go into the build directory
cd build

# run cmake to generate the build files
cmake ..

# run make to build the project
make

# copy the executable from the build directory to the release directory mac
mkdir -p ../Release && cp ./game.app/Contents/MacOS/game ../Release/Game
# in the future, we will copy the resources from the build directory to the release directory

#  run
cd ../Release && ./Game
