CXX       = g++
CXXFLAGS  = -std=c++17 -O2 -Wall -Wextra
INCLUDES  = -Iinclude
SRC_DIR   = src
OBJ_DIR   = $(SRC_DIR)

COMMON_OBJ = $(OBJ_DIR)/filemanager.o $(OBJ_DIR)/wordlist.o
ENC_OBJ    = $(OBJ_DIR)/encoder.o $(OBJ_DIR)/encoder_main.o


all: encode

encode: $(COMMON_OBJ) $(ENC_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o encode *.txt *.sf
