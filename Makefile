CC = g++

INCLUDE_DIR = /usr/local/include/
LIB_DIR = /usr/local/lib/

LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

test-inrange: test-inrange.cc
	$(CC) -o test-inrange test-inrange.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)

test-kmeans: test-kmeans.cc
	$(CC) -o test-kmeans test-kmeans.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)

test-opencv: test-opencv.cc
	$(CC) -o test-opencv test-opencv.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)

test-contour: test-contour.cc
	$(CC) -o test-contour test-contour.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)

test-opencv-so: test-opencv-so.cc
	$(CC) -o test-opencv-so test-opencv-so.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)

thresh: thresh.cc
	$(CC) -o thresh thresh.cc -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS)
