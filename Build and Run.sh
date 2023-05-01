# start by removing the old release
rm -rf Release


# go into the build directory
cd build

# run cmake to generate the build files
cmake ..

# run make to build the project
make

#  run
# only run if the build succeeded
rc=$?
if [ $rc -ne 0 ]; then
  echo "Make failed, exit code [$rc]"
  exit $rc
fi


# copy the executable from the build directory to the release directory mac
mkdir -p ../Release && cp -f ./game.app/Contents/MacOS/game ../Release/Game
# in the future, we will copy the resources from the build directory to the release directory

# run the executable
cd ../Release && ./Game
