g++ -o main main.cpp classifier.cpp cluster.cpp image.cpp `pkg-config opencv --cflags --libs opencv`
./main
