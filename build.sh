if [ ! -e build/ ]
then
mkdir build
fi
cd build
cmake ..
cd ..
cmake --build /home/vladislav/projects/Tracing/build --target Tracing -- -j 6
