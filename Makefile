# Compiler
CXX = g++
TARGET = main
TARGET_DIR = ./src
SRCS = $(TARGET_DIR)/main.cpp $(TARGET_DIR)/Classes/Mesh.cpp $(TARGET_DIR)/Classes/Shader.cpp $(TARGET_DIR)/Classes/Window.cpp
OBJS = $(SRCS:.cpp=.o)
INC_DIRS = -I$(TARGET_DIR)/Classes

# OpenGL, GLFW, and GLEW libraries
LIBS = -lglfw3 -lGLEW -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET_DIR)/$(TARGET) $(LIBS)

# Rule for compiling .cpp files to .o files
$(TARGET_DIR)/%.o: $(TARGET_DIR)/%.cpp
	$(CXX) $(INC_DIRS) -c $< -o $@

clean:
	rm -f $(TARGET_DIR)/*.o $(TARGET_DIR)/$(TARGET)
