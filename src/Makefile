ifeq ($(shell uname),Linux)
THIRD_PARTY_LIB_ROOT =../lib
CXXFLAGS = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-unused-parameter -O3 -fopenmp -std=c++17
else 
THIRD_PARTY_LIB_ROOT = ../lib
CXXFLAGS = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-unused-parameter -O1 -std=c++17
endif

CR = coin-Rehearse

LDFLAGS  = 
LIBS     =
INCLUDE  = -I$(THIRD_PARTY_LIB_ROOT)/toml11/

TARGET   = ./run
OBJDIR   = ./obj
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o)) 
DEPENDS  = $(OBJECTS:.o=.d)
$(TARGET): $(OBJECTS) $(LIBS)
	$(CXX) -o $@ $^ $(LDFLAGS)
$(OBJDIR)/%.o: %.cpp
	@if [ ! -d $(OBJDIR) ];\
	then echo "mkdir -p $(OBJDIR)";mkdir -p $(OBJDIR);\
	fi
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
.PHONY: all
all: clean $(TARGET)
.PHONY:clean
clean:
	$(RM) $(OBJECTS) $(DEPENDS) $(TARGET)
-include $(DEPENDS)
